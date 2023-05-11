// Programa que implementa el algoritmo de ordenamiento
// Merge Sort utilizando el metodo de Divide y Venceras
// Recibe N numeros enteros, seguido de N valores reales
// El programa los ordena y los imprime en forma descendente
// Jonathan Maya A01424137
// Jose Leonardo Perez Gonzalez A01424133
#include <iostream>
#include <vector>
using namespace std;

// Funcion que recibe los sub-vectores, el indice inicial, el de en medio y el indice
// final de los sub-vectores. Despues mezcla los dos sub-vectores y los ordena
void merge(vector <double> &valVector, int left, int mid, int right){
    double array1 = mid - left + 1;
    double array2 = right - mid;
 
    double *lArray = new double[array1];
    double *rArray = new double[array2];
 
    for (int i = 0; i < array1; i++){
        lArray[i] = valVector[left + i];
    }
    for (int j = 0; j < array2; j++){
        rArray[j] = valVector[mid + 1 + j];
    }
 
    int indexArray1 = 0; 
    int indexArray2 = 0;
    int indexMid = left; 
 
    while (indexArray1 < array1 && indexArray2 < array2){
        if (lArray[indexArray1] <= rArray[indexArray2]){
            valVector[indexMid] = lArray[indexArray1];
            indexArray1++;
        }
        else{
            valVector[indexMid] = rArray[indexArray2];
            indexArray2++;
        }
        indexMid++;
    }

    while (indexArray1 < array1){
        valVector[indexMid] = lArray[indexArray1];
        indexArray1++;
        indexMid++;
    }

    while (indexArray2 < array2){
        valVector[indexMid] = rArray[indexArray2];
        indexArray2++;
        indexMid++;
    }
}

// Funcion que recibe el vector a ordenar, su indice de inicio y el final
void mergeSort(vector <double> &valVector, int begin, int end){
    if (begin >= end){
        return; 
    }
 
    auto mid = begin + (end - begin) / 2;
    mergeSort(valVector, begin, mid);
    mergeSort(valVector, mid + 1, end);
    merge(valVector, begin, mid, end);
}

int main(){
    vector <double> valVector;
    double total, number;
    cout << "Ingrese el total de numeros: ";
    cin >> total;

    for (int i = 0; i < total; i++){
        cout << "Ingrese el numero a ordenar: ";
        cin >> number;
        valVector.push_back(number);
    }
 
    mergeSort(valVector, 0, valVector.size() - 1);
 
    cout << "Merge Sort Descendente" << endl;
    for (int i = valVector.size(); i > 0; i--){
        cout << valVector[i - 1] << endl;
    }

    return 0;
}