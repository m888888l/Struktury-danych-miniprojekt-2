#include <iostream>
#include "PriorityArray.hpp"

PriorityArray::PriorityArray() : capacity(5), size(0){
    data = new Element[5]; //alokuje pamiec o rozmiarze 5*sizeof(Element) i przypisuje wskaznik tej pamieci do data
}

PriorityArray::~PriorityArray(){
    delete[] data; //trzeba zwolnic pamiec tablicy
}

void PriorityArray::resize(){
    capacity = 2 * capacity;

    Element* tempData = new Element[capacity]; //wskaznik na nowo zaalokowana pamiec dla tablicy o podwojonym rozmiarze

    for(int i = 0; i < size; i++){ //kopiowanie wartosci ze starej tablicy do nowej
        tempData[i] = data[i];
    }

    delete[] data; //zwolnienie pamieci w ktorej miescila sie stara tablica

    data = tempData;
}

int PriorityArray::return_max_element_index(){
    int max_key_index = 0;

    for(int i = 1; i < size; i++){
        if(data[i].key > data[max_key_index].key) max_key_index = i;
    }

    return max_key_index;
}

Element PriorityArray::extract_max(){
    int max_element_index = return_max_element_index();//zmienna tymczasowa do trzymania indeksu najwiekszego klucza, aby nie musiec kilka razy uzywac kosztownej metody
    Element temp = data[max_element_index];
    pop_at(max_element_index);

    return temp;
}

void PriorityArray::pop_at(int index){
    if(index < 0 || index >= size) return; 
    for(int i = index; i < size-1; i++){//kazdy element od data[index] staje sie kolejnym elementem, efektywnie usuwa element data[index] 
        data[i] = data[i+1];
    }
    size--;
}

void PriorityArray::insert(int value, int key){
    if(size == capacity) resize(); //dodanie elementu, wiec trzeba sprawdzic czy sie zmiesci i powiekszyc tablice jak nie
    
    data[size].value = value;
    data[size].key = key;
    
    size++;
}

int PriorityArray::return_size(){
    return size;
}

Element PriorityArray::find_max(){
    return data[return_max_element_index()];
}
    
void PriorityArray::modify_key(int value, int key){
    for(int i = 0; i < size; i++){
        if(data[i].value == value) data[i].key = key;//znajduje pierwszy element z podana wartoscia i zmienia jej klucz
    }
}

void PriorityArray::print(){
    for(int i = 0; i < size; i++){
        std::cout<<"("<<data[i].value<<", "<<data[i].key<<")\n";
    }
}