#include <iostream>

//extern int yyparse();
extern int yylex();

int main( int Argc, char **Argv )
{
    Indent.push( 0 );

    yylex();
}

