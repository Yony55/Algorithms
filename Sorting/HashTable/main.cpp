// Programa que realiza una implementacion de hash table mediante el uso de 
// el archivo bitacora2.txt. Almacena los datos en la tabla y despues
// es pisble consultar la cantidad de accesos y las ip unicas
// ligadas con el dominio
// Antonio Jaime Lopez A01424138
// Jonathan Maya A01424137
// Juan Pablo Yanez Gonzalez A00829598
// noviembre 29, 2020

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;
vector <int> access;
vector<vector<string>> alreadyCon(32749);
int vecIndex = 0;

// Se crea la estructura de tipo ip, la cual contiene todos sus datos
struct ip{
    string domain;
    int access;
    int connections;
    vector <string> compIP;
};

// Funcion que crea un nuevo nodo con base a argumentos especificos
// Es de orden O(1), ya que solo se ejecuta una vez
ip *newNode(string domain, int access, int connections)  
{ 
    ip *temp = new ip; 
    temp->domain = domain;
    temp->access = access;
    temp->connections = connections;
    return temp; 
}

// Funcion que calcula el numero ASCII de la placa y despues
// aplica el modulo 32749 para encontrar el indice
// Es de orden O(n), ya que depende de la longitud del string
int ipASCII(string strIP){
    int index;
    vector<char> cstr(strIP.c_str(), strIP.c_str() + strIP.size() + 1);
    for(int i = 0; i < cstr.size(); i++){
        index = index + int(cstr[i]);
    }
    index = index%32749;
    return index;
}

// funcion que extrae el dominio de una ip
// es de orden O(n), ya que depende de la longitus del string
int getDomain(string str){
    int index, control = 0;
    for(int i = 16; i < str.size(); i++){
        if(str.substr(i, 1) == "."){
            control++;
        }
        if(control == 2){
            index = i;
            break;
        }
    }
    return index;
}

// funcion que extrae el acceso de una ip
// es de orden O(n), ya que depende de la longitus del string
int getAccess(string str){
    int index;
    for(int i = 16; i < str.size(); i++){
        if(str.substr(i, 1) == ":"){
            index = i;
            break;
        }
    }
    return index;
}

string deleteZeros(string str){
    int strIndex = 15;
    string newStr = str;
    while(strIndex < 38){
        string str1 = newStr.substr(strIndex, 1),
        str2 = newStr.substr(strIndex+1, 1),
        str3 = newStr.substr(strIndex+2, 1);
        int control = 0;
        if((str1 == " " || str1 == ".") && (str2 == "0") && (stoi(str3) > 0)){
            string strControl = newStr.substr(strIndex);
            string newStr1 = newStr.substr(0, (newStr.size() - strControl.size())+1);
            string newStr2 = newStr.substr(strIndex+2);
            newStr = newStr1 + newStr2;
            control = 1;
        }
        if(control == 0){
            strIndex++;
        }
    }
    return newStr;
}

// Funcion que inserta un valor dentro de la hash table, comprueba que el 
// dato no se haya ingresado antes o que la tabla ya este llena.
// Es de orden O(n), ya que contiene ciclos que dependen del tamano de la tabla
void ins(vector <ip*> & hashTable, vector <string> &already, vector <string> sortIP, int indexIP){
    int indexD = getDomain(sortIP[indexIP]);
    int indexC = getAccess(sortIP[indexIP]);
    string domain = sortIP[indexIP].substr(16, indexD - 16);
    string connection = sortIP[indexIP].substr(indexD + 1, (indexC - indexD) -1);
    int counter = 0;

    for(int i = 0; i < hashTable.size(); i++){
        if(hashTable[i]->domain != "none"){
            counter++;
        }
    }
    if(hashTable.size() == counter){
        cout << "tabla llena, imposible insertar" << endl;
        return;
    }
    
    if((find(already.begin(), already.end(), domain) != already.end())){
        for(int i = 0; i < already.size(); i++){
            if(already[i] == domain){
                access[i]++;
                int vecIndex = i;
                alreadyCon[vecIndex].push_back(connection);
                return;
            }
        }
    }

    already.push_back(domain);
    access.push_back(1);
    alreadyCon[vecIndex].push_back(connection);
    vecIndex++;
    int index = ipASCII(domain);

    for(int i = index; i < hashTable.size(); i++){
        if(hashTable[i]->domain == "none"){
            hashTable[i] = newNode(domain, 1, 0);
            return;
        }
        else if(i == hashTable.size()-1 && hashTable[i]->domain != "none"){
            i = -1;
        }
    }
}

