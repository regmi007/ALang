SET( LIB_DATATYPE_SRC
    DataType.cpp
    DataTypeDouble.cpp
    DataTypeString.cpp
    DataTypeArray.cpp
    DataTypeStruct.cpp
)

ADD_LIBRARY( ALangDataType
    ${LIB_DATATYPE_SRC}
)
