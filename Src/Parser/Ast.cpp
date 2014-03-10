#include <iostream>

#include "Parser/Ast.hpp"

using ALang::Ast::Node;
using ALang::Ast::NBlock;
using ALang::Ast::NDouble;
using ALang::Ast::NString;
using ALang::Ast::NInteger;
using ALang::Ast::NIdentifier;
using ALang::Ast::NAssignment;
using ALang::Ast::NForStatement;
using ALang::Ast::NFunctionCall;
using ALang::Ast::NArrayDefination;
using ALang::Ast::NReturnStatement;
using ALang::Ast::NExpressionStatement;
using ALang::Ast::NUserFunctionDefinition;
using ALang::Ast::NBuiltInFunctionDefinition;
using ALang::Ast::NReturnExpressionStatement;

using ALang::Dt::DtValue;
using ALang::Dt::DtValueVec;
using ALang::Dt::DtValueMap;

DtValue NBlock::Evaluate( Context & Ctx )
{
	DtValue Ret;
    
	for( auto Stmt : this->Statements )
    {
	    Ret = Stmt->Evaluate( Ctx );
        
        if( Stmt->Type == StatementType::RETURN )
            return Ret;
    }

	return Ret;
}

DtValue NExpressionStatement::Evaluate( Context & Ctx )
{
	return this->Expression.Evaluate( Ctx );
}

DtValue NReturnStatement::Evaluate( Context & Ctx )
{
	return DtValue();
}

DtValue NReturnExpressionStatement::Evaluate( Context & Ctx )
{
	return this->Expression.Evaluate( Ctx );
}

DtValue NDouble::Evaluate( Context & Ctx )
{
	return DtValue( this->Val );
}

DtValue NInteger::Evaluate( Context & Ctx )
{
	return DtValue( this->Val );
}

DtValue NString::Evaluate( Context & Ctx )
{
	return DtValue( this->Val );
}

DtValue NIdentifier::Evaluate( Context & Ctx )
{
	try
    {
		return Ctx.Local.at( this->Val );
	}
	catch( std::out_of_range & E )
	{
		std::cout << "Undefined variable " << this->Val << "\n";
		throw;
	}
}

DtValue NAssignment::Evaluate( Context & Ctx )
{	
	return Ctx.Local[ this->Identifier.Val ] =  this->Rhs.Evaluate( Ctx );
}

DtValue NFunctionCall::Evaluate( Context & Ctx )
{	
	NFunctionDefinition *PNodeFunc = nullptr;
	
    try
    {
		DtValue & Func = Ctx.Local.at( this->Identifier.Val );
		PNodeFunc = boost::any_cast< NFunctionDefinition* >( Func.Data );
	}
	catch( std::out_of_range & E )
	{
        try
        {
		    DtValue & Func = Ctx.Global.at( this->Identifier.Val );
		    PNodeFunc = boost::any_cast< NFunctionDefinition* >( Func.Data );
        }
        catch( std::out_of_range & E )
        {
		    std::cout << "Undefined function " << this->Identifier.Val << "().\n";
		    throw;
        }
	}

	DtValueMap Local;
    Context NewCtx( Local, Ctx.Global );

	if( PNodeFunc->ArgsType == ArgumentType::VARIABLE_LENGTH )
	{
		DtValue V = DtValueVec();
		
		Local[ PNodeFunc->Arguments[ 0 ]->Val ] = V;
		
		for( std::size_t i = 0; i < this->ExpList.size(); ++i )
		{
			Local[ PNodeFunc->Arguments[ 0 ]->Val ][ i ] = this->ExpList[ i ]->Evaluate( Ctx );
		}
	}
	else
	{
		if( PNodeFunc->Arguments.size() != this->ExpList.size() )
			throw "Argument length not matched with function defination\n.";
			
		for( std::size_t i = 0; i < this->ExpList.size(); ++i )
		{
			Local[ PNodeFunc->Arguments[ i ]->Val ] = this->ExpList[ i ]->Evaluate( Ctx );
		}	
	}
	
	return PNodeFunc->Call( NewCtx );
}

DtValue NUserFunctionDefinition::Evaluate( Context & Ctx )
{
	DtValue NFunc;
	NFunc.Data = ( NFunctionDefinition* ) this;
	NFunc.Type = & DtAstNode;

	return Ctx.Local[ this->Identifier.Val ] = NFunc;
}

DtValue NUserFunctionDefinition::Call( Context & Ctx )
{
	return this->Block.Evaluate( Ctx );
}

DtValue NBuiltInFunctionDefinition::Evaluate( Context & Ctx )
{
	DtValue NFunc;
	NFunc.Data = ( NFunctionDefinition* ) this;
	NFunc.Type = & DtAstNode;

	return Ctx.Local[ this->Identifier.Val ] = NFunc;
}

DtValue NBuiltInFunctionDefinition::Call( Context & Ctx )
{
	return this->Function( Ctx );
}

DtValue NArrayDefination::Evaluate( Context & Ctx )
{
	DtValueVec Vec;
	
	for( auto & Val : this->ExpList )
	{
		Vec.push_back( Val->Evaluate( Ctx ) );
	}
	
	return DtValue( Vec );
}

DtValue NForStatement::Evaluate( Context & Ctx )
{
    DtValue Res = this->Expression.Evaluate( Ctx );

    if( Res.Type != & DtArray )
    {
        std::cout << "You should not try iterating none-iterable type.\n";
        throw std::string( "Should fix with some exception type" );
    }

    Ctx.Local[ this->Identifier.Val ] = DtValue();

    DtValueVec *PVecRes = nullptr;

    PVecRes = boost::any_cast< DtValueVec >( & Res.Data );

    for( auto & V : *PVecRes )
    {
        if( V.Type != & DtDouble )
            Ctx.Local[ this->Identifier.Val ] = & V;
        else
            Ctx.Local[ this->Identifier.Val ] = V;

        this->Block.Evaluate( Ctx );
    }

    return DtValue();
}
