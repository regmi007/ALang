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

    if( PVec->size() == 0 )
        std::cout << "\n";
    else
    	for( auto & Val : *PVec )
	    	std::cout << Val << "\n";

	return DtValue();
}

DtValue ALangXArray( Context & Ctx )
{
    return DtValue( DtValueVec() );
}

DtValue ALangXStruct( Context & Ctx )
{
    return DtValue( DtValueMap() );
}

void CreateBuiltInFunction( Context & Ctx )
{
 	ParameterList 	    P;
	NIdentifier         *I = nullptr;
	NFunctionDefinition *F = nullptr;

    // Creating Ast node for Print()
	P.push_back( new NIdentifier( *(  new std::string( "Argv" ) ) ) );
	I = new NIdentifier( *(  new std::string( "Print" ) ) );
	F = new NBuiltInFunctionDefinition( *I, P, ALangXPrint, 0 );
	F->Evaluate( Ctx );

    // Creating Ast node for Array()
    P.clear();
	I = new NIdentifier( *(  new std::string( "Array" ) ) );
	F = new NBuiltInFunctionDefinition( *I, P, ALangXArray, 1 );
	
    // Creating Ast node for Struct()
    P.clear();
	I = new NIdentifier( *(  new std::string( "Struct" ) ) );
	F = new NBuiltInFunctionDefinition( *I, P, ALangXStruct, 1 );
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