//Funcion para ordenar los datos de la bitacora
// El orden es O(n^2), ya que contiene ciclos anidados
void sortIPVector2(vector<string> array, vector<string> &sortIP) {
    for (int i = 1; i < 256; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (stoi(array[j].substr(24, 3)) == i){
                sortIP.push_back(deleteZeros(array[j]));
            }
        }
    }
}

//Funcion para ordenar los datos de la bitacora
// El orden es O(n^2), ya que contiene ciclos anidados
void sortIPVector(vector<string> array, vector<string> &sortIP) {
    for (int i = 1; i < 256; i++) {
        vector<string> tempVector;
        for (int j = 0; j < array.size(); j++) {
            if (stoi(array[j].substr(20, 3)) == i){
                tempVector.push_back(array[j]);
            }
        }
        sortIPVector2(tempVector, sortIP);
    }
}

// Funcion que regresa el numero de acceso a traves de una ip
// Es de orden O(n), ya que contiene un ciclo
void searchKey(string key, vector <string> already){
    for(int j = 0; j < already.size(); j++){
        if(already[j] == key){
            cout << key << endl;
            cout << alreadyCon[j].size() << endl;
            return;
        }
    }
}

// Funcion que regresa las ip unicas a traves de un dominio
// Es de orden O(n^2), ya que contiene ciclos anidados
void searchCon(string key, vector <string> already){
    vector <string> unique;
    int index;
    for(int j = 0; j < already.size(); j++){
        if(already[j] == key){
            index = j;
        }
    }
    
    for(int k = 0; k < alreadyCon[index].size(); k++){
        int counter = 0;
        string look = alreadyCon[index][k];
        for(int j = 0; j < alreadyCon[index].size(); j++){
            if(alreadyCon[index][j] == look){
                counter++;
            }
            if(counter == 1 && k == alreadyCon[index].size()-1){
                unique.push_back(look);
            }
        }
    }

    for(int i = 0; i < unique.size(); i++){
        cout << key << "." << unique[i] << endl;
    }
}

int main(){
    ifstream archivo;
    string linea;
    vector <string> vectorTemp;
    vector <string> ipOrd;
    vector <string> sortIP;
    vector <string> already;
    vector <ip *> hashTable(32749, newNode("none", 0, 0)); // vector que servira como tabla hash

    //abrir el archivo
    archivo.open("bitacora2.txt", ios::in);
    while (!archivo.eof()) {
        getline(archivo, linea);
        vectorTemp.push_back(linea);    //Guarda las lineas del txt en un vector
    }
    
    // Ciclo que ordena el vector de acuerdo a la primera parte de la red
    // El orden es O(n^2), ya que contiene ciclos anidados
    for (int i = 1; i < 256; i++) {
        for (int j = 0; j < vectorTemp.size(); j++) {
            if (vectorTemp[j].size() > 1 && stoi(vectorTemp[j].substr(16, 3)) == i) {
                ipOrd.push_back(vectorTemp[j]);
            }
        }
    }

    // Ciclo que ordena el vector de acuerdo a la primera parte de la red
    // El orden es O(n^2), ya que contiene ciclos anidados
    for (int i = 1; i < 256; i++) {
        vector <string> tempVector;
        for (int j = 0; j < ipOrd.size(); j++) {
            if (stoi(ipOrd[j].substr(16, 3)) == i){
                tempVector.push_back(ipOrd[j]);
            }
        }
        sortIPVector(tempVector, sortIP);
    }

    // ciclo para almacenar los datos en una tabla hash
    for(int i = 0; i < sortIP.size(); i++){
        ins(hashTable, already, sortIP, i);
    }

    // menu ciclado
    int n;
    string key;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> key;
        searchKey(key, already);
        searchCon(key, already);
    }

    return 0;
}