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
    std::string *PLhs  = const_cast< std::string* >( boost::any_cast< std::string >( & Lhs.Data ));
    std::string *PRhs  = const_cast< std::string* >( boost::any_cast< std::string >( & Rhs.Data ));

    PVal->append( PLhs->c_str() );
    PVal->append( PRhs->c_str() );

    return Val;
}

void DataTypeString::To_Stream( std::ostream & Out, const DtValue & Rhs )
{
    std::string *Str  = const_cast< std::string* >( boost::any_cast< std::string >( & Rhs.Data ));
    Out << "'" << *Str << "'";
}

DtValue DataTypeString::Size( const DtValue & Lhs )
{
    std::string *Str  = const_cast< std::string* >( boost::any_cast< std::string >( & Lhs.Data ));
    DtValue Val = ( double ) Str->size();
    return Val;
}

DataTypeString DtString;
