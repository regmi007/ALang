#include "Datatype.h"

void DataType_String:: m_MessageHandler( DataType_Message Msg, DataValue *Res, DataValue *Lhs, DataValue *Rhs )
{
    switch( Msg )
    {
        DataType_Message.MSG_INIT:
            Lhs->m_Data.Pointer = ( void * ) new std::string();
            break;
        DataType_Message.MSG_ADD:
            if( Rhs->m_Type != DtString )
                throw "Unsupported operation";
            
            *( (std::string*) Res->m_Data.Pointer ) = *( (std::string*) Lhs->m_Data.Pointer ) + *( (std::string*) Rhs->m_Data.Pointer );
            break;

        DataType_Message.MSG_ADD_ASSIGN:
            if( Rhs->m_Type != DtString )
                throw "Unsupported operation";

            *( (std::string*) Lhs->m_Data.Pointer ) += *( (std::string*) Rhs->m_Data.Pointer );
            break;

        default:
            throw "Unsupported Msg";
    };
}

DataType_String DtString;
