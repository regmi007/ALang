#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeString;

using ALang::Error::OperationError;

/*
DtValue & DataTypeString::Assign( DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( std::string ) )
        throw OperationError( "Cannot assigh type other than DataTypeString." );

    Lhs.Data = Rhs.Data;
    return Lhs;
}
*/

DtValue DataTypeString::Add ( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( std::string ) )
        throw OperationError( "Cannot add type other than DataTypeString." );

    DtValue Val;
    Val.Data = boost::any_cast<std::string>( Lhs.Data ) + boost::any_cast<std::string>( Rhs.Data );
    Val.Type = Lhs.Type;
    return Val;
}

void DataTypeString::To_Stream( std::ostream & Out, const DtValue & Rhs )
{
    Out << "'" << boost::any_cast<std::string>( Rhs.Data ) << "'";
}

DtValue DataTypeString::Size( const DtValue & Lhs )
{
    DtValue Val;
    Val.Data = boost::any_cast<std::string>( Lhs.Data ).size();
    Val.Type = & DtDouble;
    return Val;
}

DataTypeString DtString;
