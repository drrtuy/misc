include_directories(/usr/include/lua5.3/)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -O3 -Wall")
add_executable(integral main.cpp)
target_link_libraries(integral lua5.3)
