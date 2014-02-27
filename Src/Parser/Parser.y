%{
#include <cstdlib>
#include <iostream>
#include <string>

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
	std::string *String;

	unsigned int Token;
}

/* Define our terminal symbols (tokens). This should
 *  match our Lexer.l lex file. We also define the node type
 *  they represent.
 */
%token <String> TIDENTIFIER TINTEGER TDOUBLE TSTRING
%token <Token>  TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <Token>  TLPAREN TRPAREN TLBRACE TRBRACE TLBRACKET TRBRACKET
%token <Token>  TNOP TCOMMA TDOT TINDENT TDEDENT TCOLON
%token <Token>  TPLUS TMINUS TMUL TDIV
%token <Token>  TEOL TRETURN TIF TELSE TELIF TWHILE TFUNC

/* Define the type of node our nonterminal symbols represent.
 *  The types refer to the %union declaration above. Ex: when
 *  we call an ident (defined by union type ident) we are really
 *  calling an (NIdentifier*). It makes the compiler happy.
 */
//%type <String> Numeric Identifier String Expression

/* Operator precedence for mathematical operators */
%nonassoc TCEQ TCNE TCLT TCLE TCGT TCGE

%left   TPLUS TMINUS
%left   TMUL TDIV
%right  TPOW
%right  TEQUAL 

%start Program

%%
Program : Statements {  }
		;

Statements : Statement  {   }
    | Statements Statement  {   }
    ;

Statement : Expression TEOL     {   }
    | ConditionalStatement      {   }
    | TWHILE Expression Block   {   }
    | TFUNC TIDENTIFIER TLPAREN ExpressionList TRPAREN Block    { std::cout << "Function defination found\n"; }
    | TRETURN Expression TEOL   {   }
    ;

ConditionalStatement : IfStatement  {   }
    | IfStatement TELSE Block   { std::cout << "If-ElseIf-Else block found\n";  }
    ;

IfStatement : TIF Expression Block  { std::cout << "If block found\n";  }
    | IfStatement TELIF Expression Block { std::cout << "If-ElseIf block found\n"; }
    ;

Block : TINDENT Statements TDEDENT  {   }
	  ;

Expression : TIDENTIFIER TEQUAL Expression          { std::cout << "Assignment found\n"; }
    | TIDENTIFIER TLPAREN ExpressionList TRPAREN    { std::cout << "Function call with arg found.\n"; }
    | TIDENTIFIER                           {   }  
    | TINTEGER                              {   }
    | TDOUBLE                               {   }
    | TSTRING                               {   }
    | Expression TMUL   Expression          {   }
    | Expression TDIV   Expression          {   }
    | Expression TPLUS  Expression          {   }
    | Expression TMINUS Expression          {   }
    | Expression TPOW   Expression          {   }
    | Expression Comparison Expression      { std::cout << "Comparision found\n"; }
    | TLPAREN Expression TRPAREN            {   }
	;

ExpressionList: /* Blank */
    | Expression                            {   }
    | ExpressionList TCOMMA Expression    {   }
    ;

Comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;

%%
