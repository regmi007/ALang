#ifndef __AST_H__
#define __AST_H__

#include <memory>
#include <functional>

#include "DataType.hpp"

using ALang::Dt::DtValue;
using ALang::Dt::DtValueMap;

namespace ALang { namespace Ast {

/** struct holding the context for each node evaluation.
 */ 
struct Context
{
    DtValueMap & Local;		///< Map containing local symbols.
    DtValueMap & Global;    ///< Map containing globals symbols.

    Context( DtValueMap & L, DtValueMap & G ) : Local( L ), Global( G )
    {
    }
};

struct NExpression;
struct NStatement;
struct NIdentifier;

typedef std::vector< NStatement* >  StatementList;
typedef std::vector< NExpression* > ExpressionList;
typedef std::vector< NIdentifier* > ParameterList;

/** Signature of a function for built-in functions.
 */
typedef std::function< DtValue( Context & Ctx ) > BuiltInFunction;

/** Base Ast node.
 */ 
struct Node
{
    ~Node()
    {
    }

	/** Function to evaluate each node.
	 */
    virtual DtValue Evaluate( Context & Ctx )
    {
        return DtValue();
    }
};

/** Parent Ast node for diferent kind of statements.
 */ 
struct NStatement : public Node
{
    NStatement() : Node()
    {
    }
};

/** Parent Ast node for diferent kind of expression.
 */ 
struct NExpression : public Node
{
    NExpression() : Node()
    {
    }
};

/** Ast node for Integer.
 */
struct NInteger : public NExpression
{
    int Val;	///< Integer value this node holds.

    NInteger( const std::string & Str ) : NExpression(), Val( std::stoi( Str ) )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

/** Ast node for Double.
 */
struct NDouble : public NExpression
{
    double Val;	///< Double value this node holds.

    NDouble( const std::string & Str ) : NExpression(), Val( std::stod( Str ) )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

/** Ast node for String.
 */
struct NString : public NExpression
{
    const std::string & Val;	///< String value this node holds.

    NString( const std::string & Str ) : NExpression(), Val( Str )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

/** Ast node for Double.
 */
struct NIdentifier : public NExpression
{
    const std::string & Val;	///< Double value this node holds.

    NIdentifier( const std::string & Str ) : NExpression(), Val( Str )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

/** Ast node for Double.
 */
struct NFunctionCall : public NExpression
{
    const NIdentifier & Identifier;		///< Name of the function being called.
    
    ExpressionList ExpList;				///< Argument passed to the function.

    NFunctionCall( const NIdentifier & I, const ExpressionList & List ):
        NExpression(),
        Identifier( I ),
        ExpList( List )
    {
    }

    NFunctionCall( const NIdentifier & I ):
        NExpression(),
        Identifier( I ),
        ExpList() 
    {
    }

	/** Make a function call.
	 * @param Ctx Context for the call.
	 */
    DtValue Evaluate( Context & Ctx );
};

/** Ast node for Array defination.
 */
struct NArrayDefination : public NExpression
{
    ExpressionList ExpList;		///< List of items in the array.

    NArrayDefination(): NExpression(), ExpList()
    {
    }

    NArrayDefination( const ExpressionList & List ):
        NExpression(),
        ExpList( List )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

/** Ast node for binary operation.
 */
struct NBinaryOperator : NExpression
{
    int Operation;		///< Type of operation.

    NExpression & Lhs;	///< Expresssion on the left hand side.
    NExpression & Rhs;	///< Expresssion on the right hand side.

    NBinaryOperator( NExpression & L, int O, NExpression & R ):
        NExpression(),
        Operation( O ),
        Lhs( L ),
        Rhs( R )
    {
    }

    //DtValue Evaluate( Context & Ctx );
};

/** Ast node for assignment.
 */
struct NAssignment : NExpression
{
    const NIdentifier & Identifier;	///< Name of the variable to which value to assign.
    
    NExpression & Rhs;				///< Expresssion on the right hand side.

    NAssignment( const NIdentifier & I, NExpression & R ):
        NExpression(),
        Identifier( I ),
        Rhs( R )
    {
    }
    
    DtValue Evaluate( Context & Ctx );
};

/** Ast node for expression statement .
 */
struct NExpressionStatement : public NStatement
{
	NExpression & Expression;

	NExpressionStatement( NExpression & Expr ) : 
		Expression( Expr )
	{
	}

    DtValue Evaluate( Context & Ctx );
};

/** Ast node for return statement .
 */
struct NReturnStatement : public NStatement
{
	NExpression & Expression;	///< Expression to return.
    
	NReturnStatement( NExpression & Exp ):
        NStatement(),
		Expression( Exp )
    {
    }

    //DtValue Evaluate( Context & Ctx );
};

/** Ast node for code block.
 */
struct NBlock : public NStatement 
{
	StatementList Statements;

	NBlock() : NStatement()
    {
    }

    DtValue Evaluate( Context & Ctx );
};

/** Ast node for For statement.
 * eg,  For( v : arr )
 */
struct NForStatement : public NStatement
{
   	const NIdentifier & Identifier;
	NExpression & Expression;
	NBlock & Block;					///< Code block to evaluate for each value

	NForStatement( const NIdentifier & I, NExpression & E, NBlock & B ):
        NStatement(),
        Identifier( I ),
		Expression( E ),
        Block( B )
    {
    }

	/** Execute the for loop.
	 * @param Ctx Context for the function.
	 */
    DtValue Evaluate( Context & Ctx );
};

/** Parent Ast node for function definition.
 */
struct NFunctionDefinition : public NStatement
{
	const NIdentifier & Identifier;		///< Identifier defining the name of the function.
	ParameterList 		Arguments;		///< List of name of argument this function accepts.
    int ArgsType;						///< Type of args  this function accepts. Variable arg or fixed arg.
    
	NFunctionDefinition(  const NIdentifier & I,  const ParameterList & Args, int T ):
		Identifier( I ),
        Arguments( Args ),
        ArgsType( T )
	{
	}
	
	/** Make a function call.
	 * @param Ctx Context for the function.
	 */
	virtual DtValue Call( Context & Ctx ) = 0;
};

/** Ast node for user defined function.
 */
struct NUserFunctionDefinition : public NFunctionDefinition
{
	NBlock & Block;		///< Code block to evaluate when function is called.

	NUserFunctionDefinition( const NIdentifier & I, const ParameterList & Args, NBlock & Block, int T ):
		NFunctionDefinition( I, Args, T ),
        Block( Block )
    {
    }

    /** Register the function in the supplied context.
	 * @param Ctx Context for the function.
	 */
    DtValue Evaluate( Context & Ctx );
    
    /** Make a function call.
	 * @param Ctx Context for the function.
	 */
	DtValue Call( Context & Ctx );
};

/** Ast node for built-in functions.
 */
struct NBuiltInFunctionDefinition : public NFunctionDefinition
{
    BuiltInFunction Function;		///< Function to call when this functin is called.

	NBuiltInFunctionDefinition( const NIdentifier & I, const ParameterList & Args, BuiltInFunction F, int T ):
		NFunctionDefinition( I, Args, T ),
        Function( F )
    {
    }

    /** Register the function  in the supplied context.
	 * @param Ctx Context for the function.
	 */
    DtValue Evaluate( Context & Ctx );
    
    /** Make a function call.
	 * @param Ctx Context for the function.
	 */
	DtValue Call( Context & Ctx );
};

}} // Namespace Ast, ALang

#endif
