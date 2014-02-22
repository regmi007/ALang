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

DtValue & DataType::SubScriptGet( const DtValue & Lhs, int Index )
{
    throw OperationError( "Operation not implemented." );
}

DtValue & DataType::SubScriptSet( DtValue & Lhs, int Index )
{
    throw OperationError( "Operation not implemented." );
}

void DataType::To_Stream( std::ostream & Out, const DtValue & Lhs )
{
    throw OperationError( "Operation not implemented." );
}

DataType DtNull;

DtValue::DtValue() : Data(), Type( & DtNull )
{
}

DtValue::DtValue( boost::any D, DataType *T ) : Data( D ), Type( T )
{
}

DtValue::DtValue( const DtValue & Src ) : Data( Src.Data ), Type( Src.Type )
{
//    this->Data = Src.Data;
//    this->Type = Src.Type;
}

DtValue DtValue::Size()
{
    return this->Type->Size( *this );
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

DtValue & DtValue::operator [] ( int Index ) const
{
    return this->Type->SubScriptGet( *this, Index );
}

DtValue & DtValue::operator [] ( int Index )
{
    return this->Type->SubScriptSet( *this, Index );
}

std::ostream & operator << ( std::ostream & Out, const DtValue & Val )
{
    Val.Type->To_Stream( Out, Val );
    return Out;
}
