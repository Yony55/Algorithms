//
//A01424138 / Antonio Jaime Lopez
//A01424137 / Jonathan Maya
//A00829598 / Juan Pablo Yanez Gonzalez
//Programa que realiza el ordenamiento de un archivo .txt, ordenándolo por mes, día y hora 
//utilizando los métodos de Bubble Sort y búsqueda secuencial
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

//Arreglo de meses para facilitar el ordenamiento por mes
string mesesAr[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
//Vector de string que almacena el arreglo ordenado 
vector <string> finalVector;

//Función que implementa la busqueda secuencial para los datos ingresados por el usuario y al
//final los muestra en pantalla en forma descendente. Recibe el vector ordenado, mes inicial, dia
//inicial, mes final y dia final
//La funcion es de orden O(n), ya que la cantidad de repeticiones depende del tamano del vector
void busqSecuencial(vector<string> vectorOrd, int mesI, int diaI, int mesF, int diaF) {
    int tamanoVectorI = vectorOrd.size(); //Calcula el tamano de los vectores para 
    int tamanoVectorF = vectorOrd.size(); //los ciclos for
    bool control = true; //variable de control para romper el ciclo
    int i = 0, indexI = 0, indexF = 0;
    //ciclo for para encontrar el indice mayor o indice inicial
    for (i = tamanoVectorI; i > 0 && control; i--) {
        if (mesesAr[mesI - 1] == vectorOrd[i].substr(0, 3) && diaI == stoi(vectorOrd[i].substr(4, 6))) {
            indexI = i;
            tamanoVectorI = 0;
            control = false;
        }
    }
    //ciclo for que encuentra el indice menor o inidce final
    for (i = 0; i < tamanoVectorF; i++) {
        if (mesesAr[mesF - 1] == vectorOrd[i].substr(0, 3) && diaF == stoi(vectorOrd[i].substr(4, 6))) {
            indexF = i;
            tamanoVectorF = 0;
        }
    }
    //imprime en pantalla la busqueda ordenada de forma ascendente
    for (i = indexI; i > indexF - 1; i--) {
        cout << vectorOrd[i] << endl;
    }
}

//Funcion que implementa el ordenamiento por burbuja de los segundos
//Esta función es de orden O(n^2), ya que hay dos ciclos for anidados
void ordenaBurbujaSegundos(vector<string> arreglo, int pasos) {
    bool detener = true; //Variable de control para romper el ciclo
    for (int i = 0; i < pasos - 1 && detener; i++) {
        detener = false;
        for (int j = 0; j < pasos - i - 1; j++) {
            int segundosA, segundosB; //variables enteras que alcacenarán el valor de la hora convertida en segundos
            segundosA = (stoi(arreglo[j + 1].substr(7, 9))) * 3600 + (stoi(arreglo[j + 1].substr(10, 12))) * 60 + stoi(arreglo[j + 1].substr(13, 15));
            segundosB = (stoi(arreglo[j].substr(7, 9))) * 3600 + (stoi(arreglo[j].substr(10, 12))) * 60 + stoi(arreglo[j].substr(13, 15));
            if (segundosA < segundosB) { //compara los valores de los segundos para determinar el menor
                string mayor = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = mayor;
                detener = true;
            }
        }
    }
    //ciclo for para anadir los datos ordenados al vector ordenado
    for (int i = arreglo.size() - 1; i >= 0; i--) {
        finalVector.push_back(arreglo[i]);
    }
}

//Funcion que implementa el ordenamiento por burbuja de los dias
//Esta función es de orden O(n^2), ya que hay dos ciclos for anidados
void ordenaBurbuja(vector<string> arreglo, int pasos) {
    bool detener = true;
    for (int i = 0; i < pasos - 1 && detener; i++) {
        detener = false;
        for (int j = 0; j < pasos - i - 1; j++) {
            if (stoi(arreglo[j + 1].substr(4, 6)) < stoi(arreglo[j].substr(4, 6))) {
                string mayor = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = mayor;
                detener = true;
            }
        }
    }
    //separa los valores ordenados por dias en vectores temporales que incluyen dia y mes ordenados
    for (int j = 32; j >= 0; j--) {
        vector <string> vectorTemp3;
        for (int i = 0; i < arreglo.size(); i++) {
            if (stoi(arreglo[i].substr(4, 6)) == j) {
                vectorTemp3.push_back(arreglo[i]);
            }
        }
        //se pasa el vector ordenado por dia y mes para que pueda ser ordenado por sus horarios
        ordenaBurbujaSegundos(vectorTemp3, vectorTemp3.size());
    }
}
//Este es el main
int main() {
    //Declaramos variables 
    ifstream archivo;
    string linea;
    vector <string> vectorTemp;
    vector <string> meses;
    vector <string> mesesOrd;

    ////////////Archivo///////////////
    //Se abre el archivo bitacora.txt
    archivo.open("bitacora.txt", ios::in);

    //se imprime un mensaje de error si es que no se pudo acceder al archivo
    if (archivo.fail()) {
        cout << "No se encontró el archivo" << endl;
        exit(1);
    }

    //Se meten las lineas del archivo un vector temporal
    while (!archivo.eof()) {
        getline(archivo, linea);
        vectorTemp.push_back(linea);
    }
    //Se meten los meses de una matriz a un vector
    ///////Vector de los meses///////////////////////
    for (int j = 0; j <= 11; j++) {
        meses.push_back(mesesAr[j]);
    }

    //Se ordenan los meses del vector temporal
    //La complejidad del ordenamiento es 0(n^2), ya que hay for anidados
    ////////////Orneamiento de meses////////////////
    for (int k = 11; k > 0; k--) {
        for (int j = 0; j < vectorTemp.size(); j++) {
            if (vectorTemp[j].substr(0, 3) == mesesAr[k]) {
                mesesOrd.push_back(vectorTemp[j]);
            }
        }
    }

    //Se separan los meses en un vector
    //La complejidad del ordenamiento es 0(n^2), ya que hay for anidados
    for (int j = 11; j > 0; j--) {
        vector <string> vectorTempMeses;
        for (int i = 0; i < mesesOrd.size(); i++) {
            if (mesesAr[j] == mesesOrd[i].substr(0, 3)) {
                vectorTempMeses.push_back(mesesOrd[i]);
            }
        }
        ordenaBurbuja(vectorTempMeses, vectorTempMeses.size());
    }

    //Se crea un archivo sortedData.txt con los datos ordenados
    ofstream output_file("./sortedData.txt");
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(finalVector.begin(), finalVector.end(), output_iterator);

    int diaI, mesI, diaF, mesF;
    ///////Pedir datos al usuario////////////////
    cin >> diaI;
    cin >> mesI;
    cin >> diaF;
    cin >> mesF;
    //////Llamada a la funcion que busca los datos////
    busqSecuencial(finalVector, mesI, diaI, mesF, diaF);
    return 0;
}
