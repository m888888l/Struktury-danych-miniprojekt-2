#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include "Menu.hpp"
#include "Heap.hpp"
#include "PriorityArray.hpp"

using namespace std;


Menu::Menu(){};
Menu::~Menu(){};

void Menu::menu(){
    int structure;
    bool running = false;
    int arg1;
    int arg2;
    int arg3;
    Base* chosen_structure = nullptr;

    while(1){
        system("cls");
        cout<<"1. Heap\n2. Array\n3. Testy automatyczne\n4. Wyjdz\n";
        cin>>structure;
        system("cls");
        if(structure == 1) chosen_structure = new Heap;
        else if(structure == 2) chosen_structure = new PriorityArray;
        else if(structure == 3) ;//testy
        else if(structure == 4) return;

        if(chosen_structure != nullptr){
            running = true;
            while (running){
                cout << "1. Dodaj element\n"
                        "2. Pokaz MAX\n"
                        "3. Wyciagnij MAX\n"
                        "4. Zmodyfikuj klucz\n"
                        "5. Wyswietl strukture\n"
                        "6. Wyswietl rozmiar\n"
                        "7. Wstaw losowe wartosci\n"
                        "8. Zaladuj wartosci z pliku\n"
                        "9. Wyczysc strukture\n"
                        "10. Wyjdz\n";
                cin>>arg1;
                system("cls");
                switch (arg1){
                    case 1:{
                        cout<<"Wartosc: "; cin>>arg1;
                        cout<<"Klucz: "; cin>>arg2;
                        chosen_structure->insert(arg1, arg2);
                        system("cls");
                        break;
                    }
                    case 2:{
                        if(chosen_structure->return_size() < 1) cout<<"Brak elementow\n";
                        else{
                            Element temp = chosen_structure->find_max();
                            cout<<"("<<temp.value<<", "<<temp.key<<")\n\n";
                        }
                        break;
                    }
                    case 3:{
                        if(chosen_structure->return_size() < 1) cout<<"Brak elementow\n";
                        else{
                            Element temp = chosen_structure->extract_max();
                            cout<<"("<<temp.value<<", "<<temp.key<<")\n\n";
                        }
                        break;
                    }
                    case 4:{
                        if(chosen_structure->return_size() < 1) cout<<"Brak elementow\n";
                        else{
                            cout<<"Wartosc: "; cin>>arg1;
                            cout<<"Klucz: "; cin>>arg2;
                            chosen_structure->modify_key(arg1, arg2);
                            system("cls");
                        }
                        break;
                    }
                    case 5:{
                        chosen_structure->print();
                        cout<<"\n\n";
                        break;
                    }
                    case 6:{
                        cout<<"Rozmiar: "<<chosen_structure->return_size()<<"\n\n";
                        break;
                    }
                    case 7:{
                        cout<<"Ilosc losowych wartosci: "; cin>>arg1;
                        cout<<"Zakres wartosci OD: "; cin>>arg2;
                        cout<<"Zakres wartosci DO: "; cin>>arg3;
                        random_device rd;
                        mt19937 gen(rd());
                        uniform_int_distribution<> dist_values(arg2, arg3);
                        uniform_int_distribution<> dist_keys(arg2, arg3*3);
                        for(int i = 0; i < arg1; i++)
                            chosen_structure->insert(dist_values(gen), dist_keys(gen));
                        system("cls");
                        break;
                    }
                    case 8:{
                        delete chosen_structure;
                        if(structure == 1) chosen_structure = new Heap;
                        else if(structure == 2) chosen_structure = new PriorityArray;
                        string fileName;
                        char separator;
                        cout<<"Z jakiego pliku chcesz zaladowac dane: "; cin>>fileName;
                        cout<<"Jaki separator jest uzyty w pliku: "; cin>>separator;
                        loadFromFile(fileName, separator, chosen_structure);
                        system("cls");
                        break;
                    }
                    case 9:{
                        delete chosen_structure;
                        if(structure == 1) chosen_structure = new Heap;
                        else if(structure == 2) chosen_structure = new PriorityArray;
                        break;
                    }
                    case 10:{
                        delete chosen_structure;
                        chosen_structure = nullptr;
                        running = false;
                        break;
                    }
                    default:{
                        cout<<"Niepoprawny wybor\n\n";
                        break;
                    }
                }
            }
        }
    }
}

void Menu::loadFromFile(string fileName, char separator, Base* structure){
    ifstream file(fileName);
    if (!file.is_open())
        return;

    string line;

    while (getline(file, line)){
        stringstream ss(line);

        string valueStr;
        string keyStr;

        if (getline(ss, valueStr, separator) && getline(ss, keyStr, separator)){
        structure->insert(stoi(valueStr), stoi(keyStr));
        }
    }
    file.close();
}
