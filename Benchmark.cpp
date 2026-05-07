#include "Benchmark.hpp"

using namespace std;
using namespace std::chrono;

const vector<int> SIZES = {100, 200, 300, 400, 500, 600, 700, 800};
const int SAMPLES = 100;

Benchmark::Benchmark(){};
Benchmark::~Benchmark(){};

void Benchmark::writeResultToFile(ofstream &file, int size, const string &opName, int structure, const unsigned long long &time) {
    std::string structure_name;
    if(structure == 0) structure_name = "Heap";
    else if(structure == 1) structure_name = "Array";
    file << size << ";" << opName << ";" << structure_name << ";" << time << "\n";
}

Base* Benchmark::createStructure(int type) {
    if (type == 0) return new Heap();
    if (type == 1) return new PriorityArray();
    return nullptr;
}

void Benchmark::fill_structure(int size, int seed, Base* structure){
    mt19937 gen(seed);
    uniform_int_distribution<> dist_values(0, 100000000);
    uniform_int_distribution<> dist_keys(0, size * 4);
    for(int i = 0; i < size; i++) structure->insert(dist_values(gen), dist_keys(gen));
}

void Benchmark::run(const std::string &outputFilename){ 
    ofstream file(outputFilename);
    file << "Rozmiar;Operacja;Struktura;czas[ns]\n";

    auto start = high_resolution_clock::now();
    auto end = start;

    vector<Base*> structures;
    structures.reserve(SAMPLES);

    for(int i = 0; i < 2; i++){//przechodzi po strukturach
        for(int size : SIZES){
            mt19937 gen(0);
            uniform_int_distribution<> dist_value(0, 100000000);
            uniform_int_distribution<> dist_key(0, size * 4);

            for(int j = 0; j < SAMPLES; j++){
                structures.push_back(createStructure(i));
                fill_structure(size, j, structures.back());
            }
            int key = dist_key(gen);
            start = high_resolution_clock::now();
            for(int j = 0; j < SAMPLES; j++){
                structures[j]->insert(0, key);
            }
            end = high_resolution_clock::now();
            writeResultToFile(file, size, "insert", i, duration_cast<nanoseconds>(end - start).count()/SAMPLES);
            for(auto s : structures){
                delete s;
            }
            structures.clear();
            
            for(int j = 0; j < SAMPLES; j++){
                structures.push_back(createStructure(i));
                fill_structure(size, j, structures.back());
            }
            start = high_resolution_clock::now();
            for(int j = 0; j < SAMPLES; j++){
                structures[j]->extract_max();
            }
            end = high_resolution_clock::now();
            writeResultToFile(file, size, "extract_max", i, duration_cast<nanoseconds>(end - start).count()/SAMPLES);
            for(auto s : structures){
                delete s;
            }
            structures.clear();

            for(int j = 0; j < SAMPLES; j++){
                structures.push_back(createStructure(i));
                fill_structure(size, j, structures.back());
            }
            start = high_resolution_clock::now();
            for(int j = 0; j < SAMPLES; j++){
                structures[j]->find_max();
            }
            end = high_resolution_clock::now();
            writeResultToFile(file, size, "find_max", i, duration_cast<nanoseconds>(end - start).count()/SAMPLES);
            for(auto s : structures){
                delete s;
            }
            structures.clear();

            for(int j = 0; j < SAMPLES; j++){
                structures.push_back(createStructure(i));
                fill_structure(size, j, structures.back());
            }
            key = dist_key(gen);
            int value = dist_value(gen);
            start = high_resolution_clock::now();
            for(int j = 0; j < SAMPLES; j++){
                structures[j]->modify_key(value, key);
            }
            end = high_resolution_clock::now();
            writeResultToFile(file, size, "modify_key", i, duration_cast<nanoseconds>(end - start).count()/SAMPLES);
            for(auto s : structures){
                delete s;
            }
            structures.clear();

            for(int j = 0; j < SAMPLES; j++){
                structures.push_back(createStructure(i));
                fill_structure(size, j, structures.back());
            }
            start = high_resolution_clock::now();
            for(int j = 0; j < SAMPLES; j++){
                structures[j]->return_size();
            }
            end = high_resolution_clock::now();
            writeResultToFile(file, size, "return_size", i, duration_cast<nanoseconds>(end - start).count()/SAMPLES);
            for(auto s : structures){
                delete s;
            }
            structures.clear();
        }
    }
    return;
}