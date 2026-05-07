#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include "Heap.hpp"
#include "PriorityArray.hpp"

class Menu{
    public:
    Menu();
    ~Menu();

    void menu();
    void loadFromFile(std::string fileName, char separator, Base* structure);

};