SET( BISON_OUTPUT Parser/Parser.cpp )

ADD_CUSTOM_COMMAND(
    OUTPUT ${BISON_OUTPUT}
    COMMAND ${BISON_EXECUTABLE}
            --defines=${CMAKE_SOURCE_DIR}/Include/Parser/Parser.h
            --output=${BISON_OUTPUT}
            Parser/Parser.y
    COMMENT "Generating Parser.cpp"
)

SET( FLEX_OUTPUT Lexer/Lexer.cpp )

ADD_CUSTOM_COMMAND(
    OUTPUT ${FLEX_OUTPUT}
    COMMAND ${FLEX_EXECUTABLE}
          --outfile=${FLEX_OUTPUT}
          Lexer/Lexer.l
    COMMENT "Generating Lexer.cpp"
)

ADD_SUBDIRECTORY( Lexer )

SET( ALANG_SRC
    Main.cpp
    ${FLEX_OUTPUT}
    ${BISON_OUTPUT}
)

ADD_EXECUTABLE( ALang ${ALANG_SRC} )
