%{
#include <stack>
#include <string>
#include <cstdlib>
#include <iostream>

#include "Parser.hpp"

#ifndef ALANG_DEBUG_LEXER
    #define TOKEN_STR_EMPTY yylval.String = new std::string()
    #define TOKEN_STR_ALL   yylval.String = new std::string( yytext, yyleng )
    #define TOKEN_SUB_STR(t,l) (yylval.String = new std::string(t,l))
    #define TOKEN(t) (yylval.Token = t)
    #define ECHO
#else
    #define TOKEN_STR_EMPTY
    #define TOKEN_STR_ALL
    #define TOKEN_SUB_STR
    #define TOKEN(t) (t)
    #define ECHO std::cout << yytext << "\n"
#endif

bool First       = true;
bool EndOfFile   = false;
bool FirstIndent = true;

unsigned int Nesting        = 0;
unsigned int SpacePerIndent = 0;
unsigned int PreviousLevel  = 0;

std::stack<unsigned int> Indent;

int ProcessIndent( const char* Line ) ;
%}

EXP	([Ee][-+]?[0-9]+)

%option noyywrap
%option yylineno

%x DEDENT

%%

<DEDENT>.|\n            {
                            yyless(0);

                            if( PreviousLevel < Indent.top() )
                            {
                                Indent.pop();

                                #ifdef ALANG_DEBUG_LEXER
                                    std::cout << "DEDENT\n";
                                #endif

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

                            if( Result != TNOP )
                                return Result;
                        }

[ \r\n]                 ;

"Func"                  ECHO; return TOKEN( TFUNC );
"Return"                ECHO; return TOKEN( TRETURN );
"If"                    ECHO; return TOKEN( TIF );
"Else"                  ECHO; return TOKEN( TELSE );
"Elif"                  ECHO; return TOKEN( TELIF );
"While"                 ECHO; return TOKEN( TWHILE );

"\"".*"\""              {
                            ECHO;
                            
                            if( yyleng > 2 )
                                TOKEN_SUB_STR(yytext+1,yyleng-2);
                            else
                                TOKEN_STR_EMPTY;

                            return TSTRING;
                        }

"'".*"'"                {
                            ECHO;
                            
                            if( yyleng > 2 )
                                TOKEN_SUB_STR(yytext+1,yyleng-2);
                            else
                                TOKEN_STR_EMPTY;

                            return TSTRING;
                        }

[A-Za-z_][A-Za-z0-9_]*  ECHO; TOKEN_STR_ALL; return TIDENTIFIER;
[0-9]+\.[0-9]*{EXP}?    ECHO; TOKEN_STR_ALL; return TDOUBLE;
[0-9]+                  ECHO; TOKEN_STR_ALL; return TINTEGER;

"="                     ECHO; return TOKEN( TEQUAL );

"=="                    ECHO; return TOKEN( TCEQ );
"!="                    ECHO; return TOKEN( TCNE );
"<"                     ECHO; return TOKEN( TCLT );
"<="                    ECHO; return TOKEN( TCLE );
">"                     ECHO; return TOKEN( TCGT );
">="                    ECHO; return TOKEN( TCGE );

"("                     ECHO; ++Nesting; return TOKEN( TLPAREN );
")"                     ECHO; --Nesting; return TOKEN( TRPAREN );
"{"                     ECHO; ++Nesting; return TOKEN( TLBRACE );
"}"                     ECHO; --Nesting; return TOKEN( TRBRACE );
"["                     ECHO; ++Nesting; return TOKEN( TLBRACKET );
"]"                     ECHO; --Nesting; return TOKEN( TRBRACKET );

"+"                     ECHO; return TOKEN( TPLUS );
"-"                     ECHO; return TOKEN( TMINUS );
"*"                     ECHO; return TOKEN( TMUL );
"/"                     ECHO; return TOKEN( TDIV );
"^"                     ECHO; return TOKEN( TPOW );

":"                     ECHO; return TOKEN( TCOLON );
"."                     ECHO; return TOKEN( TDOT );
","                     ECHO; return TOKEN( TCOMMA );

.                       std::cout<< "Unknown token at line: " << yylineno << "\n"; yyterminate();

<<EOF>>                 {
                            if( EndOfFile )
                                return 0;

                            int Result = ProcessIndent( "" );

                            if( Result == -1  )
                            {
                                std::cout << "Indentation mis-match at line: " << yylineno << "\n";
                                yyterminate();
                            }

                            if( Result != TNOP )
                            {
                                EndOfFile = true;
                                return Result;
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
    {
        /* Ignore indents while nested. */
        return TNOP;
    }

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
        {
            #ifdef ALANG_DEBUG_LEXER
                std::cout << "EOL\n";
            #endif
        
            return TOKEN( TEOL );
        }

        First = false ;
        return TNOP;
    }
    else if( Level > Indent.top() )
    {
        Indent.push( Level );
        
        #ifdef ALANG_DEBUG_LEXER
            std::cout << "INDENT\n";
        #endif

        return TOKEN( TINDENT );
    }
    else
    {
        PreviousLevel = Level;

        Indent.pop();
        BEGIN DEDENT;
        
        #ifdef ALANG_DEBUG_LEXER
            std::cout << "DEDENT\n";
        #endif
        
        return TOKEN( TDEDENT );
    }

    return TNOP;
}

#if defined( ALANG_DEBUG_LEXER )
int main()
{
    Indent.push( 0 );

    while( yylex() );

    return 0;
}
#endif
