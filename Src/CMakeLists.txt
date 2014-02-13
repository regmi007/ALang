ADD_SUBDIRECTORY( Lexer )
ADD_SUBDIRECTORY( Parser )

SET( ALANG_SRC
    Lexer/Lexer.cpp
    Parser/Parser.cpp
    Main.cpp
)

ADD_EXECUTABLE( ALang ${ALANG_SRC} )
