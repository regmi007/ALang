ADD_CUSTOM_COMMAND(
    OUTPUT Parser.cpp
    COMMAND ${BISON_EXECUTABLE}
            --defines=${CMAKE_SOURCE_DIR}/Include/Parser.h
            --output=Parser.cpp
            Parser.y
    COMMENT "Generating Parser.cpp"
)
