#include <iostream>
#include <vector>
using namespace std;

void finalChange(vector<vector<int>> newVector, vector<int> coinValues, int coinsSize, int change){
    bool control = true;
    vector <int> finalChangeVec;
    coinsSize--;
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

    for(int i = 0; i < finalChangeVec.size(); i++){
        cout << finalChangeVec[i] << endl;
    }
}

void changeTable(){
    int numOfCoins, coin, p, q, change;
    vector<int> coinValues {0}; 
    cout << "Ingrese el número de monedas: ";
    cin >> numOfCoins;
    for(int i = 0; i < numOfCoins; i++){
        cout << "Ingrese la denominación: ";
        cin >> coin;
        coinValues.push_back(coin);
    }
    cout << "Ingrese el precio del producto: ";
    cin >> p;
    cout << "Ingrese el el billete o moneda: ";
    cin >> q;
    change = q - p; 
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

    // for(int i = 0; i < coinValues.size() ; i++){
    //      for(int j = 0; j < change + 1; j++){
    //          cout << newVector[i][j] << " ";
    //      }
    //      cout << endl;
    // }

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

    // for(int i = 0; i < coinValues.size() ; i++){
    //      for(int j = 0; j < change + 1; j++){
    //          cout << newVector[i][j] << " ";
    //      }
    //      cout << endl;
    // }
    finalChange(newVector,coinValues, coinValues.size(), change);
}

int main(){
    changeTable();

    return 0;
}