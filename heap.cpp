#include "heap.hpp"
#include <iostream>

heap::heap() {}

heap::~heap() {}

void heap::heapify_up(int index) {
  if (index == 0)
    return;

  int parent = (index - 1) / 2;

  if (data[index].key > data[parent].key) {
    Element temp = data[index];
    data[index] = data[parent];
    data[parent] = temp;

    heapify_up(parent);
  }
}

void heap::heapify_down(int index) {
  int largest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int current_size = data.size();

  if (left < current_size && data[left].key > data[largest].key) {
    largest = left;
  }

  if (right < current_size && data[right].key > data[largest].key) {
    largest = right;
  }

  if (largest != index) {
    Element temp = data[index];
    data[index] = data[largest];
    data[largest] = temp;

    heapify_down(largest);
  }
}

void heap::insert(int value, int key) {
  data.push_back(Element{value, key});
  heapify_up(data.size() - 1);
}

Element heap::extract_max() {
  Element max_element = data[0];

  data[0] = data.back();
  data.pop_back();

  if (!data.empty()) {
    heapify_down(0);
  }

  return max_element;
}

Element heap::find_max() { return data[0]; }

int heap::return_size() { return data.size(); }

void heap::modify_key(int value, int key) {
  int current_size = data.size();
  for (int i = 0; i < current_size; i++) {
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

void heap::print() {
  int current_size = data.size();
  for (int i = 0; i < current_size; i++) {
    std::cout << "(" << data[i].value << ", " << data[i].key << ")\n";
  }
}
