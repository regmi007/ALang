CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( ALang )

# The version number.
SET( ALang_VERSION_MAJOR 1 )
SET( ALang_VERSION_MINOR 0 )

# set all the required variables above this point
# so that it can be override through CMake.vars
INCLUDE( CMake.vars OPTIONAL )

INCLUDE_DIRECTORIES ("${PROJECT_SOURCE_DIR}/Include")

SET( CMAKE_MODULE_PATH "CMakeFiles/Modules" ${CMAKE_MODULE_PATH} )

SET( CMAKE_CXX_FLAGS "-fPIC -std=c++11" )

IF( DEBUG )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Wall" )
ELSE
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2" )
ENDIF()

FIND_PACKAGE( Boost REQUIRED COMPONENTS regex )

INCLUDE_DIRECTORIES( "${Boost_INCLUDE_DIRS}" )

MESSAGE( STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}" )
MESSAGE( STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}" )

FIND_PACKAGE( BISON REQUIRED )

SET( BISON_OUTPUT ${CMAKE_SOURCE_DIR}/Src/Parser/Parser.cpp )

#ADD_CUSTOM_COMMAND(
#    OUTPUT ${BISON_OUTPUT}
#    COMMAND ${BISON_EXECUTABLE}
#          --defines=${CMAKE_SOURCE_DIR}/Include/Parser.h
#          --output=${BISON_OUTPUT}
#          ${CMAKE_SOURCE_DIR}/Src/Parser/Parser.y
#    COMMENT "Generating Parser.cpp"
#)

FIND_PACKAGE( FLEX REQUIRED )

SET( FLEX_OUTPUT ${CMAKE_SOURCE_DIR}/Src/Lexer/Lexer.cpp )

ADD_CUSTOM_COMMAND(
    OUTPUT ${FLEX_OUTPUT}
    COMMAND ${FLEX_EXECUTABLE}
          --outfile=${FLEX_OUTPUT}
          ${CMAKE_SOURCE_DIR}/Src/Lexer/Lexer.l
    COMMENT "Generating Lexer.cpp"
)

SET( ALANG_SRC
    ${FLEX_OUTPUT}
#    ${BISON_OUTPUT}
    Main.cpp
)

ADD_EXECUTABLE( ALang ${ALANG_SRC} )

