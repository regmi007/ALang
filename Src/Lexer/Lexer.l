%{
#include <stack>
#include <string>
#include <cstdlib>
#include <iostream>

#include "Parser/Ast.hpp"
#include "Parser/Parser.h"

#ifndef ALANG_DEBUG_LEXER
    #define TOKEN_STR_EMPTY     yylval.String = new std::string()
    #define TOKEN_STR_ALL       yylval.String = new std::string( yytext, yyleng )
    #define TOKEN_SUB_STR(t,l)  (yylval.String = new std::string(t,l))
    #define TOKEN(t)            (yylval.Token = t)
    
    // Dummy, do nothing. 
    #define PRINT_TOKEN(t,s)    (1 + 2)
#else
    #define TOKEN_STR_EMPTY
    #define TOKEN_STR_ALL
    #define TOKEN_SUB_STR
    #define TOKEN(t)            (t)
    #define PRINT_TOKEN(t,s)    (std::cout << t << ", " << s << "\n")
#endif

bool First       = true;
bool EndOfFile   = false;
bool FirstIndent = true;

unsigned int Nesting        = 0;
unsigned int SpacePerIndent = 0;
unsigned int PreviousLevel  = 0;
unsigned int CurrentLevel   = 0;

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

                            if( CurrentLevel < Indent.top() )
                            {
                                Indent.pop();

                                #ifdef ALANG_DEBUG_LEXER
                                    std::cout << "TDEDENT\n";
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

"Func"                  PRINT_TOKEN( "TFUNC", "" );    return TOKEN( TFUNC );
"Return"                PRINT_TOKEN( "TRETURN", "" );  return TOKEN( TRETURN );
"If"                    PRINT_TOKEN( "TIF", "" );      return TOKEN( TIF );
"Else"                  PRINT_TOKEN( "TELSE", "" );    return TOKEN( TELSE );
"Elif"                  PRINT_TOKEN( "TELIF", "" );    return TOKEN( TELIF );
"While"                 PRINT_TOKEN( "TWHILE", "" );   return TOKEN( TWHILE );

"\"".*"\""              {
                            PRINT_TOKEN( "TSTRING", yytext );
                            
                            if( yyleng > 2 )
                                TOKEN_SUB_STR(yytext+1,yyleng-2);
                            else
                                TOKEN_STR_EMPTY;

                            return TSTRING;
                        }

"'".*"'"                {
                            PRINT_TOKEN( "TSTRING", yytext );
                            
                            if( yyleng > 2 )
                                TOKEN_SUB_STR(yytext+1,yyleng-2);
                            else
                                TOKEN_STR_EMPTY;

                            return TSTRING;
                        }

[A-Za-z_][A-Za-z0-9_]*  PRINT_TOKEN( "TIDENTIFIER", yytext );    TOKEN_STR_ALL; return TIDENTIFIER;
[0-9]+\.[0-9]*{EXP}?    PRINT_TOKEN( "TDOUBLE", yytext );        TOKEN_STR_ALL; return TDOUBLE;
[0-9]+                  PRINT_TOKEN( "TINTEGER", yytext );       TOKEN_STR_ALL; return TINTEGER;

"="                     PRINT_TOKEN("TEQUAL",""); return TOKEN( TEQUAL );

"=="                    PRINT_TOKEN("TCEQ",""); return TOKEN( TCEQ );
"!="                    PRINT_TOKEN("TCNE",""); return TOKEN( TCNE );
"<"                     PRINT_TOKEN("TCLT",""); return TOKEN( TCLT );
"<="                    PRINT_TOKEN("TCLE",""); return TOKEN( TCLE );
">"                     PRINT_TOKEN("TCGT",""); return TOKEN( TCGT );
">="                    PRINT_TOKEN("TCGE",""); return TOKEN( TCGE );

"("                     PRINT_TOKEN("TLPAREN",""); ++Nesting; return TOKEN( TLPAREN );
")"                     PRINT_TOKEN("TRPAREN",""); --Nesting; return TOKEN( TRPAREN );
"{"                     PRINT_TOKEN("TLBRACE",""); ++Nesting; return TOKEN( TLBRACE );
"}"                     PRINT_TOKEN("TRBRACE",""); --Nesting; return TOKEN( TRBRACE );
"["                     PRINT_TOKEN("TLBRACKET",""); ++Nesting; return TOKEN( TLBRACKET );
"]"                     PRINT_TOKEN("TRBRACKET",""); --Nesting; return TOKEN( TRBRACKET );

"+"                     PRINT_TOKEN("TPLUS",""); return TOKEN( TPLUS );
"-"                     PRINT_TOKEN("TMINUS",""); return TOKEN( TMINUS );
"*"                     PRINT_TOKEN("TMUL",""); return TOKEN( TMUL );
"/"                     PRINT_TOKEN("TDIV",""); return TOKEN( TDIV );
"^"                     PRINT_TOKEN("TPOW",""); return TOKEN( TPOW );

":"                     PRINT_TOKEN("TCOLON",""); return TOKEN( TCOLON );
"."                     PRINT_TOKEN("TDOT",""); return TOKEN( TDOT );
","                     PRINT_TOKEN("TCOMMA",""); return TOKEN( TCOMMA );

.                       std::cout<< "Unknown token at line: " << yylineno << "\n"; yyterminate();

<DEDENT><<EOF>>         {
                            if( CurrentLevel < Indent.top() )
                            {
                                Indent.pop();

                                #ifdef ALANG_DEBUG_LEXER
                                    std::cout << "TDEDENT\n";
                                #endif

                                return TOKEN( TDEDENT );
                            }
                            else
                            {
                                EndOfFile = true;
                                BEGIN INITIAL;
                            }
                        }

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
                std::cout << "TEOL\n";
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
        CurrentLevel = Level;

        BEGIN DEDENT;
        #ifdef ALANG_DEBUG_LEXER
            std::cout << "TEOL\n";
        #endif
        return TOKEN( TEOL );

/*        
        PreviousLevel = Level;

        Indent.pop();
        BEGIN DEDENT;

        #ifdef ALANG_DEBUG_LEXER
            std::cout << "TDEDENT\n";
        #endif
        
        return TOKEN( TDEDENT );
*/
    }

    return TNOP;
}

#if defined( ALANG_DEBUG_LEXER )
int main( int Argc, char *Argv[] )
{
    Indent.push( 0 );
    
    FILE *Fp = nullptr;
    
    if( Argc == 2)
    {   
        FILE *Fp = fopen( Argv[1], "r" );

        if( !Fp )
        {
            perror( Argv[1]);
            return( 1 );
        }
        
        yyin = Fp;
    }

    while( yylex() );

    if( Fp != nullptr )
        fclose( Fp );
}
#endif
