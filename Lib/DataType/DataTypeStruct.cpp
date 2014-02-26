#include <stdexcept>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeStruct;

using ALang::Error::OperationError;

void DataTypeStruct::ToStream( std::ostream & Out, const DtValue & Rhs )
{
    const std::unordered_map< std::string, DtValue > *PMapRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::unordered_map< std::string, DtValue > ))
        PMapRhs = boost::any_cast< const std::unordered_map< std::string, DtValue >>( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PMapRhs = boost::any_cast< const std::unordered_map< std::string, DtValue >>( PData );        
    }

    std::size_t i = 0;
    Out << "{ ";
    for( auto Kv : *PMapRhs )
     {
        Out << Kv.first << " : " << Kv.second;

        if( i < PMapRhs->size() - 1)
            Out << ", ";

        ++i;
    }
    Out << " }";
}

DtValue DataTypeStruct::Size( const DtValue & Lhs )
{
    const std::unordered_map< std::string, DtValue > *PMapLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::unordered_map< std::string, DtValue > ))
        PMapLhs = boost::any_cast< const std::unordered_map< std::string, DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PMapLhs = boost::any_cast< const std::unordered_map< std::string, DtValue >>( PData );        
    }

    DtValue Val = ( double ) PMapLhs->size();
    return Val;
}

/*
DtValue & DataTypeStruct::SubScriptGetKey( const DtValue & Lhs, const std::string & Key )
{
    const std::unordered_map< std::string, DtValue> *PMapLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( PData );        
    }
    
    return const_cast< std::vector< DtValue >* >( PVecLhs )->at( Index );
}*/

DtValue & DataTypeStruct::SubScriptSetKey( DtValue & Lhs, const std::string & Key )
{
    std::unordered_map< std::string, DtValue > *PMapLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::unordered_map< std::string, DtValue > ))
        PMapLhs = boost::any_cast< std::unordered_map< std::string, DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PMapLhs = boost::any_cast< std::unordered_map< std::string, DtValue >>( PData );        
    }

    ( *PMapLhs )[ Key ] = DtValue();
    return ( *PMapLhs )[ Key ];
}

DataTypeStruct DtStruct;
