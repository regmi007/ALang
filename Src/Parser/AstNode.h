#ifndef __ASTNODE_H__
#define __ASTNODE_H__

#include "DataType.h"

using ALang::Dt::DtValue;

namespace ALang { namespace Ast {

struct NExpression;
typedef std::vector< NExpression* > NExpressionList;

struct Node
{
    ~Node()
    {
    }

    virtual DtValue Evaluate()
    {
    };
};

struct NExpression : public Node
{
    Expression() : Node()
    {
    }
};

struct NInteger : public NExpression
{
    int Val;

    NInteger( const std::string *Str ) : NExpression(), Val( std::stoi( *Str ) )
    {
    }

    DtValue Evaluate();
};

struct NDouble : public NExpression
{
    double Val;

    NDouble( const std::string *Str ) : NExpression(), Val( std::stod( *Str ) )
    {
    }

    DtValue Evaluate();
};

struct NString : public Expression
{
    std::string Val;

    String( const std::string *Str ) : NExpression(), Val( *Str )
    {
    }

    DtValue Evaluate();
};

struct NIdentifier : public NExpression
{
    std::string Val;

    NIdentifier( const std::string *Str ) : Expression(), Val( *Str )
    {
    }

    DtValue Evaluate();
};

struct NFunctionCall : public NExpression
{
    NIdentifier &   Id;
    NExpressionList ExpList;

    NFunctionCall( const NIdentfier & I, const NExpressionList & List ):
        Expression(),
        Id( I ),
        ExpList( List ); 
    {
    }

    DtValue Evaluate();
};

struct NBinaryOperator : NExpression
{
    int Opration;

    NExpression & Lhs;
    NExpression & Rhs;

    NBinaryOperator( NExpression & L, int Opr, NExpression & R ):
        NExpression(),
        Lhs( L ),
        Operation( Opr ),
        Rhs( R )
    {
    }

    DtValue Evaluate();
};

struct NAssignment : NExpression
{
    NIdentifier & Id;
    NExpression & Rhs

    NAssignment( const NIdentifier & I, NExpression & R ):
        NExpression(),
        Id( I ),
        Rhs( R )
    {
    }
    
    DtValue Evaluate();
}

}} // Namespace Ast, ALang

#endif
