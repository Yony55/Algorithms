// Jonathan Maya
// Jose Leonardo Perez Gonazalez
// Programa que resuelve el problema de cambio de monedas utilizando
// la programacion dinamica y los algoritmos avaros
// 24 de agosto, 2021

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Funcion que recibe N cantidad de monedas
// y genera un vector con las denominaciones
// complejidad O(n)
vector<int> fillCoins(int N){
  vector<int> res = {};
  int n;
  for (int i =0; i<N;i++){
    cout<<"Ingrese la " << i+1 <<" moneda: ";
    cin>>n;
    res.push_back(n);
  }
  sort(res.begin(), res.end());
  reverse(res.begin(), res.end());
  return res;
};

// Algoritmo avaro que implementa el cambio de monedas
// complejidad O(n)
vector <vector<int>> getChange (vector<int> availableCoins, int value ) {
  vector <vector<int>> vec;
  vector <int> vtemp;
  vtemp.push_back(0);
  vtemp.push_back(0);
  int n = availableCoins.size();
  for(int i=0; i<n; i++){
    vtemp[0] = availableCoins[i];
    vtemp[1] = 0;
    while(value >= availableCoins[i]) {
      value = value - availableCoins[i];
      vtemp[0] = availableCoins[i];
      vtemp[1] = (vtemp[1]) +1; 
    }
    vec.push_back(vtemp);
  }
  return vec;
}

// Funcion que imprime los resultados del algoritmo avaro
// complejidad O(n)
void printChange(vector<vector<int>> data, int N){
    cout << "--Algoritmo avaro--" << endl;
  for(int i=0; i<N;i++){
    cout<< "Moneda: "<<data[i][0]<<" Cantidad: "<<data[i][1]<<endl;
  }
}

// Funcion que calcula la cantidad de monedas y denominaciones para el cambio 
// Recibe la tabla generada por el algoritmo dinamico, el vector de denominaciones
// la cantidad de monedas y el cambio a entregar
// complejidad O(n^2)
void finalChange(vector<vector<int>> newVector, vector<int> coinValues, int coinsSize, int change){
    bool control = true;
    vector <int> finalChangeVec;
    coinsSize--;
    cout << "--Programación dinámica--" << endl;
    while(control){
        if(change == 0){
            control = false;
        }
        else if(coinsSize == 1){
            int finalCoins = newVector[coinsSize-1][change] / coinValues[coinsSize];
            for(int i = finalCoins; i > 0; i--){
                finalChangeVec.push_back(coinValues[coinsSize]);
                change -= coinValues[coinsSize];
            }
            if(change != 0)
                cout << "No se pudo dar: " + to_string(change) + " peso(s), mejor te damos un cicle :)" << endl;
            control = false;
        }
        else if(newVector[coinsSize][change] == newVector[coinsSize-1][change]){
            coinsSize--;
        }
        else if(newVector[coinsSize][change] == 1 + newVector[coinsSize][change - coinValues[coinsSize]]){
            finalChangeVec.push_back(coinValues[coinsSize]);
            change -= coinValues[coinsSize];
        }
    }

    for(auto it = cbegin(finalChangeVec); it != cend(finalChangeVec); ) {  
        int dups = count(it, cend(finalChangeVec), *it);
        if ( dups > 0 )
            cout << "Moneda: " << *it << " Cantidad: " << dups << endl;
        for(auto last = *it;*++it == last;);
    }
}

// funcion que genera la tabla de valores para el cambio
// utilizando la programacion dinamica 
// complejidad O(n^2)
void changeTable(vector<int> coinValues, int change){
    vector<vector<int>> newVector;
    for(int i = 0; i < coinValues.size() + 1; i++){
        vector<int> v;
        if(i == 0){
            for(int j = 0; j < change + 1 ; j++){
                v.push_back(j);
            }
            newVector.push_back(v);
        }
        else{
            for(int j = 0; j < change + 1 ; j++){
                v.push_back(0);
            }
            newVector.push_back(v);
        }
    }

    for(int i = 1; i <= coinValues.size(); i++){
        for(int j = 1; j <= change; j++){
            if (i == 1){
                newVector[i][j] = j;
            }
            else if(j < coinValues[i]){
                newVector[i][j] = newVector[i - 1][j];
            }
            else{
                newVector[i][j] = min(newVector[i - 1][j], 1 + newVector[i][j - coinValues[i]]);
            }
        }
    }
    
    // cout << "--Tabla generada por el algoritmo de programación dinámica--" << endl;
    // for(int i = 0; i < coinValues.size() ; i++){
    //      for(int j = 0; j < change + 1; j++){
    //          cout << newVector[i][j] << " ";
    //      }
    //      cout << endl;
    // }
    finalChange(newVector,coinValues, coinValues.size(), change);
}

int main(){
    int N,P,Q;
    cout<< "Digite la cantidad de monedas: ";
    cin>> N;
    vector<int> availableCoins = fillCoins(N);
    vector<int> coinValues;
    coinValues.push_back(0);
    for(int i = availableCoins.size() - 1; i >= 0; i--){
        coinValues.push_back(availableCoins[i]);
    }
    cout<< "Digite el valor de P: ";
    cin>> P;
    cout<<"Digite el valor de Q: ";
    cin>> Q;

    cout<<"Se dara el cambio de: "<< Q-P<<endl<<endl;
    vector<vector<int>> data = getChange(availableCoins, Q-P);
    changeTable(coinValues, Q - P);
    printChange(data,N);
    return 0;
}