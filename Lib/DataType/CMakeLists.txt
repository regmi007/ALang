SET( LIB_DATATYPE_SRC
    DataType.cpp
    DataTypeDouble.cpp
    DataTypeString.cpp
    DataTypeArray.cpp
    DataTypeStruct.cpp
    DataTypeAstNode.cpp
)

ADD_LIBRARY( ALangDataType SHARED ${LIB_DATATYPE_SRC} )
