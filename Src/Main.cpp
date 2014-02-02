#include <stack>

extern int yyparse();
extern std::stack<int> Indent;

int main( int Argc, char **Argv )
{
    Indent.push( 0 );

    yyparse();
}

