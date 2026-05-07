#include "Heap.hpp"
#include <iostream>
#include <cstdlib>

Heap::Heap() {}

Heap::~Heap() {}

void Heap::heapify_up(int index) {
  if (index == 0)
    return;

  int parent = (index - 1) / 2;

  if (data[index].key > data[parent].key) {
    std::swap(data[index], data[parent]);

    heapify_up(parent);
  }
}

void Heap::heapify_down(int index) {
  int largest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < data.size() && data[left].key > data[largest].key) {
    largest = left;
  }

  if (right < data.size() && data[right].key > data[largest].key) {
    largest = right;
  }

  if (largest != index) {
    std::swap(data[index], data[largest]);

    heapify_down(largest);
  }
}

void Heap::insert(int value, int key) {
  data.push_back(Element{value, key});
  heapify_up(data.size() - 1);
}

Element Heap::extract_max() {
  Element max_element = data[0];

  data[0] = data.back();
  data.pop_back();

  if (!data.empty()) {
    heapify_down(0);
  }

  return max_element;
}

Element Heap::find_max() { return data[0]; }

int Heap::return_size() { return data.size(); }

void Heap::modify_key(int value, int key) {
  for (int i = 0; i < data.size(); i++) {
    if (data[i].value == value) {
      int old_key = data[i].key;
      data[i].key = key;

      if (key > old_key) {
        heapify_up(i);
      } else if (key < old_key) {
        heapify_down(i);
      }
      break;
    }
  }
}

void Heap::print() {
  for (int i = 0; i < data.size(); i++) {
    std::cout << "(" << data[i].value << ", " << data[i].key << ") ";
  }
}
