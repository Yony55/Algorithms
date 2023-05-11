// Programa que realiza una implementacion de grafo dirigido a partir
// de un archivo de bitacora de accesos. Divide la red, host y puerto(puerto, mensaje, fecha y hora)
// en distintos niveles de nodos y los almacena. Al final, muestra cual es la red
// con el mayor numero de nodos registrados y los hosts con mayor numero de incidencias (puertos)
// Antonio Jaime Lopez A01424138
// Jonathan Maya A01424137
// Juan Pablo Yanez Gonzalez A00829598
// octubre 23, 2020

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

// se crea una structura de tipo nodo
struct Node{     
    string key;  
    vector<Node*> ip;  //Se crea un vector de nodos para asi poder ingresar las ips.
};              

//Funcion que sirve para crear un nuevo nodo
Node *newNode(string key)  
{ 
    Node *temp = new Node; 
    temp->key = key; 
    return temp; 
}


//Funcion para ordenar los datos de la bitacora
// El orden es O(n^2), ya que contiene ciclos anidados
void sortIPVector2(vector<string> array, vector<string> &sortIP) {
    for (int i = 1; i < 256; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (stoi(array[j].substr(24, 3)) == i){
                sortIP.push_back(array[j]);
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


int main(){
    //Declaracion de variables y vectores
    ifstream archivo;
    string linea;
    vector <string> vectorTemp;
    vector <string> ipOrd;
    vector <string> sortIP;
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
    
    //Se inicia el root del grafo
    Node *root = newNode("0"); 
    //vectores para saber que datos ya han sido agregados
    vector<string> visitedNet;
    vector <string> visitedHost;
    
    //Ingreso de la red (2 primeros dos numero de la IP) al grafo
    //[Root]->[Red]
    for(int i = 0; i < sortIP.size(); i++){
        if(!(find(visitedNet.begin(), visitedNet.end(), sortIP[i].substr(16, 7)) != visitedNet.end())){
            (root->ip).push_back(newNode(sortIP[i].substr(16, 7)));
            visitedNet.push_back(sortIP[i].substr(16, 7)); //ingreso de la Red agregada a la lista de ya visitadas
        }
    }
    
    //Ingreso del host (Ultimos 2 numeros de la IP) al grafo 
    //[Root]->[Red]->[Host]
    for(int i = 0; i < sortIP.size(); i++){
        if(!(find(visitedHost.begin(), visitedHost.end(), sortIP[i].substr(16, 15)) != visitedHost.end())){
            int index;
            for(int j = 0; j < visitedNet.size(); j++){
                if(sortIP[i].substr(16, 7) == visitedNet[j]){
                    index = j;
                }
            }
            (root->ip[index]->ip).push_back(newNode(sortIP[i].substr(24, 7)));
            visitedHost.push_back(sortIP[i].substr(16, 15));//ingreso del Host agregado a la lista de ya visitados
        }
    }

    //Ingreso del Port, mensaaje y fecha en la que se realizo el registro al grafo
    //[Root]->[Red]->[Host]->[Port]
    for(int i = 0; i < sortIP.size(); i++){
        int indexL1, indexL2;
        string net = sortIP[i].substr(16, 7);
        string host = sortIP[i].substr(24, 7);
        for(int j = 0; j < visitedNet.size(); j++){
            if(net == visitedNet[j]){
                    indexL1 = j;
            }
        }
        for(int k = 0; k < (root->ip[indexL1]->ip).size(); k++){
            if(host == (root->ip[indexL1]->ip[k])->key){
                    indexL2 = k;
                }
        }
        //Union del puerto, mensaje y fecha en una sola variable
        string temp = sortIP[i].substr(32) + " " + sortIP[i].substr(0, 15);
        (root->ip[indexL1]->ip[indexL2]->ip).push_back(newNode(temp));
    }

    //vector que contiene el indice de red para sacar el maximo 
    vector<int> indexVectorNet;
    int maxNet = 0;
    int indexNet = 0;

    //Ciclos para conseguir el maximo de la red
    for(int i = 0; i < (root->ip).size(); i++){
        int current = (root->ip[i]->ip).size();
        if(current > maxNet){
            maxNet = current;
            indexNet = i;
        }
    }
    for(int i = 0; i < (root->ip).size(); i++){
        int current = (root->ip[i]->ip).size();
        if(current >= maxNet){
            indexVectorNet.push_back(i);
        }
    }

    //Ciclos para conseguir el maximo Host
    vector<string> indexVectorHost;
    int maxHost = 0;
    for(int i = 0; i < (root->ip).size(); i++){
        for(int j = 0; j <  (root->ip[i]->ip).size() ; j++){
            int current = (root->ip[i]->ip[j]->ip).size();
            if(current > maxHost){
                maxHost = current;
            }
        }
    }
    for(int i = 0; i < (root->ip).size(); i++){
        for(int j = 0; j <  (root->ip[i]->ip).size() ; j++){
            int current = (root->ip[i]->ip[j]->ip).size();
            if(current >= maxHost){
                string temp = (root->ip[i])->key + "." + (root->ip[i]->ip[j])->key;
                indexVectorHost.push_back(temp);
            }
        }
    }

    //ciclo para imprimir los datos ip
    for(int i = 0; i < indexVectorNet.size(); i++){
        cout << visitedNet[indexVectorNet[i]] << endl;
    }
    //Salto de linea que divide los resultados
    cout << endl;
    
    //ciclo para imprimir los datos puerto
    for(int i = 0; i < indexVectorHost.size(); i++){
        cout << indexVectorHost[i] << endl;
    }

    return 0;
}