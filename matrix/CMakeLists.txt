cmake_minimum_required(VERSION 2.6)

add_custom_command(
    OUTPUT parser.tab.cpp lex.tab.cpp
    COMMAND bison -d parser.ypp
    COMMAND flex -o lex.tab.cpp scanner.lpp
    WORKING_DIRECTORY ./
    DEPENDS parser.ypp scanner.lpp
)

add_custom_target(lexer DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lex.tab.cpp)
add_custom_target(parser DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser.tab.cpp)

set(MATRIX_CLI_SRC matrix.cpp expression.cpp operand.cpp operation.cpp lex.tab.cpp parser.tab.cpp matrix-cli.cpp)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=gnu++11)


add_executable(matrix-cli ${MATRIX_CLI_SRC})

add_dependencies(lexer parser)

install(TARGETS matrix-cli DESTINATION ./)
