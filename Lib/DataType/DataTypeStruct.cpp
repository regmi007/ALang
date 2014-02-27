#include <stdexcept>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DtValueMap;
using ALang::Dt::DataTypeStruct;

using ALang::Error::OperationError;

void DataTypeStruct::ToStream( std::ostream & Out, const DtValue & Rhs )
{
    const DtValueMap *PMapRhs = nullptr;

    if( Rhs.Data.type() == typeid( DtValueMap ))
        PMapRhs = boost::any_cast< const DtValueMap >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PMapRhs = boost::any_cast< const DtValueMap >( PData );        
    }

    std::size_t i = 0;
    Out << "{ ";
    for( auto Kv : *PMapRhs )
     {
        Out << "'" << Kv.first << "' : " << Kv.second;

        if( i < PMapRhs->size() - 1)
            Out << ", ";

        ++i;
    }
    Out << " }";
}

DtValue DataTypeStruct::Size( const DtValue & Lhs )
{
    const DtValueMap *PMapLhs = nullptr;

    if( Lhs.Data.type() == typeid( DtValueMap ))
        PMapLhs = boost::any_cast< const DtValueMap >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PMapLhs = boost::any_cast< const DtValueMap >( PData );        
    }

    DtValue Val = ( double ) PMapLhs->size();
    return Val;
}

DtValue & DataTypeStruct::SubScriptGetKey( const DtValue & Lhs, const std::string & Key )
{
    const DtValueMap *PMapLhs = nullptr;

    if( Lhs.Data.type() == typeid( DtValueMap ))
        PMapLhs = boost::any_cast< const DtValueMap >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PMapLhs = boost::any_cast< const DtValueMap >( PData );        
    }
   
    return const_cast< DtValueMap* >( PMapLhs )->at( Key );
}

DtValue & DataTypeStruct::SubScriptSetKey( DtValue & Lhs, const std::string & Key )
{
    DtValueMap *PMapLhs = nullptr;

    if( Lhs.Data.type() == typeid( DtValueMap ))
        PMapLhs = boost::any_cast< DtValueMap >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PMapLhs = boost::any_cast< DtValueMap >( PData );        
    }

    return ( *PMapLhs )[ Key ];
}

DataTypeStruct DtStruct;
