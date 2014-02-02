%{
#include "Parser/Ast.h"

#include <cstdlib>
#include <iostream>

/* the top level root node of our final AST */
NBlock *ProgramBlock;

extern int yylex();
void yyerror( const char *S )
{
    std::cout << "Error: " <<  S << "\n";
    std::exit(1);
}
%}

/* Represents the many different ways we can access our data */
%union {
	Node        *Node;
	NBlock      *Block;
	NExpression *Expression;
	NStatement  *Statement;
	NIdentifier *Identifier;

	std::vector<NIdentifier*> *IdentifierVec;

	std::vector<NExpression*> *ExpressionVec;

	std::string     *String;
	unsigned int    Token;
}

/* Define our terminal symbols (tokens). This should
 *  match our Lexer.l lex file. We also define the node type
 *  they represent.
 */
%token <String> TIDENTIFIER TINTEGER TDOUBLE
%token <Token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <Token> TLPAREN TRPAREN TLBRACE TRBRACE TLBRACKET TRBRACKET TCOMMA TDOT
%token <Token> TPLUS TMINUS TMUL TDIV
%token <Token> TEOL TRETURN TIF TELSE TELIF TWHILE

/* Define the type of node our nonterminal symbols represent.
 *  The types refer to the %union declaration above. Ex: when
 *  we call an ident (defined by union type ident) we are really
 *  calling an (NIdentifier*). It makes the compiler happy.
 */
%type <Identifier> Identifier
%type <Expression> Numeric Expression
%type <IdentifierVec> IdentifierList
%type <ExpressionVec> ExpressionList
%type <Block> Program Statements Block
%type <Statement> Statement VariableInit FuncDef
%type <Token> Comparison

/* Operator precedence for mathematical operators */
%nonassoc TCEQ TCNE TCLT TCLE TCGT TCGE

%left   TPLUS TMINUS
%left   TMUL TDIV
%right  TPOW
%right  TEQUAL 

%start Program

%%

Program : Statements { ProgramBlock = $1; }
		;

Statements : Statement          { $$ = new NBlock(); $$->m_Statements.push_back($<Statement>1); }
    | Statements Statement    { $1->m_Statements.push_back($<Statement>2); }
	;

Statement : Expression      { $$ = new NExpressionStatement(*$1); }
	| TRETURN Expression   { $$ = new NReturnStatement(*$2); }
    ;

Block : TINDENT Statements TDEDENT { $$ = $2; }
	;

Identifier : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
    ;

IdentifierList : /*blank*/              {  }
	| Identifier                        {  }
	| IdentifierList TCOMMA Identifier  {  }
	;

FunctionDefination : Identifier Identfier TLPAREN IdentifierList TRPAREN Block
    { $$ = new NFunctionDefination(*$1, *$2, *$4, *$6); delete $4; }
	;

Numeric : TINTEGER  { $$ = new NInteger( atol( $1->c_str() )); delete $1; }
	| TDOUBLE       { $$ = new NDouble( atof( $1->c_str() )); delete $1; }
	;
	
Expression : Identifier TEQUAL Expression    { $$ = new NAssignment(*$<ident>1, *$3); }
    | Identifier TLPAREN CallArgs TRPAREN    { $$ = new NMethodCall(*$1, *$3); delete $3; }
	| Identifier                             { $<Identifier>$ = $1; }
	| Numeric
    | Expression TMUL Expression             { $$ = new NBinaryOperator(*$1, $2, *$3); }
    | Expression TDIV Expression             { $$ = new NBinaryOperator(*$1, $2, *$3); }
    | Expression TPLUS Expression            { $$ = new NBinaryOperator(*$1, $2, *$3); }
    | Expression TMINUS Expression           { $$ = new NBinaryOperator(*$1, $2, *$3); }
 	| Expression Comparison Expression       { $$ = new NBinaryOperator(*$1, $2, *$3); }
    | TLPAREN Expression TRPAREN             { $$ = $2; }
	;
	
ExpressionList : /*blank*/        { $$ = new ExpressionVec(); }
	| Expression                  { $$ = new ExpressionVec(); $$->push_back( $1 ); }
	| ExpressionList TCOMMA Expression  { $1->push_back( $3 ); }
	;

Comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;

%%
