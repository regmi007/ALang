#include <stdexcept>

#include "DataType.hpp"

using ALang::Dt::DtValue;
using ALang::Dt::DtValueVec;
using ALang::Dt::DataTypeArray;

using ALang::Error::OperationError;

DtValue DataTypeArray::Add( const DtValue & Lhs, const DtValue & Rhs )
{
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }

    const DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }

    DtValue Val = DtValueVec();
    DtValueVec *PVecVal = boost::any_cast< DtValueVec >( & Val.Data );

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
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }
    
    DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< DtValueVec >( PData );        
    }

    std::size_t Size = PVecRhs->size();

    for( std::size_t i = 0; i < Size; ++i )
        PVecLhs->push_back( ( *PVecRhs )[ i ]);

   return Lhs;
}

void DataTypeArray::ToStream( std::ostream & Out, const DtValue & Rhs )
{
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }
    
    std::size_t Size = PVecRhs->size();

    Out << "[ ";
    for( std::size_t i = 0; i < Size; ++i )
    {
        if( ( *PVecRhs )[ i ].Type == & DtString )
            Out << "'" << ( *PVecRhs )[ i ] << "'";
        else
            Out << ( *PVecRhs )[ i ];
            
        if( i != Size - 1 )
            Out << ", ";
    }
    Out << " ]";
}

DtValue DataTypeArray::Size( const DtValue & Lhs )
{
    const DtValueVec *PVecLhs = nullptr;

    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }

    DtValue Val = ( double ) PVecLhs->size();
    return Val;
}

DtValue & DataTypeArray::SubScriptGetIndex( const DtValue & Lhs, std::size_t Index )
{
    const DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }
    
    return const_cast< DtValueVec* > ( PVecLhs )->at( Index );
}

DtValue & DataTypeArray::SubScriptSetIndex( DtValue & Lhs, std::size_t Index )
{
    DtValueVec *PVecLhs = nullptr;

    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< DtValueVec >( PData );        
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

bool DataTypeArray::LessThan( const DtValue & Lhs, const DtValue & Rhs )
{
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }

    const DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }

    return ( *PVecLhs ) < ( *PVecRhs );
}

bool DataTypeArray::LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }

    const DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }

    return ( *PVecLhs ) <= ( *PVecRhs );
}

bool DataTypeArray::GreaterThan( const DtValue & Lhs, const DtValue & Rhs )
{
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }

    const DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }

    return ( *PVecLhs ) > ( *PVecRhs );
}

bool DataTypeArray::GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }

    const DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }

    return ( *PVecLhs ) >= ( *PVecRhs );
}

bool DataTypeArray::EqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    const DtValueVec *PVecRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( DtValueVec ) )
        PVecRhs = boost::any_cast< const DtValueVec >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PVecRhs = boost::any_cast< const DtValueVec >( PData );        
    }

    const DtValueVec *PVecLhs = nullptr;
    
    if( Lhs.Data.type() == typeid( DtValueVec ) )
        PVecLhs = boost::any_cast< const DtValueVec >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PVecLhs = boost::any_cast< const DtValueVec >( PData );        
    }

    return ( *PVecLhs ) == ( *PVecRhs );
}

DataTypeArray DtArray;
