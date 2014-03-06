#ifndef __AST_H__
#define __AST_H__

#include <memory>
#include <functional>

#include "DataType.hpp"

using ALang::Dt::DtValue;
using ALang::Dt::DtValueMap;

namespace ALang { namespace Ast {

struct NExpression;
struct NStatement;
struct NIdentifier;

typedef std::vector< NStatement* >  StatementList;
typedef std::vector< NExpression* > ExpressionList;
typedef std::vector< NIdentifier* > ParameterList;

typedef std::function< DtValue( DtValueMap & Context ) > BuiltInFunction;

struct Node
{
    ~Node()
    {
    }

    virtual DtValue Evaluate( DtValueMap & Context )
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

    DtValue Evaluate( DtValueMap & Context );
};

struct NDouble : public NExpression
{
    double Val;

    NDouble( const std::string & Str ) : NExpression(), Val( std::stod( Str ) )
    {
    }

    DtValue Evaluate( DtValueMap & Context );
};

struct NString : public NExpression
{
    const std::string & Val;

    NString( const std::string & Str ) : NExpression(), Val( Str )
    {
    }

    DtValue Evaluate( DtValueMap & Context );
};

struct NIdentifier : public NExpression
{
    const std::string & Val;

    NIdentifier( const std::string & Str ) : NExpression(), Val( Str )
    {
    }

    DtValue Evaluate( DtValueMap & Context );
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

    DtValue Evaluate( DtValueMap & Context );
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
    
    DtValue Evaluate( DtValueMap & Context );
};

struct NExpressionStatement : public NStatement
{
	NExpression & Expression;

	NExpressionStatement( NExpression & Expr ) : 
		Expression( Expr )
	{
	}

    DtValue Evaluate( DtValueMap & Context );
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

    DtValue Evaluate( DtValueMap & Context );
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
	
	virtual DtValue Call( DtValueMap & Context ) = 0;
};

struct NUserFunctionDefinition : public NFunctionDefinition
{
	NBlock & Block;

	NUserFunctionDefinition( const NIdentifier & I, const ParameterList & Args, NBlock & Block, int T ):
		NFunctionDefinition( I, Args, T ),
        Block( Block )
    {
    }

    DtValue Evaluate( DtValueMap & Context );
	DtValue Call( DtValueMap & Context );
};

struct NBuiltInFunctionDefinition : public NFunctionDefinition
{
    BuiltInFunction Function;

	NBuiltInFunctionDefinition( const NIdentifier & I, const ParameterList & Args, BuiltInFunction F, int T ):
		NFunctionDefinition( I, Args, T ),
        Function( F )
    {
    }

    DtValue Evaluate( DtValueMap & Context );
	DtValue Call( DtValueMap & Context );
};

}} // Namespace Ast, ALang

#endif
