%{
#include <stack>
#include <string>
#include <cstdlib>
#include <iostream>

#define SAVE_STRING yylval.String = new std::string( yytext, yyleng )

#define TOKEN( t ) ( yylval.Token = t )

bool First       = true;
bool FirstIndent = true;

unsigned int Nesting        = 0;
unsigned int SpacePerIndent = 0;
unsigned int PreviousLevel  = 0;

std::stack<unsigned int> Indent;

bool ProcessIndent( const char* Line ) ;
%}

EXP	([Ee][-+]?[0-9]+)

%option noyywrap
%option yylineno

%%

<DEDENT>.|\n            {
                            yyless(0);

                            if( PreviousLevel < Indent.top() )
                            {
                                Indent.pop();
                                return TOKEN( TDEDENT );
                            }
                            else
                                BEGIN INITIAL;
                        }
                        
^[ ]*\n                 ;

#[^\n]*                 ;

^[ ]*[^ \n]+            {
                            int Last = yyleng - 1;
                            unsigned int Result = ProcessIndent( yytext );
                            
                            if( Result == -1 )
                            {
                                std::cout << "Indentation mis-match at line: " << yylineno << "\n";
                                yyterminate();
                            }

                            while( ( Last >= 0 ) && ( yytext[ Last ] != ' ') )
                            {
                                unput( yytext[ Last ] );
                                --Last;
                            }

                            return Result;
                        }

[ \r\n]                 ;

"Func"                  return TOKEN( TFUNC );
"Return"                return TOKEN( TRETURN );
"If"                    return TOKEN( TIF );
"Else"                  return TOKEN( TELSE );
"Elif"                  return TOKEN( TELIF );
"While"                 return TOKEN( TWHILE );

[A-Za-z_][A-Za-z0-9_]*  SAVE_STRING; return TOKEN( TIDENTIFIER );
[0-9]+\.[0-9]*{EXP}?    SAVE_STRING; return TOKEN( TDOUBLE );
[0-9]+                  SAVE_STRING; return TOKEN( TINTEGER );

"="                     return TOKEN( TEQUAL );

"=="                    return TOKEN( TCEQ );
"!="                    return TOKEN( TCNE );
"<"                     return TOKEN( TCLT );
"<="                    return TOKEN( TCLE );
">"                     return TOKEN( TCGT );
">="                    return TOKEN( TCGE );

"("                     ++Nesting; return TOKEN( TLPAREN );
")"                     --Nesting; return TOKEN( TRPAREN );
"{"                     ++Nesting; return TOKEN( TLBRACE );
"}"                     --Nesting; return TOKEN( TRBRACE );
"["                     ++Nesting; return TOKEN( TLBRACKET );
"]"                     --Nesting; return TOKEN( TRBRACKET );

"+"                     return TOKEN( TPLUS );
"-"                     return TOKEN( TMINUS );
"*"                     return TOKEN( TMUL );
"/"                     return TOKEN( TDIV );
"^"                     return TOKEN( TPOW );

":"                     return TOKEN( TCOL );
"."                     return TOKEN( TDOT );
","                     return TOKEN( TCOMMA );

.                       std::cout<< "Unknown token at line: " << yylineno << "\n"; yyterminate();

<<EOF>>                 {
                            if( ! ProcessIndent( "" ) )
                            {
                                std::cout << "Indentation mis-match at line: " << yylineno << "\n";
                                yyterminate();
                            }
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

int ProcessIndent( const char* Line )
{
    if( Nesting )
        /* Ignore indents while nested. */
        return 0;

    unsigned int Level = SpaceCount( Line ) ;

    if( Level > 0 )
    {
        if( FirstIndent )
        {
            SpacePerIndent = Level;
            FirstIndent = false;
        }

        if( Level % SpacePerIndent != 0 )
            return -1;
    } 

    if( Level == Indent.top() )
    {
        if( ! First )
            return TOKEN( TEOL );

        First = false ;
        return 0;
    }
    else if( Level > Indent.top() )
    {
        Indent.push( Level );
        return TOKEN( INDENT );
    }
    else( Level < Indent.top() )
    {
        PreviousLevel = Level;

        Indent.pop();
        BEGIN DEDENT;
        return TOKEN( TDEDENT );
    }

    return 0;
}
