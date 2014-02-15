#include "Datatype.h"

void DataType_Array:: m_MessageHandler( DataType_Message Msg, DataValue *Res, DataValue *Lhs, DataValue *Rhs )
{
    switch( Msg )
    {
        DataType_Message.MSG_INIT:
            std::vector< DataValue > *v = new std::vector< DataValue >;
            Lhs->m_Data.Pointer = (void *) v;
            break;

        DataType_Message.MSG_PUSH_BACK:
            ((std::vector<DataValue>*) Lhs->m_Data.Pointer)->push_back( *Rhs );
            break;

        DataType_Message.MSG_PUSH_BACK:
            ((std::vector<DataValue>*) Lhs->m_Data.Pointer)->push_back( *Rhs );
            break;

        DataType_Message.MSG_FREE:
            delete Lhs->m_Data.Pointer;
            break;

        default:
            throw "Unsupported Msg";
    };
}

DataType_Array DtArray;
