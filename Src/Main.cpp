#include <stack>
#include <stdio.h>

extern FILE *yyin;
extern int yyparse();
extern std::stack<int> Indent;

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


    yyparse();

    if( Fp != nullptr )
        fclose( Fp );
}
