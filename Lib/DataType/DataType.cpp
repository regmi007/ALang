#include "DataType.hpp"

using ALang::Dt::DtValue;
using ALang::Dt::DataType;

using ALang::Error::OperationError;

DtValue & DataType::Assign( DtValue & Lhs, const DtValue & Rhs )
{
    Lhs.Data = Rhs.Data;
    Lhs.Type = Rhs.Type;
    return Lhs;
}

DtValue & DataType::Assign( DtValue & Lhs, DtValue * Rhs )
{
    if( Rhs->Type != & DtString && Rhs->Type != & DtArray && Rhs->Type != & DtStruct )
        throw OperationError( "Addsrss asignment, Operation permited only for Rhs of type DtString, DtStruct and Dtarray." );

    Lhs.Data = & Rhs->Data;
    Lhs.Type = Rhs->Type;
    return Lhs;
}

DtValue DataType::Add( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "+, Operation not implemented." );
}

DtValue DataType::Substract( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "-, Operation not implemented." );
}

DtValue DataType::Multiply( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "*, Operation not implemented." );
}

DtValue DataType::Divide( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "/, Operation not implemented." );
}

DtValue & DataType::AddAssign( DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "+=, Operation not implemented." );
}

DtValue & DataType::SubstractAssign( DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "-=, Operation not implemented." );
}

DtValue & DataType::MultiplyAssign( DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "*=, Operation not implemented." );
}

DtValue & DataType::DivideAssign( DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "/=, Operation not implemented." );
}

bool DataType::LessThan( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "<, Operation not implemented." );
}

bool DataType::GreaterThan( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( ">, Operation not implemented." );
}

bool DataType::LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "<=, Operation not implemented." );
}

bool DataType::GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( ">=, Operation not implemented." );
}

bool DataType::EqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    throw OperationError( "==, Operation not implemented." );
}

DtValue DataType::Size( const DtValue & Lhs )
{
    throw OperationError( "Size(), Operation not implemented." );
}

DtValue & DataType::SubScriptGetIndex( const DtValue & Lhs, std::size_t Index )
{
    throw OperationError( "DtValue[ Index ], Operation not implemented." );
}

DtValue & DataType::SubScriptSetIndex( DtValue & Lhs, std::size_t Index )
{
    throw OperationError( "DtValue[ Index ], Operation not implemented." );
}

DtValue & DataType::SubScriptGetKey( const DtValue & Lhs, const std::string & Key )
{
    throw OperationError( "DtValue[ \"Key\" ],  Operation not implemented." );
}

DtValue & DataType::SubScriptSetKey( DtValue & Lhs, const std::string & Key )
{
    throw OperationError( "DtValue[ \"Key\" ], Operation not implemented." );
}

void DataType::ToStream( std::ostream & Out, const DtValue & Lhs )
{
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

DtValue::DtValue( const DtValueVec & Vec ) : Data( Vec ), Type( & DtArray )
{
}

DtValue::DtValue( const DtValueMap & Map ) : Data( Map ), Type( & DtStruct )
{
}

DtValue::DtValue( const DtValue & Src ) : Data( Src.Data ), Type( Src.Type )
{
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

DtValue & DtValue::operator = ( const DtValueVec & Vec )
{
    this->Data = Vec;
    this->Type = & DtArray;
    return *this;
}

DtValue & DtValue::operator = ( const DtValueMap & Map )
{
    this->Data = Map;
    this->Type = & DtStruct;
    return *this;
}

DtValue & DtValue::operator = ( const DtValue & Rhs )
{
    return this->Type->Assign( *this, Rhs );
}

DtValue & DtValue::operator = ( DtValue * Rhs )
{
    return this->Type->Assign( *this, Rhs );
}

DtValue DtValue::operator + ( const DtValue & Rhs ) const
{
    return this->Type->Add( *this, Rhs );
}

DtValue DtValue::operator - ( const DtValue & Rhs ) const
{
    return this->Type->Substract( *this, Rhs );
}

DtValue DtValue::operator * ( const DtValue & Rhs ) const
{
    return this->Type->Multiply( *this, Rhs );
}

DtValue DtValue::operator / ( const DtValue & Rhs ) const
{
    return this->Type->Divide( *this, Rhs );
}

DtValue & DtValue::operator += ( const DtValue & Rhs )
{
    return this->Type->AddAssign( *this, Rhs );
}

DtValue & DtValue::operator -= ( const DtValue & Rhs )
{
    return this->Type->SubstractAssign( *this, Rhs );
}

DtValue & DtValue::operator *= ( const DtValue & Rhs )
{
    return this->Type->MultiplyAssign( *this, Rhs );
}

DtValue & DtValue::operator /= ( const DtValue & Rhs )
{
    return this->Type->DivideAssign( *this, Rhs );
}

bool DtValue::operator < ( const DtValue & Rhs ) const
{
    return this->Type->LessThan( *this, Rhs );
}

bool DtValue::operator > ( const DtValue & Rhs ) const
{
    return this->Type->GreaterThan( *this, Rhs );
}

bool DtValue::operator <= ( const DtValue & Rhs ) const
{
    return this->Type->LessThanEqualTo( *this, Rhs );
}

bool DtValue::operator >= ( const DtValue & Rhs ) const
{
    return this->Type->GreaterThanEqualTo( *this, Rhs );
}

bool DtValue::operator == ( const DtValue & Rhs ) const
{
    return this->Type->EqualTo( *this, Rhs );
}

bool DtValue::operator != ( const DtValue & Rhs ) const
{
    return ! this->Type->EqualTo( *this, Rhs );
}

DtValue & DtValue::operator [] ( std::size_t Index ) const
{
    return this->Type->SubScriptGetIndex( *this, Index );
}

DtValue & DtValue::operator [] ( std::size_t Index )
{
    return this->Type->SubScriptSetIndex( *this, Index );
}

DtValue & DtValue::operator [] ( const std::string & Key ) const
{
    return this->Type->SubScriptGetKey( *this, Key );
}

DtValue & DtValue::operator [] ( const std::string & Key )
{
    return this->Type->SubScriptSetKey( *this, Key );
}

DtValue ALang::Dt::Size( const DtValue & Val ) 
{
    return Val.Type->Size( Val );
}

std::ostream & operator << ( std::ostream & Out, const DtValue & Val )
{
    Val.Type->ToStream( Out, Val );
    return Out;
}
