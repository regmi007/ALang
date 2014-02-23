#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataType;

using ALang::Error::OperationError;

DtValue & DataType::Assign( DtValue & Lhs, const DtValue & Rhs )
{
    Lhs.Data = Rhs.Data;
    Lhs.Type = Rhs.Type;
    return Lhs;
}

DtValue DataType::Add( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "Operation not implemented." );
}

DtValue DataType::Substract( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "Operation not implemented." );
}

DtValue DataType::Multiply( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "Operation not implemented." );
}

DtValue DataType::Divide( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "Operation not implemented." );
}

DtValue DataType::Size( const DtValue & Lhs )
{
    throw OperationError( "Operation not implemented." );
}

DtValue & DataType::SubScriptGet( const DtValue & Lhs, std::size_t Index )
{
    throw OperationError( "Operation not implemented." );
}

DtValue & DataType::SubScriptSet( DtValue & Lhs, std::size_t Index )
{
    throw OperationError( "Operation not implemented." );
}

void DataType::ToStream( std::ostream & Out, const DtValue & Lhs )
{
    throw OperationError( "Operation not implemented." );
}

DataType DtNull;

DtValue::DtValue() : Data(), Type( & DtNull )
{
}

DtValue::DtValue( double Val ) : Data( Val ), Type( & DtDouble )
{
}

DtValue::DtValue( const char* Str ) : Data( std::string( Str )), Type( & DtString )
{
}

DtValue::DtValue( const std::string & Str ) : Data( Str ), Type( & DtString )
{
}

DtValue::DtValue( const std::vector<DtValue> & Arr ) : Data( Arr ), Type( & DtArray )
{
}

DtValue::DtValue( const DtValue & Src ) : Data( Src.Data ), Type( Src.Type )
{
}

DtValue DtValue::Size()
{
    return this->Type->Size( *this );
}

DtValue & DtValue::operator = ( double Val )
{
    this->Data = Val;
    this->Type = & DtDouble;
    return *this;
}

DtValue & DtValue::operator = ( const char* Str )
{
    this->Data = std::string( Str );
    this->Type = & DtString;
    return *this;
}

DtValue & DtValue::operator = ( const std::string & Str )
{
    this->Data = Str;
    this->Type = & DtString;
    return *this;
}

DtValue & DtValue::operator = ( const std::vector<DtValue> & Arr )
{
    this->Data = Arr;
    this->Type = & DtArray;
    return *this;
}

DtValue & DtValue::operator = ( const DtValue & Rhs )
{
    return this->Type->Assign( *this, Rhs );
}

DtValue DtValue::operator + ( const DtValue & Rhs )
{
    return this->Type->Add( *this, Rhs );
}

DtValue DtValue::operator - ( const DtValue & Rhs )
{
    return this->Type->Substract( *this, Rhs );
}

DtValue DtValue::operator * ( const DtValue & Rhs )
{
    return this->Type->Multiply( *this, Rhs );
}

DtValue DtValue::operator / ( const DtValue & Rhs )
{
    return this->Type->Divide( *this, Rhs );
}

DtValue & DtValue::operator [] ( std::size_t Index ) const
{
    return this->Type->SubScriptGet( *this, Index );
}

DtValue & DtValue::operator [] ( std::size_t Index )
{
    return this->Type->SubScriptSet( *this, Index );
}

std::ostream & operator << ( std::ostream & Out, const DtValue & Val )
{
    Val.Type->ToStream( Out, Val );
    return Out;
}
