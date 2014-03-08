#ifndef __AST_H__
#define __AST_H__

#include <memory>
#include <functional>

#include "DataType.hpp"

using ALang::Dt::DtValue;
using ALang::Dt::DtValueMap;

namespace ALang { namespace Ast {

struct Context
{
    DtValueMap & Local;
    DtValueMap & Global;

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

typedef std::function< DtValue( Context & Ctx ) > BuiltInFunction;

struct Node
{
    ~Node()
    {
    }

    virtual DtValue Evaluate( Context & Ctx )
    {
        return DtValue();
    }
};

struct NStatement : public Node
{
    NStatement() : Node()
    {
    }
};

struct NExpression : public Node
{
    NExpression() : Node()
    {
    }
};

struct NInteger : public NExpression
{
    int Val;

    NInteger( const std::string & Str ) : NExpression(), Val( std::stoi( Str ) )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

struct NDouble : public NExpression
{
    double Val;

    NDouble( const std::string & Str ) : NExpression(), Val( std::stod( Str ) )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

struct NString : public NExpression
{
    const std::string & Val;

    NString( const std::string & Str ) : NExpression(), Val( Str )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

struct NIdentifier : public NExpression
{
    const std::string & Val;

    NIdentifier( const std::string & Str ) : NExpression(), Val( Str )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

struct NFunctionCall : public NExpression
{
    const NIdentifier & Identifier;
    
    ExpressionList ExpList;

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

    DtValue Evaluate( Context & Ctx );
};

struct NArrayDefination : public NExpression
{
    ExpressionList ExpList;

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

struct NBinaryOperator : NExpression
{
    int Operation;

    NExpression & Lhs;
    NExpression & Rhs;

    NBinaryOperator( NExpression & L, int O, NExpression & R ):
        NExpression(),
        Operation( O ),
        Lhs( L ),
        Rhs( R )
    {
    }

    //DtValue Evaluate();
};

struct NAssignment : NExpression
{
    const NIdentifier & Identifier;
    
    NExpression & Rhs;

    NAssignment( const NIdentifier & I, NExpression & R ):
        NExpression(),
        Identifier( I ),
        Rhs( R )
    {
    }
    
    DtValue Evaluate( Context & Ctx );
};

struct NExpressionStatement : public NStatement
{
	NExpression & Expression;

	NExpressionStatement( NExpression & Expr ) : 
		Expression( Expr )
	{
	}

    DtValue Evaluate( Context & Ctx );
};

struct NReturnStatement : public NStatement
{
	NExpression & Expression;
    
	NReturnStatement( NExpression & Exp ):
        NStatement(),
		Expression( Exp )
    {
    }

    //DtValue Evaluate();
};

struct NBlock : public NStatement 
{
	StatementList Statements;

	NBlock() : NStatement()
    {
    }

    DtValue Evaluate( Context & Ctx );
};

struct NForStatement : public NStatement
{
   	const NIdentifier & Identifier;
	NExpression & Expression;
	NBlock & Block;

	NForStatement( const NIdentifier & I, NExpression & E, NBlock & B ):
        NStatement(),
        Identifier( I ),
		Expression( E ),
        Block( B )
    {
    }

    DtValue Evaluate( Context & Ctx );
};

struct NFunctionDefinition : public NStatement
{
	const NIdentifier & Identifier;
	ParameterList 		Arguments;
    int ArgsType;
    
	NFunctionDefinition(  const NIdentifier & I,  const ParameterList & Args, int T ):
		Identifier( I ),
        Arguments( Args ),
        ArgsType( T )
	{
	}
	
	virtual DtValue Call( Context & Ctx ) = 0;
};

struct NUserFunctionDefinition : public NFunctionDefinition
{
	NBlock & Block;

	NUserFunctionDefinition( const NIdentifier & I, const ParameterList & Args, NBlock & Block, int T ):
		NFunctionDefinition( I, Args, T ),
        Block( Block )
    {
    }

    DtValue Evaluate( Context & Ctx );
	DtValue Call( Context & Ctx );
};

struct NBuiltInFunctionDefinition : public NFunctionDefinition
{
    BuiltInFunction Function;

	NBuiltInFunctionDefinition( const NIdentifier & I, const ParameterList & Args, BuiltInFunction F, int T ):
		NFunctionDefinition( I, Args, T ),
        Function( F )
    {
    }

    DtValue Evaluate( Context & Ctx );
	DtValue Call( Context & Ctx );
};

}} // Namespace Ast, ALang

#endif
