%{
#include <stack>
#include <string>
#include <iostream>

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

bool First       = true;
bool FirstIndent = true;

unsigned int Nesting        = 0;
unsigned int SpacePerIndent = 0;

std::stack<unsigned int> Indent;

bool ProcessIndent( const char* Line ) ;
%}

%option noyywrap
%option yylineno

%%

^[ ]*\n                 ;

#[^\n]*                 ;

^[ ]*[^ \n]+            {
                            int Last = yyleng - 1;

                            if( ! ProcessIndent( yytext ) )
                            {
                                std::cout << "Indentation mis-match at line: " << yylineno << "\n";
                                yyterminate();
                            }

                            while( ( Last >= 0 ) && ( yytext[ Last ] != ' ') )
                            {
                                unput( yytext[ Last ] );
                                --Last;
                            }
                        }

[ \r\n]                 ;

"Func"                  std::cout << "FUNC\n";
"Return"                std::cout << "RETURN\n";
"If"                    std::cout << "IF\n";
"Else"                  std::cout << "ELSE\n";
"While"                 std::cout << "ELSE\n";

[A-Za-z_][A-Za-z0-9_]*  std::cout << "IDENTFIER, " << yytext << "\n";
[0-9]+\.[0-9]*          std::cout << "DOUBLE, " << yytext << "\n";
[0-9]+                  std::cout << "INT, " << yytext << "\n";

"="                     std::cout << "EQUAL\n";

"=="                    std::cout << "CEQ\n";
"!="                    std::cout << "CNE\n";
"<"                     std::cout << "CLT\n";
"<="                    std::cout << "CLE\n";
">"                     std::cout << "CGT\n";
">="                    std::cout << "CGE\n";

"("                     std::cout << "LPAREN\n"; ++Nesting;
")"                     std::cout << "RPAREN\n"; --Nesting;
"{"                     std::cout << "LBRACE\n"; ++Nesting;
"}"                     std::cout << "RBRACE\n"; --Nesting;
"["                     std::cout << "LBRACKET\n"; ++Nesting;
"]"                     std::cout << "RBRACKET\n"; --Nesting;

"+"                     std::cout << "PLUS\n";
"-"                     std::cout << "MINUS\n";
"*"                     std::cout << "MUL\n";
"/"                     std::cout << "DIV\n";

":"                     std::cout << "COL\n";
"."                     std::cout << "DOT\n";
","                     std::cout << "COMMA\n";

.                       std::cout<< "Unknown token at line: " << yylineno << "\n"; yyterminate();

<<EOF>>                 {
                            ProcessIndent( "" );
                            return 0;
                        }
%%

unsigned int SpaceCount( const char* Line )
{
    unsigned int Count = 0 ;

    while( *Line == ' ' )
        Count++, Line++ ;

    return Count ;
}

bool ProcessIndent( const char* Line )
{
    if( Nesting )
        /* Ignore indents while nested. */
        return true;

    unsigned int Level = SpaceCount( Line ) ;

    if( Level > 0 )
    {
        if( FirstIndent )
        {
            SpacePerIndent = Level;
            FirstIndent = false;
        }

        if( Level % SpacePerIndent != 0 )
            return false;
    } 

    if( Level == Indent.top() )
    {
        if( ! First )
            std::cout << "EOL\n";

        First = false ;

        return true;
    }

    if( Level > Indent.top() )
    {
        std::cout  << "INDENT\n";

        Indent.push( Level );

        return true;
    }

    while( Level < Indent.top() )
    {
        Indent.pop();

        std::cout << "DEDENT\n" ;
    }

    return true;
}
