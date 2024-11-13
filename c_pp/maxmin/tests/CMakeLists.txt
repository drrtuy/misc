# tests/CMakeLists.txt

# Включение тестирования
enable_testing()

# Поиск установленного Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Создание исполняемого файла для тестов
add_executable(HeapTests
    HeapTests.cpp
)

# Линкуем с библиотеками gtest и pthread (для Unix-систем)
target_link_libraries(HeapTests
    GTest::GTest
    GTest::Main
    pthread
)

# Добавление тестов
gtest_discover_tests(HeapTests)