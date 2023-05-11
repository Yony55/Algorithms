// Programa que realiza el algoritmo de Suffix Array, el cual 
// encuentra los sufijos de un string, los ordena y los 
// imprime con su respectivo index
// Jonathan Maya A01424137
// Jose Leonardo Perez Gonzalez A01424133
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Estructura que almacena los sufijos y su respectivo índice
struct suffixStr{
    string str;
    int index;
};


// Funcion que recibe un string, encuentra sus sufijos, los ordena
// y despues los imprime en orden alfabetico
// Orden O(n^2)
void suffixArray(string str){
    vector<string> suffixArray;
    vector<suffixStr> suffixStructure; 

    for(int i = str.size() - 1; i >= 0; i--){
        string suffix = str.substr(i);
        for_each(suffix.begin(), suffix.end(), [](char & c){
            c = ::toupper(c);
        });
        suffixStr str {suffix, i};
        suffixStructure.push_back(str);
        suffixArray.push_back(suffix);
    }

    sort(suffixArray.begin(), suffixArray.end());

    for(int i = 0; i < suffixArray.size(); i++){
        for(int j = 0; j < suffixStructure.size(); j++){
            if(suffixArray[i] == suffixStructure[j].str){
                cout << suffixStructure[j].index << " " << suffixStructure[j].str << endl;
            }
        }
    }
}

int main(){
    string str;
    cout << "Ingrese la palabra: ";
    cin >> str;
    suffixArray(str);
    return 0;
}