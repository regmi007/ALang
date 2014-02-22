SET( LIB_DATATYPE_SRC
    DataType.cpp
    DataTypeDouble.cpp
    DataTypeString.cpp
    DataTypearray.cpp
)

ADD_LIBRARY( DataType
    ${LIB_DATATYPE_SRC}
)
