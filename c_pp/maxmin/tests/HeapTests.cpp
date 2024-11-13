
#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include "../MinMaxHeap.h" // Путь к вашему заголовочному файлу MinHeap

// Тестовый набор для MinHeap
TEST(MinHeapTest, IsEmptyInitially) {
    EXPECT_EQ(42, 42);
    MinMaxHeap<std::less<int>> heap;
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(heap.size(), 0);
}

TEST(MinHeapTest, InsertSingleElement) {
    MinMaxHeap<std::less<int>> heap;
    heap.insert(10);
    EXPECT_FALSE(heap.isEmpty());
    EXPECT_EQ(heap.size(), 1);
    EXPECT_EQ(heap.peek(), 10);
}

TEST(MinHeapTest, InsertMultipleElements) {
    MinMaxHeap<std::less<int>> heap;
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(30);
    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.peek(), 5); // Наименьший элемент
}

// TEST(MinHeapTest, ExtractElementsInOrder) {
//     MinMaxHeap<std::less<int>> heap;
//     std::vector<int> elements = {20, 5, 15, 30, 10};
//     for(auto el : elements) {
//         heap.insert(el);
//     }

//     std::vector<int> expected = {5, 10, 15, 20, 30};
//     for(auto expected_el : expected) {
//         EXPECT_EQ(heap.extract(), expected_el);
//     }
//     EXPECT_TRUE(heap.isEmpty());
// }

TEST(MinHeapTest, HandleDuplicates) {
    MinMaxHeap<std::less<int>> heap;
    heap.insert(10);
    heap.insert(10);
    heap.insert(5);
    heap.insert(5);
    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.extract(), 5);
    EXPECT_EQ(heap.extract(), 5);
    EXPECT_EQ(heap.extract(), 10);
    EXPECT_EQ(heap.extract(), 10);
    EXPECT_TRUE(heap.isEmpty());
}

TEST(MinHeapTest, PeekDoesNotRemoveElement) {
    MinMaxHeap<std::less<int>> heap;
    heap.insert(10);
    heap.insert(5);
    EXPECT_EQ(heap.peek(), 5);
    EXPECT_EQ(heap.size(), 2);
    EXPECT_EQ(heap.extract(), 5);
    EXPECT_EQ(heap.peek(), 10);
    EXPECT_EQ(heap.size(), 1);
}

TEST(MinHeapTest, ExtractFromEmptyHeap) {
    MinMaxHeap<std::less<int>> heap;
    EXPECT_TRUE(heap.isEmpty());
    // Предполагается, что извлечение из пустой кучи бросает исключение
    EXPECT_THROW(heap.extract(), std::out_of_range);
}

// Тестовый набор для MaxHeap
TEST(MaxHeapTest, IsEmptyInitially) {
    MinMaxHeap<std::greater<int>> heap;
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(heap.size(), 0);
}

TEST(MaxHeapTest, InsertSingleElement) {
    MinMaxHeap<std::greater<int>> heap;
    heap.insert(10);
    EXPECT_FALSE(heap.isEmpty());
    EXPECT_EQ(heap.size(), 1);
    EXPECT_EQ(heap.peek(), 10);
}

TEST(MaxHeapTest, InsertMultipleElements) {
    MinMaxHeap<std::greater<int>> heap;
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(30);
    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.peek(), 30); // Наибольший элемент
}

TEST(MaxHeapTest, ExtractElementsInOrder) {
    MinMaxHeap<std::greater<int>> heap;
    std::vector<int> elements = {20, 5, 15, 30, 10};
    for(auto el : elements) {
        heap.insert(el);
    }

    std::vector<int> expected = {30, 20, 15, 10, 5};
    for(auto expected_el : expected) {
        EXPECT_EQ(heap.extract(), expected_el);
    }
    EXPECT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, HandleDuplicates) {
    MinMaxHeap<std::greater<int>> heap;
    heap.insert(10);
    heap.insert(10);
    heap.insert(20);
    heap.insert(20);
    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.extract(), 20);
    EXPECT_EQ(heap.extract(), 20);
    EXPECT_EQ(heap.extract(), 10);
    EXPECT_EQ(heap.extract(), 10);
    EXPECT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, PeekDoesNotRemoveElement) {
    MinMaxHeap<std::greater<int>> heap;
    heap.insert(10);
    heap.insert(20);
    EXPECT_EQ(heap.peek(), 20);
    EXPECT_EQ(heap.size(), 2);
    EXPECT_EQ(heap.extract(), 20);
    EXPECT_EQ(heap.peek(), 10);
    EXPECT_EQ(heap.size(), 1);
}

TEST(MaxHeapTest, ExtractFromEmptyHeap) {
    MinMaxHeap<std::greater<int>> heap;
    EXPECT_TRUE(heap.isEmpty());
    // Предполагается, что извлечение из пустой кучи бросает исключение
    EXPECT_THROW(heap.extract(), std::out_of_range);
}

// Дополнительные Тесты (Опционально)

// Тестирование с отрицательными числами
TEST(MinHeapTest, InsertNegativeNumbers) {
    MinMaxHeap<std::less<int>> heap;
    heap.insert(-10);
    heap.insert(-20);
    heap.insert(0);
    EXPECT_EQ(heap.size(), 3);
    EXPECT_EQ(heap.peek(), -20);
    EXPECT_EQ(heap.extract(), -20);
    EXPECT_EQ(heap.extract(), -10);
    EXPECT_EQ(heap.extract(), 0);
    EXPECT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, InsertNegativeNumbers) {
    MinMaxHeap<std::greater<int>> heap;
    heap.insert(-10);
    heap.insert(-20);
    heap.insert(0);
    EXPECT_EQ(heap.size(), 3);
    EXPECT_EQ(heap.peek(), 0);
    EXPECT_EQ(heap.extract(), 0);
    EXPECT_EQ(heap.extract(), -10);
    EXPECT_EQ(heap.extract(), -20);
    EXPECT_TRUE(heap.isEmpty());
}

// Тестирование с большим количеством элементов
TEST(MinHeapTest, LargeNumberOfElements) {
    MinMaxHeap<std::less<int>> heap;
    const int N = 20;
    for(int i = N; i >=1; --i) {
        heap.insert(i);
    }
    auto prev = std::numeric_limits<int>::min();
    EXPECT_EQ(heap.size(), N);
    for(int i =1; i <=N; ++i) {
        auto current = heap.extract();
        EXPECT_LE(prev, current);
        prev = current;
    }
    EXPECT_TRUE(heap.isEmpty());
}

TEST(MaxHeapTest, LargeNumberOfElements) {
    MinMaxHeap<std::greater<int>> heap;
    const int N = 1000;
    for(int i =1; i <=N; ++i) {
        heap.insert(i);
    }
    EXPECT_EQ(heap.size(), N);
    for(int i =N; i >=1; --i) {
        EXPECT_EQ(heap.extract(), i);
    }
    EXPECT_TRUE(heap.isEmpty());
}