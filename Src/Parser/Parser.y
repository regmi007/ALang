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
//%type <String> Numeric Identifier

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

Statements : Statement {}
    | Statements Statement {}
    ;

Numeric : TINTEGER  { std::cout << "Integer: " << *$1 << "\n"; delete $1; }
	| TDOUBLE       { std::cout << "Double: " << *$1 << "\n"; delete $1; }
	;

Identifier : TIDENTIFIER { std::cout << "Identifier: " << *$1 << "\n"; delete $1; }
    ;

StringLiteral : TSTRING { std::cout << "String: " << *$1 << "\n"; delete $1; }
    ;

Statement : Expression TEOL { }
    | Expression TDEDENT { }
    ;

Expression : Identifier TEQUAL Expression    { std::cout << "Assignment: \n"; }
    | Expression TMUL Expression             {  }
    | Expression TDIV Expression             {  }
    | Expression TPLUS Expression            {  }
    | Expression TMINUS Expression           {  }
	| Identifier                             {  }
	| Numeric                                {  }
    | StringLiteral                          {  }
	;

%%
