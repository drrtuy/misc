project(ltl2ba)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


set(SRC lib/ltl.cpp
        #lib/test.cpp
        graph.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(ltl2ba ${SRC})
