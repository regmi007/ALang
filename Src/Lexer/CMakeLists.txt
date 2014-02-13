ADD_CUSTOM_COMMAND(
    OUTPUT Lexer.cpp
    COMMAND ${FLEX_EXECUTABLE}
            --outfile=${FLEX_OUTPUT}
            Lexer.l
    COMMENT "Generating Lexer.cpp"
)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DALANG_DEBUG_LEXER" )
ADD_EXECUTABLE( ALang.lexer Lexer.cpp ${FLEX_LIBRARIES} )
