#include <stack>
#include <iostream>

//extern int yyparse();
extern int yylex();
extern std::stack<int> Indent;

int main( int Argc, char **Argv )
{
    Indent.push( 0 );

    yylex();
}

