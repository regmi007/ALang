#ifndef __AST_H__
#define __AST_H__

#include <memory>

#include "DataType.hpp"

using ALang::Dt::DtValue;

namespace ALang { namespace Ast {

struct NExpression;
struct NStatement;
struct NIdentifier;

typedef std::vector< NStatement* >  StatementList;
typedef std::vector< NExpression* > ExpressionList;
typedef std::vector< NIdentifier* > ParameterList;

struct Node
{
    ~Node()
    {
    }

    virtual DtValue Evaluate()
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

    NInteger( const std::string *Str ) : NExpression(), Val( std::stoi( *Str ) )
    {
    }

    //DtValue Evaluate();
};

struct NDouble : public NExpression
{
    double Val;

    NDouble( const std::string *Str ) : NExpression(), Val( std::stod( *Str ) )
    {
    }

    //DtValue Evaluate();
};

struct NString : public NExpression
{
    const std::string & Val;

    NString( const std::string *Str ) : NExpression(), Val( *Str )
    {
    }

    //DtValue Evaluate();
};

struct NIdentifier : public NExpression
{
    std::string Val;

    NIdentifier( const std::string & Str ) : NExpression(), Val( Str )
    {
    }

    //DtValue Evaluate();
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

    //DtValue Evaluate();
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
    
    //DtValue Evaluate();
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

    //DtValue Evaluate();
};

struct NFunctionDefinition : public NStatement
{
	const NIdentifier & Identifier;
	
	ParameterList Arguments;
	
	NBlock & Block;

	NFunctionDefinition( const NIdentifier & I, const ParameterList & Args, NBlock & Block ):
		Identifier( I ),
        Arguments( Args ),
        Block( Block )
    {
    }

    //DtValue Evaluate();
};

}} // Namespace Ast, ALang

#endif
