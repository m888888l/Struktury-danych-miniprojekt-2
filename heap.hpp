#pragma once
#include "Base.hpp"
#include <vector>

class heap : public Base {
public:
  heap();
  ~heap();

  void insert(int value, int key);
  Element extract_max();
  Element find_max();
  int return_size();
  void modify_key(int value, int key);
  void print();

private:
  void heapify_up(int index);
  void heapify_down(int index);
  std::vector<Element> data;
};
