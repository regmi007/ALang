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
%type <String> Numeric Identifier String Expression

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

Block : TINDENT Statements TDEDENT  {  std::cout << "Block: \n"; }
	  ;

Numeric : TINTEGER  { $$ = $1; }
	| TDOUBLE       { $$ = $1; }
	;

Identifier : TIDENTIFIER { $$ = $1; }
    ;

String : TSTRING { $$ = $1; }
    ;

Statement : Expression TEOL {   }
    | TIF Expression TINDENT Statements TDEDENT  { std::cout << "If Block found\n";  }
    ;

Expression : Identifier TEQUAL Expression   { std::cout << "Assignment: " << *$1 << " = " << *$3 << "\n"; $$ = $1; }
    | Expression TMUL Expression            {   }
    | Expression TDIV Expression            {   }
    | Expression TPLUS Expression           {   }
    | Expression TMINUS Expression          {   }
    
    | Expression Comparison Expression      { std::cout << "Comparision: " << *$1 << ", " << *$3 << "\n"; }
    
	| Identifier                            {   }
	| Numeric                               {   }
    | String                                {   }
	;

Comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE;

%%
