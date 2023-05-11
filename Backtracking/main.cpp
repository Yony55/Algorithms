#include <iostream>
#include <vector>
using namespace std;

void printMatrix(vector<vector <int>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool validPlace(vector<vector <int>> mazeMatrix, int i, int j){
    if(i >= 0 && i < mazeMatrix.size() && j >= 0 && j < mazeMatrix[0].size() && mazeMatrix[i][j] == 1){
        return true;
    }
    return false;
}

bool backtrackingMaze(vector<vector <int>> mazeMatrix, vector <vector <int>> &solMatrix, int i, int j){
    if(i == mazeMatrix.size() - 1 && j == mazeMatrix[i].size() - 1 && mazeMatrix[i][j] == 1){
        solMatrix[i][j] = 1;
        return true;
    }
    if(validPlace(mazeMatrix, i, j)){
        if(solMatrix[i][j] == 1){
            return false;
        }
        solMatrix[i][j] = 1;
        if(backtrackingMaze(mazeMatrix, solMatrix, i + 1, j)){
            return true;
        }
        if(backtrackingMaze(mazeMatrix, solMatrix, i, j + 1)){
            return true;
        }
        if(backtrackingMaze(mazeMatrix, solMatrix, i - 1, j)){
            return true;
        }
        if(backtrackingMaze(mazeMatrix, solMatrix, i, j - 1)){
            return true;
        }
        solMatrix[i][j] = 0;
        return false;
    }
    return false;
}

int main(){
    int M, N, n;
    vector<vector <int>> mazeMatrix;
    vector<vector <int>> solMatrix;

    cin >> M;
    cin >> N;

    for(int i = 0; i < M; i++){
        vector <int> temp;
        for(int j = 0; j < N; j++){
            cin >> n;
            temp.push_back(n);
        }
        mazeMatrix.push_back(temp);
    }

    for(int i = 0; i < M; i++){
        vector <int> temp;
        for(int j = 0; j < N; j++){
            temp.push_back(0);
        }
        solMatrix.push_back(temp);
    }

    backtrackingMaze(mazeMatrix, solMatrix, 0, 0);
    cout << endl;
    printMatrix(mazeMatrix);
    cout << endl;
    printMatrix(solMatrix);

    return 0;
}