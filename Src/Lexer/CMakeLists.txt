# This need to be fixed.
ADD_CUSTOM_COMMAND(
    OUTPUT ${FLEX_OUTPUT}
    COMMAND ${FLEX_EXECUTABLE}
          --outfile=${FLEX_OUTPUT}
          ${CMAKE_SOURCE_DIR}/Src/Lexer/Lexer.l
    COMMENT "Generating Lexer.cpp"
)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DALANG_DEBUG_LEXER" )
ADD_EXECUTABLE( ALang.lexer ${FLEX_OUTPUT} )
