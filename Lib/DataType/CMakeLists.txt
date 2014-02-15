SET( LIB_ALANG_DATATYPE_SRC
    DataType_Double.cpp,
    DataType_String.cpp,
    DataType_Array.cpp
)

ADD_LIBRARY( DATATYPE SHARED
    ${LIB_ALANG_DATATYPE_SRC}
)
