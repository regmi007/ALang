#include <stdexcept>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeArray;

using ALang::Error::OperationError;

DtValue DataTypeArray::Add( const DtValue & Lhs, const DtValue & Rhs )
{
    const std::vector<DtValue> *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecRhs = boost::any_cast< const std::vector< DtValue >>( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const std::vector< DtValue >>( PData );        
    }

    const std::vector<DtValue> *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( PData );        
    }

    DtValue Val = std::vector< DtValue >();
    std::vector<DtValue> *PVecVal = boost::any_cast< std::vector< DtValue >>( & Val.Data );

    std::size_t Size = PVecLhs->size();

    for( std::size_t i = 0; i < Size; ++i )
        PVecVal->push_back( ( *PVecLhs )[ i ]);

    Size = PVecRhs->size();

    for( std::size_t i = 0; i < Size; ++i )
        PVecVal->push_back( ( *PVecRhs )[ i ]);
 
   return Val;
}

DtValue & DataTypeArray::AddAssign( DtValue & Lhs, const DtValue & Rhs )
{
    const std::vector<DtValue> *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecRhs = boost::any_cast< const std::vector< DtValue >>( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const std::vector< DtValue >>( PData );        
    }
    
    std::vector<DtValue> *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecLhs = boost::any_cast< std::vector< DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< std::vector< DtValue >>( PData );        
    }

    std::size_t Size = PVecRhs->size();

    for( std::size_t i = 0; i < Size; ++i )
        PVecLhs->push_back( ( *PVecRhs )[ i ]);

   return Lhs;
}

void DataTypeArray::ToStream( std::ostream & Out, const DtValue & Rhs )
{
    const std::vector<DtValue> *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecRhs = boost::any_cast< const std::vector< DtValue >>( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const std::vector< DtValue >>( PData );        
    }
    
    std::size_t Size = PVecRhs->size();

    Out << "[ ";
    for( std::size_t i = 0; i < Size; ++i )
    {
        Out << ( *PVecRhs )[ i ];

        if( i != Size - 1 )
            Out << ", ";
    }
    Out << " ]";
}

DtValue DataTypeArray::Size( const DtValue & Lhs )
{
    const std::vector<DtValue> *PVecLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( PData );        
    }

    DtValue Val = ( double ) PVecLhs->size();
    return Val;
}

DtValue & DataTypeArray::SubScriptGetIndex( const DtValue & Lhs, std::size_t Index )
{
    const std::vector<DtValue> *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const std::vector< DtValue >>( PData );        
    }
    
    return const_cast< std::vector< DtValue >* >( PVecLhs )->at( Index );
}

DtValue & DataTypeArray::SubScriptSetIndex( DtValue & Lhs, std::size_t Index )
{
    std::vector<DtValue> *PVecLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::vector<DtValue> ) )
        PVecLhs = boost::any_cast< std::vector< DtValue >>( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< std::vector< DtValue >>( PData );        
    }

    if( Index < PVecLhs->size() )
        return ( *PVecLhs )[ Index ];

    if( Index == PVecLhs->size() )
    {
        DtValue V;
        PVecLhs->push_back( V );
        return ( *PVecLhs )[ Index ];
    }

    PVecLhs->resize( Index + 1 );
    return ( *PVecLhs )[ Index ];
}

DataTypeArray DtArray;
