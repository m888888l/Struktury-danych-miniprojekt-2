#pragma once

class heap {
public:
  void insert(int index, int priority);
  void extractMax();
  void findMax();
  void modifyKey(int index, int priority);
  void returnSize();

private:
  void heapify();
};
