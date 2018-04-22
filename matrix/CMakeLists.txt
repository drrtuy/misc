CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(MATRIX_CLI_SRC operand.cpp operation.cpp matrix-cli.cpp)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=gnu++11)

add_executable(matrix-cli ${MATRIX_CLI_SRC})
install(TARGETS matrix-cli DESTINATION ./)
