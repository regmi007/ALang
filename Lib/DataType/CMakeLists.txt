SET( LIB_DATATYPE_SRC
    DataType.cpp
    DataTypeDouble.cpp
    DataTypeString.cpp
    DataTypeArray.cpp
)

ADD_LIBRARY( DataType
    ${LIB_DATATYPE_SRC}
)
