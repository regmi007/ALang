#include <stack>
#include <iostream>
#include <stdio.h>

#include "Parser/Ast.hpp"

extern FILE *yyin;
extern int yyparse();
extern std::stack< int > Indent;

extern ALang::Ast::NBlock *Program;

using ALang::Dt::DtValue;
using ALang::Dt::DtValueMap;
using ALang::Dt::DtValueVec;

using ALang::Ast::NIdentifier;
using ALang::Ast::ParameterList;
using ALang::Ast::NFunctionDefinition;
using ALang::Ast::NBuiltInFunctionDefinition;

DtValue ALangXPrint( DtValueMap & Context )
{
	DtValueVec *PVec = boost::any_cast< DtValueVec >( & Context[ "Argv" ].Data );
	
	for( auto & Val : *PVec )
		std::cout << Val << "\n";

	return DtValue();
}

void CreateBuiltInFunction( DtValueMap & Context )
{
	ParameterList 	P { new NIdentifier( "Argv" ) };

	NIdentifier *I = new NIdentifier( "Print" );
		
	NFunctionDefinition *F = new NBuiltInFunctionDefinition( *I, P, ALangXPrint, 0 );

	F->Evaluate( Context );
}

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

    DtValueMap Context;
    
    yyparse();

	CreateBuiltInFunction( Context );

    Program->Evaluate( Context );
    
    if( Fp != nullptr )
        fclose( Fp );
}
