#include <iostream>
#include <vector>

class NIdentifier;
class NExpression;

typedef std::vector<NExpression*> ExpressionVec;
typedef std::vector<NIdentifier*> IdentifierVec;

class Node
{
public:
	virtual ~Node() {}
};

class NExpression : public Node
{
};

class NStatement : public Node
{
};

class NInteger : public NExpression
{
public:
	long long m_Value;
	NInteger(long long Value) : m_Value( Value ) { }
};

class NDouble : public NExpression
{
public:
	double m_Value;
	NDouble( double Value ) : m_Value( Value ) { }
};

class NIdentifier : public NExpression
{
public:
	std::string m_Name;
	NIdentifier( const std::string& Name ): m_Name( Name ) { }
};

class NMethodCall : public NExpression
{
public:
	const NIdentifier& m_Name;
	ExpressionVec m_Arguments;

	NMethodCall( const NIdentifier& Name, ExpressionList& Arguments ):
		m_Name( Name ),
        m_Arguments( Arguments ) { }

	NMethodCall( const NIdentifier& Name ): m_Name( Name ) { }
};

class NBinaryOperator : public NExpression
{
public:
	int m_Op;

	NExpression& m_Lhs;
	NExpression& m_Rhs;

	NBinaryOperator( NExpression& Lhs, int Op, NExpression& Rhs ):
		m_Lhs( Lhs ),
        m_Rhs( Rhs ),
        m_Op( Op ) { }
};

class NAssignment : public NExpression
{
public:
	NIdentifier& m_Lhs;
	NExpression& m_Rhs;

	NAssignment( NIdentifier& Lhs, NExpression& Rhs ):
        m_Lhs( Lhs ),
        m_Rhs( Rhs ) { }
};

class NBlock : public NExpression
{
public:
	StatementList m_Statements;
	NBlock() { }
};

class NExpressionStatement : public NStatement
{
public:
	NExpression& m_Expression;

	NExpressionStatement( NExpression& Expression ):
		m_Expression( Expression ) { }
};

class NReturnStatement : public NStatement
{
public:
	NExpression& m_Expression;

	NReturnStatement( NExpression& Expression ):
		m_Expression( Expression ) { }
};

class NFunctionDefination : public NStatement
{
public:
	const NIdentifier& m_Name;

	IdentifierVec m_Arguments;

	NBlock& m_Block;

	NFunctionDeclaration( const NIdentifier& Name, const VariableList& Arguments, NBlock& Block ):
        m_Name( Name ),
        m_Arguments( Arguments ),
        m_Block( Block ) { }
};
