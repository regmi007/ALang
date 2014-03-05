SET( BISON_OUTPUT ${CMAKE_SOURCE_DIR}/Src/Parser/Parser.cpp )

ADD_CUSTOM_COMMAND(
    OUTPUT ${BISON_OUTPUT}
    COMMAND ${BISON_EXECUTABLE}
            --defines=${CMAKE_SOURCE_DIR}/Include/Parser/Parser.h
            --output=${BISON_OUTPUT}
            ${CMAKE_SOURCE_DIR}/Src/Parser/Parser.y
    COMMENT "Generating Parser.cpp"
)

SET( FLEX_OUTPUT ${CMAKE_SOURCE_DIR}/Src/Lexer/Lexer.cpp )

ADD_CUSTOM_COMMAND(
    OUTPUT ${FLEX_OUTPUT}
    COMMAND ${FLEX_EXECUTABLE}
          --outfile=${FLEX_OUTPUT}
          ${CMAKE_SOURCE_DIR}/Src/Lexer/Lexer.l
    COMMENT "Generating Lexer.cpp"
)

SET( ALANG_SRC
    Main.cpp
    
    ${FLEX_OUTPUT}
    ${BISON_OUTPUT}
    
    Parser/Ast.cpp
)

ADD_SUBDIRECTORY( Lexer )

ADD_EXECUTABLE( ALang ${ALANG_SRC} )
TARGET_LINK_LIBRARIES( ALang ALangDataType )
