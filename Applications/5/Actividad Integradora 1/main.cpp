// Programa que realiza la implementación de los algoritmos
// Longest Common Subsequence y Longest Common Substring
// para realizar la búsqueda de coincidencias entre archivos
// de texto.
// Jonathan Maya A01424137
// Jose Leonardo Perez Gonzalez A01424133
// 27 de septiembre, 2021

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Estructura utilizada para guardar los valores de las coincidencias
struct Subsequences{
    bool status = false;
    int row = 0;
    int index = 0;
};

// Función para hacer un "reverse" al string
void reverseString(string& str){
    int n = str.length();

    for (int i = 0; i < n / 2; i++){
        swap(str[i], str[n - i - 1]);
    }
}

// Funcion que recibe dos strings, un indice y encuentra la subsecuencia mas
// larga entre ambas cadenas de texto
// O(nm)
vector<int> LCSubsequence(string str1, string str2, int row){
    //reverseString(str2);
    int x1, y1;
    int numOfRows = str1.length();
    int numOfColumns = str2.length();
    int L[numOfRows + 1][numOfColumns + 1];
    vector<int> v;
 
    for (int i = 0; i <= numOfRows; i++){
        for (int j = 0; j <= numOfColumns; j++){
            if (i == 0 || j == 0){
                L[i][j] = 0;
            } else if (str1[i-1] == str2[j-1]){
	            x1 = i;
	            y1 = j;
                L[i][j] = L[i - 1][j - 1] + 1;
            } else{
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }
    v.push_back(row);
    v.push_back(x1);
    v.push_back(L[numOfRows][numOfColumns]);
    return v;
}

// Funcion que recibe dos strings, un indice y encuentra la subcadena mas
// larga entre ambas cadenas de texto
// O(nm)
vector<int> LCSubstring(string str1, string str2, int row){
    int x1, y1, sizeOfSubStr = 0;
    int numOfRows = str1.length();
    int numOfColumns = str2.length();
    int lcsTable[numOfRows + 1][numOfColumns + 1];
    vector<int> v;

    for(int i = 0; i < numOfRows; i++){
        lcsTable[i][0] = 0;
    }
    for(int i = 0; i < numOfColumns; i++){
        lcsTable[0][i] = 0;
    }

    for(int i = 1; i <= numOfRows; i++){
	    for(int j = 1; j <= numOfColumns; j++){
	        if(str1[i - 1] == str2[j - 1]){
	            lcsTable[i][j] = 1 + lcsTable[i-1][j-1];
	            if(sizeOfSubStr < lcsTable[i][j]){
	                sizeOfSubStr = lcsTable[i][j];
	                x1 = i;
	                y1 = j;
	            }
	        } else{
	            lcsTable[i][j]=0;
            }
	    }
	}
    if(sizeOfSubStr == 0){
        x1 = 0;
    }
    v.push_back(row + 1);
    v.push_back(x1 - sizeOfSubStr + 1);
    v.push_back(x1);
    v.push_back(sizeOfSubStr);
    return v;
} 

// funcion que recibe los archivos de transmision y maliciosos en forma
// de vector y llama a las funciones correspondientes para la busqueda.
void compareFiles(vector<vector<string>> transVector, vector<vector<string>> malVector){
    Subsequences subsArray[transVector.size() * malVector.size()];   
    for (int i = 0; i < transVector.size(); i++){
        int confirmed[malVector.size()] = {0, 0, 0};
        for(int j = 0; j < transVector[i].size(); j++){
            for(int k = 0; k < malVector.size(); k++){
                for(int l = 0; l < malVector[k].size(); l++){
                    if(confirmed[k] == 1){
                        break;
                    } else{
                        vector<int> eval;
                        eval = LCSubstring(transVector[i][j], malVector[k][l], j);
                        int index;
                            if(i == 0){
                                index = 0 + k;
                            } else{
                                index = 3 + k;
                            }
                        if(eval[3] == (malVector[k][l].length())){
                            subsArray[index].status = 1;
                            subsArray[index].row = eval[0];
                            subsArray[index].index = eval[1];
                            confirmed[k] = 1;
                            break;
                        } else if(eval[2] < 2 && l == malVector[k].size() - 1 && j == transVector[i].size() - 1){
                            subsArray[index].status = 0;
                            subsArray[index].row = 0;
                            subsArray[index].index = 0;
                        }
                    }
                }
            }
        }
    }

    vector<vector<int>> sequenceVector;
    for (int i = 0; i < transVector.size(); i++){
        vector<int> v{0, 0, 0, 0};
        for(int j = 0; j < transVector[i].size(); j++){
            for(int k = 0; k < malVector.size(); k++){
                for(int l = 0; l < malVector[k].size(); l++){
                    vector<int> eval;
                    string revStr = malVector[k][l];
                    reverseString(revStr);
                    eval = LCSubstring(transVector[i][j], revStr, j);
                    if(eval[3] > v[3] && eval[3] == (malVector[k][l].length())){
                        v = eval;
                    }
                }
            }
        }
        sequenceVector.push_back(v); 
    }

    vector<int> v{0, 0, 0, 0};
    for(int i = 0; i < transVector[0].size(); i++){
        for(int j = 0; j < transVector[1].size(); j++){
            vector<int> eval;
            eval = LCSubstring(transVector[0][i], transVector[1][j], i);
            if(eval[3] > v[3]){
                v = eval;
            }
        }
    }

    cout << "Parte 1"  << endl;
    for(int i = 0; i < (sizeof(subsArray)/sizeof(*subsArray)); i++){
        if(subsArray[i].status == 0){
            cout << "false" << endl;
        } else{
            cout << "true " << subsArray[i].row << " " << subsArray[i].index << endl;
        }
    }

    cout << "\nParte 2"  << endl;
    for(int i = 0; i < sequenceVector.size(); i++){
        for(int j = 0; j < sequenceVector[i].size() - 1; j++){
            cout << sequenceVector[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\nParte 3"  << endl;
    cout << v[0] << " " << v[1] << " " << v[2] << endl;
}

int main(){
    vector<string> fileNames = {"transmission1.txt", "transmission2.txt", "mcode1.txt", "mcode2.txt", "mcode3.txt"};
    vector<vector<string>> transVector;
    vector<vector<string>> malVector;

    for(int i = 0; i < fileNames.size(); i++){
        ifstream file;
        string strLine;
        vector <string> vectorTemp; 
        file.open(fileNames[i], ios::in);
        while (!file.eof()) {
            getline(file, strLine);
            vectorTemp.push_back(strLine);
        }
        if(i < 2){
            transVector.push_back(vectorTemp);
        } else{
            malVector.push_back(vectorTemp);
        }
    }

    compareFiles(transVector, malVector);

    return 0; 
}