#include <iostream>
#include <vector>

class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

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
	long long value;
	NInteger(long long value) : value(value) { }
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
	const NIdentifier& m_Id;
	ExpressionList m_Arguments;

	NMethodCall( const NIdentifier& Id, ExpressionList& Arguments):
		m_Id( Id ),
        m_Arguments( Arguments ) { }

	NMethodCall( const NIdentifier& Id ): m_Id( id ) { }
};

class NBinaryOperator : public NExpression
{
public:
	int m_Op;

	NExpression& m_Lhs;
	NExpression& m_Rhs;

	NBinaryOperator(NExpression& lhs, int op, NExpression& rhs):
		m_Lhs( Lhs ),
        m_Rhs( Rhs ),
        m_Op( Op ) { }
};

class NAssignment : public NExpression
{
public:
	NIdentifier& m_Lhs;
	NExpression& m_Rhs;

	NAssignment(NIdentifier& lhs, NExpression& rhs):
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

class NVariableDeclaration : public NStatement
{
public:
	const NIdentifier& m_Type;

	NIdentifier& m_Id;

	NExpression *m_AssignmentExpr;

	NVariableDeclaration( const NIdentifier& Type, NIdentifier& Id ):
		m_Type( type ),
        m_Id( id ) { }

	NVariableDeclaration( const NIdentifier& Type, NIdentifier& Id, NExpression *AssignmentExpr ):
		m_Type( Type ),
        m_Id( Id ),
        m_AssignmentExpr( AssignmentExpr ) { }
};

class NFunctionDeclaration : public NStatement
{
public:
	const NIdentifier& m_Type;

	const NIdentifier& m_Id;

	VariableList m_Arguments;

	NBlock& m_Block;

	NFunctionDeclaration( const NIdentifier& Type, const NIdentifier& Id, const VariableList& Arguments, NBlock& Block ):
	    m_Type( Type ),
        m_Id( Id ),
        m_Arguments( Arguments ),
        m_Block( Block ) { }
};
