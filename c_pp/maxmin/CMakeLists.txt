cmake_minimum_required(VERSION 3.14)
project(HeapProject VERSION 1.0 LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление поддиректорий
add_subdirectory(tests)

