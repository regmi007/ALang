#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeString;

using ALang::Error::OperationError;

DtValue DataTypeString::Add ( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( std::string ) )
        throw OperationError( "Cannot add type other than DataTypeString." );

    DtValue Val = std::string();

    std::string *PVal  = boost::any_cast< std::string >( & Val.Data );
    const std::string *PLhs  = boost::any_cast< const std::string >( & Lhs.Data );
    const std::string *PRhs  = boost::any_cast< const std::string >( & Rhs.Data );

    PVal->append( PLhs->c_str() );
    PVal->append( PRhs->c_str() );

    return Val;
}

DtValue & DataTypeString::AddAssign( DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( std::string ) )
        throw OperationError( "Cannot add type other than DataTypeString." );

    std::string *PLhs = boost::any_cast< std::string >( & Lhs.Data );
    const std::string *PRhs  = boost::any_cast< const std::string >( & Rhs.Data );

    PLhs->append( PRhs->c_str() );

    return Lhs;
}


void DataTypeString::ToStream( std::ostream & Out, const DtValue & Rhs )
{
    const std::string *Str = boost::any_cast< const std::string >( & Rhs.Data );
    Out << "'" << *Str << "'";
}

DtValue DataTypeString::Size( const DtValue & Lhs )
{
    const std::string *Str  = boost::any_cast< const std::string >( & Lhs.Data );
    DtValue Val = ( double ) Str->size();
    return Val;
}

DataTypeString DtString;
