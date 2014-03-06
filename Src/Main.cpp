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

using ALang::Ast::Context;
using ALang::Ast::NIdentifier;
using ALang::Ast::ParameterList;
using ALang::Ast::NFunctionDefinition;
using ALang::Ast::NBuiltInFunctionDefinition;

DtValue ALangXPrint( Context & Ctx )
{
	DtValueVec *PVec = boost::any_cast< DtValueVec >( & Ctx.Local[ "Argv" ].Data );
	
	for( auto & Val : *PVec )
		std::cout << Val << "\n";

	return DtValue();
}

void CreateBuiltInFunction( Context & Ctx )
{
	std::string *A = new std::string( "Argv" );
	std::string *N = new std::string( "Print" );
	
	ParameterList 	P { new NIdentifier( *A ) };

	NIdentifier *I = new NIdentifier( *N );
		
	NFunctionDefinition *F = new NBuiltInFunctionDefinition( *I, P, ALangXPrint, 0 );

	F->Evaluate( Ctx );
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

    DtValueMap Hash;
    Context Ctx( Hash, Hash );
    
    yyparse();

	CreateBuiltInFunction( Ctx );

    Program->Evaluate( Ctx );
    
    if( Fp != nullptr )
        fclose( Fp );
}
