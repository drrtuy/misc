#pragma once
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ratio>
#include <utility>
#include <vector>

template <typename CMP> class MinMaxHeap {
public:
  MinMaxHeap() : size_(0) { heap_.push_back(0); };
  ~MinMaxHeap(){};

  void siftUp() {
    size_t idx = heap_.size() - 1;

    int parent = heap_[idx / 2];
    int value = heap_.back();
    while (CMP{}(value, parent) && idx > 1) {
      std::swap(heap_[idx], heap_[idx / 2]);
      idx = idx / 2;
      parent = heap_[idx / 2];
    }
  }

  void siftDown() {
    if (heap_.size() == 3) {
      if (CMP{}(heap_[2], heap_[1])) {
        std::swap(heap_[1], heap_[2]);
      }
      return;
    }
    size_t idx = 1;
    size_t half = heap_.size() >> 1;
    while (idx < half) {
      size_t left = idx << 1;
      size_t right = left + 1;
      size_t appropriate = CMP{}(heap_[left], heap_[right]) ? left : right;
      if (CMP{}(heap_[idx], heap_[appropriate])) {
        break;
      }
      std::swap(heap_[idx], heap_[appropriate]);
      idx = appropriate;
    }
  }

  void insert(int value) {
    size_++;
    if (size_ == 1) {
      heap_.push_back(value);
      return;
    }

    heap_.push_back(value);
    // printHeap("Insert");
    siftUp();
    // printHeap("Insert2");
  }
  int extract() {
    if (size_ == 0) {
      throw std::out_of_range("Heap is empty");
    }

    // printHeap("Extract");
    int root = heap_[1];
    std::swap(heap_[1], heap_[heap_.size() - 1]);
    heap_.pop_back();
    siftDown();

    // printHeap("Extract2");
    size_--;
    return root;
  }
  int peek() { return heap_[1]; }
  bool isEmpty() { return !size_; }
  size_t size() { return size_; }

private:
  void printHeap(const std::string &msg) {
    std::cout << msg << " ";
    std::copy(heap_.begin(), heap_.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
  std::vector<int> heap_;
  size_t size_;
};