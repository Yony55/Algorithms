// Programa que realiza una implementacion del algoritmo
// Hash String, recibe un archivo de texto y 'n' columnas
// como parametros e imprime su representacion hexadecimal
// Jonathan Maya A01424137
// Jose Leonardo Perez Gonzalez A01424133
// 5 de septiembre, 2021

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;

// Funcion que recibe la tabla generada por el algoritmo y
// el numero de columnas como parametros. Genera el arreglo
// 'a' e imprime la representacion hexadecimal del archivo
// Orden O(n^2)
void toHex(vector<vector<char>> hashTable, int n){
    vector<int> a;
    for(int i = 0; i < n; i++){
        int count = 0;
        for(int j = 0; j < hashTable.size(); j++){
            if(hashTable[j][i] == '['){
                count += n;
            } else{
                count += int(hashTable[j][i]);
            }
        }
        a.push_back(count % 256);
    }
    cout << endl;
    cout << "Arreglo de longitud 'n' que muestra la suma de las columnas con el modulo 256" << endl;
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
    
    string str = "";
    for(int i = 0; i < a.size(); i++){
        stringstream hexString;
        hexString << hex << a[i];
        if(hexString.str().size() < 2){
            string x = hexString.str();
            transform(x.begin(), x.end(), x.begin(), ::toupper);
            str += '0' + x;
        } else{
            string x = hexString.str();
            transform(x.begin(), x.end(), x.begin(), ::toupper);
            str += x;
        }
    }

    cout << endl;
    cout << "Representacion hexadecimal" << endl;
    int hexLength = n / 4;
    int control = 0;
    for(int i = 0; i < str.size(); i++){
        if(control == hexLength){
            cout << " " << str.at(i);
            control = 1;
        } else{
            cout << str.at(i);
            control ++;
        }
    }
}

// Funcion que recibe el vector de strings almacenados 
// en el archivo y el numero de columnas. Calcula el numero
// de filas que se tendra en la tabla hash
// Orden O(n)
double rowsInHash(vector<string> strings, int n){
    double rows;
    for(int i = 0; i < strings.size(); i++){
        rows += strings[i].size();
    }
    rows += strings.size();
    rows = ceil(rows / n);
    return rows;
}


// Funcion que resibe un vector de vectores y lo imprime
// en pantalla
// Orden O(n^2)
void printMatrix(vector<vector <char>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j] == '\n'){
                cout << '-' << " ";
            } else{
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// funcion que recibe el vector de strings almacenados
// en el archivo y el numero de columnas. Calcula y genera
// la matriz de hash.
// Orden O(n^2) 
void hashString(vector<string> strings, int n){
    int rows = rowsInHash(strings, n);
    vector<vector<char>> hashTable(rows);
    vector<char> charVector;
    for(int i = 0; i < strings.size(); i++){
        for(int j = 0; j < strings[i].size(); j++){
            charVector.push_back(strings[i].at(j));
        }
        charVector.push_back('S');
    }

    int strCount = strings.size() - 1;
    int strIterator = 0;
    for(int i = 0; i < hashTable.size(); i++){
        for(int j = 0; j < n; j++){
            if(strIterator < charVector.size() - 1){
                if(charVector[strIterator] == 'S'){
                    hashTable[i].push_back('\n');
                    strIterator++;
                } else{
                    hashTable[i].push_back(charVector[strIterator]);
                    strIterator++;
                }
            } else{
                hashTable[i].push_back('[');
            }
        }
    }
    cout << endl;
    cout << "Matriz generada por el algoritmo, los saltos de linea se representan con '-' y espacios rellenados con '['" << endl;
    printMatrix(hashTable);
    toHex(hashTable, n);
}
    

int main(){
    int n;
    ifstream fileIn;
    string strLine, fileName;
    vector <string> vectorTemp;

    cout << "Ingrese el nombre del archivo de texto (sin extension): ";
    cin >> fileName;
    fileName += ".txt";
    fileIn.open(fileName, ios::in);
    if (fileIn.fail()) {
        cout << "El archivo no existe" << endl;
        exit(1);
    }
    while (!fileIn.eof()) {
        getline(fileIn, strLine);
        vectorTemp.push_back(strLine);
    }

    cout << "Ingrese un multiplo 'n' de 4 entre 16 y 64: ";
    bool control = false;
    while(!control){
        cin >> n;
        if((n >= 16 || n <= 64) && n % 4 == 0){
            control = true;
        } else{
            cout << "Ingrese un numero válido: ";
        }
    }

    hashString(vectorTemp, n);

    return 0;
}