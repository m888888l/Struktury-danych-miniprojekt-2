#pragma once
#include <iostream>

struct Element{
    int value;
    int key;
};

class PriorityArray{
    public:
    PriorityArray();
    ~PriorityArray();

    void insert(int value, int key);
    Element extract_max();
    Element find_max();
    int return_size();
    void modify_key(int value, int key);
    void print();
    
    private:
        int return_max_element_index(); //metoda pomocnicza do znajdowania indeksu pod ktorym znajduje sie najwiekszy klucz
        void pop_at(int index);
        void resize(); //metoda pomocnicza do powiekszenia tablicy
        Element* data;
        int size; //ilosc elementow
        int capacity; //rozmiar tablicy
};