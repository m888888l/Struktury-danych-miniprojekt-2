#pragma once
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "Heap.hpp"
#include "PriorityArray.hpp"

class Benchmark{
    public:
    Benchmark();
    ~Benchmark();
    void run(const std::string &outputFilename = "wyniki_testow.csv");
    void fill_structure(int size, int seed, Base* structure);
    void writeResultToFile(std::ofstream &file, int size, const std::string &opName, int structure, const unsigned long long &time);
    Base* createStructure(int type);
};