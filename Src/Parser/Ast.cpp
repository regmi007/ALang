#include <iostream>

#include "Parser/Ast.hpp"

using ALang::Ast::Node;
using ALang::Ast::NBlock;
using ALang::Ast::NDouble;
using ALang::Ast::NString;
using ALang::Ast::NInteger;
using ALang::Ast::NIdentifier;
using ALang::Ast::NAssignment;
using ALang::Ast::NFunctionCall;
using ALang::Ast::NExpressionStatement;
using ALang::Ast::NUserFunctionDefinition;
using ALang::Ast::NBuiltInFunctionDefinition;

using ALang::Dt::DtValue;
using ALang::Dt::DtValueVec;
using ALang::Dt::DtValueMap;

DtValue NBlock::Evaluate( DtValueMap & Context )
{
	DtValue Ret;
	
	for( auto Stmt : this->Statements )
	    Ret = Stmt->Evaluate( Context );
	    
	return Ret;
}

DtValue NExpressionStatement::Evaluate( DtValueMap & Context )
{
	return this->Expression.Evaluate( Context );
}

DtValue NDouble::Evaluate( DtValueMap & Context )
{
	return DtValue( this->Val );
}

DtValue NInteger::Evaluate( DtValueMap & Context )
{
	return DtValue( this->Val );
}

DtValue NString::Evaluate( DtValueMap & Context )
{
	return DtValue( this->Val );
}

DtValue NIdentifier::Evaluate( DtValueMap & Context )
{
	try
    {
		return Context.at( this->Val );
	}
	catch( std::out_of_range & E )
	{
		std::cout << "Undefined variable " << this->Val << "\n";
		throw;
	}
}

DtValue NAssignment::Evaluate( DtValueMap & Context )
{	
	Context[ this->Identifier.Val ] =  this->Rhs.Evaluate( Context );

    return DtValue();
}

DtValue NFunctionCall::Evaluate( DtValueMap & Context )
{	
	NFunctionDefinition *PNodeFunc = nullptr;
	
    try
    {
		DtValue & Func = Context.at( this->Identifier.Val );
		PNodeFunc = boost::any_cast< NFunctionDefinition* >( Func.Data );
	}
	catch( std::out_of_range & E )
	{
		std::cout << "Undefined function " << this->Identifier.Val << "().\n";
		throw;
	}

	DtValueMap Local;

	if( PNodeFunc->ArgsType == 0 )
	{
		DtValue V = DtValueVec();
		
		Local[ PNodeFunc->Arguments[ 0 ]->Val ] = V;
		
		for( std::size_t i = 0; i < this->ExpList.size(); ++i )
		{
			Local[ PNodeFunc->Arguments[ 0 ]->Val ][ i ] = this->ExpList[ i ]->Evaluate( Context );
		}	
	}
	else
	{
		if( PNodeFunc->Arguments.size() != this->ExpList.size() )
			throw "Argument length not matched with function defination\n.";
			
		for( std::size_t i = 0; i < this->ExpList.size(); ++i )
		{
			Local[ PNodeFunc->Arguments[ i ]->Val ] = this->ExpList[ i ]->Evaluate( Context );
		}	
	}
	
	return PNodeFunc->Call( Local );
}

DtValue NUserFunctionDefinition::Evaluate( DtValueMap & Context )
{
	DtValue NFunc;
	NFunc.Data = ( NFunctionDefinition* ) this;
	NFunc.Type = & DtALangNode;

	return Context[ this->Identifier.Val ] = NFunc;
}

DtValue NUserFunctionDefinition::Call( DtValueMap & Context )
{
	return this->Block.Evaluate( Context );
}

DtValue NBuiltInFunctionDefinition::Evaluate( DtValueMap & Context )
{
	DtValue NFunc;
	NFunc.Data = ( NFunctionDefinition* ) this;
	NFunc.Type = & DtALangNode;

	return Context[ this->Identifier.Val ] = NFunc;
}

DtValue NBuiltInFunctionDefinition::Call( DtValueMap & Context )
{
	return this->Function( Context );
}
