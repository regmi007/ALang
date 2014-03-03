%{
#include <string>
#include <cstdlib>
#include <iostream>

#include "Parser/Ast.hpp"

ALang::Ast::NBlock *Program;

extern int yylex();
void yyerror( const char *S )
{
    std::cout << "Error: " <<  S << "\n";
    std::exit(1);
}
%}

%error-verbose

/* Represents the many different ways we can access our data */
%union {
	ALang::Ast::Node 		*Node;
	ALang::Ast::NBlock 		*Block;
	ALang::Ast::NExpression *Expr;
	ALang::Ast::NStatement 	*Stmt;
	ALang::Ast::NIdentifier *Ident;
	
	ALang::Ast::ParameterList 	*ParaList;
	ALang::Ast::ExpressionList 	*ExprList;
	
	std::string 	*String;
	unsigned int 	Token;
}

/* Define our terminal symbols (tokens). This should
 *  match our Lexer.l lex file. We also define the node type
 *  they represent.
 */
%token <String> TIDENTIFIER TINTEGER TDOUBLE TSTRING
%token <Token>  TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <Token>  TLPAREN TRPAREN TLBRACE TRBRACE TLBRACKET TRBRACKET
%token <Token>  TNOP TCOMMA TDOT TINDENT TDEDENT TCOLON
%token <Token>  TPLUS TMINUS TMUL TDIV TPOW
%token <Token>  TEOL TRETURN TIF TELSE TELIF TWHILE TFUNC

/* Define the type of node our nonterminal symbols represent.
 *  The types refer to the %union declaration above.
 */

%type <Ident> Identifier
%type <Expr> Expression Number String
%type <ExprList> ExpressionList
%type <ParaList> ParameterList
%type <Block> Program Statements Block
%type <Stmt> Statement
%type <Token> Comparison

/* Operator precedence for mathematical operators */
%nonassoc TCEQ TCNE TCLT TCLE TCGT TCGE

%left   TPLUS TMINUS
%left   TMUL TDIV
%right  TPOW
%right  TEQUAL 

%start Program

%%
Program : Statements { Program = $1; }
		;

Statements : Statement  { $$ = new ALang::Ast::NBlock(); $$->Statements.push_back( $<Stmt>1 ); }
    | Statements Statement  { $1->Statements.push_back( $<Stmt>2 ); }
    ;

Statement : Expression TEOL     {   }
    | TRETURN Expression TEOL   { $$ = new ALang::Ast::NReturnStatement( *$2 ); }
    | ConditionalStatement      {   }
    | TWHILE Expression Block   {   }
    | TFUNC TIDENTIFIER TLPAREN ParameterList TRPAREN Block    {   }
    ;

ConditionalStatement : IfStatement  {   }
    | IfStatement TELSE Block       {   }
    ;

IfStatement : TIF Expression Block       {   }
    | IfStatement TELIF Expression Block {   }
    ;

Block : TINDENT Statements TDEDENT  { $$ = $2; }
	  ;

Identifier : TIDENTIFIER { $$ = new ALang::Ast::NIdentifier( *$1 ); delete $1; }
	  ;

Number : TINTEGER { $$ = new ALang::Ast::NInteger( $1 ); delete $1; }
	| TDOUBLE { $$ = new ALang::Ast::NDouble( $1 ); delete $1; }
	;

String : TSTRING { $$ = new ALang::Ast::NString( $1 ); }
	;

Expression : Identifier TEQUAL Expression          { $$ = new ALang::Ast::NAssignment( *$1, *$3 ); }
    | Identifier TLPAREN ExpressionList TRPAREN    { $$ = new ALang::Ast::NFunctionCall( *$1, *$3 ); delete $3; }
    | Number
    | String
    | Expression TMUL   Expression          { $$ = new ALang::Ast::NBinaryOperator( *$1, $2, *$3 ); }
    | Expression TDIV   Expression          { $$ = new ALang::Ast::NBinaryOperator( *$1, $2, *$3 ); }
    | Expression TPLUS  Expression          { $$ = new ALang::Ast::NBinaryOperator( *$1, $2, *$3 ); }
    | Expression TMINUS Expression          { $$ = new ALang::Ast::NBinaryOperator( *$1, $2, *$3 ); }
    | Expression TPOW   Expression          { $$ = new ALang::Ast::NBinaryOperator( *$1, $2, *$3 ); }
    | Expression Comparison Expression      { $$ = new ALang::Ast::NBinaryOperator( *$1, $2, *$3 ); }
    | TLPAREN Expression TRPAREN            { $$ = $2; }
	;

ExpressionList: /* Blank */                 { $$ = new ALang::Ast::ExpressionList(); }
    | Expression                            { $$ = new ALang::Ast::ExpressionList(); $$->push_back( $1 ); }
    | ExpressionList TCOMMA Expression      { $1->push_back( $3 ); }
    ;

ParameterList: /* Blank */                  { $$ = new ALang::Ast::ParameterList(); }  
    | Identifier                            { $$ = new ALang::Ast::ParameterList(); $$->push_back( $1 );  }
    | ParameterList TCOMMA Identifier	    { $1->push_back( $3 ); }
    ;

Comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;

%%
