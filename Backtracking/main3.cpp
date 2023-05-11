// Programa que realiza la solucion a el problema del laberinto
// Se utilizan las tecnicas de backtracking y branch and bound
// utilizando el recorrido BFS para encontrar la mejor solucion
// Jonathan Maya
// Jose Leonardo Perez Gonzalez
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

// Funcion que imprime un vector de vectores
// Orden O(n^2)
void printMatrix(vector<vector <int>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Funcion que evalua si la posicion actual es valida
// Orden O(n)
bool validPlace(vector<vector <int>> mazeMatrix, int i, int j){
    if(i >= 0 && i < mazeMatrix.size() && j >= 0 && j < mazeMatrix[0].size() && mazeMatrix[i][j] == 1){
        return true;
    }
    return false;
}

// Funcion reursiva que realiza la solucion del laberinto usando la tecnica de backtracking
// Orden O(2^(n^2))
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

// Funcion que imprime la mejor solucion del algoritmo branch and bound
// Orden O(n^2)
void findPath(vector<pair<int, int>> path, int M, int N){
    vector<vector <int>> solMatrix;
    int end = path.size() - 1;
    int prev = end - 1;
    pair<int, int> begin = {0, 0};
    pair<int, int> endPosition = {path[end].first, path[end].second};
    for(int i = 0; i < M; i++){
        vector <int> temp;
        for(int j = 0; j < N; j++){
            temp.push_back(0);
        }
        solMatrix.push_back(temp);
    }
    bool control = true;
    while(control){
        if(path[end].first == M-1 && path[end].second == N-1){
            control = false;
        }
        else {
            end--;
            prev--;
        }
    }
    while(endPosition != begin){
        if(path[prev].first == 0 && path[prev].second == 0){
                solMatrix[path[0].first][path[0].second] = 1;
                printMatrix(solMatrix);
                break;
        }
        else if(sqrt(pow(path[end].second - path[prev].second, 2) + pow(path[end].first - path[prev].first, 2)) == 1){
            endPosition = {path[prev].first, path[prev].second};
            solMatrix[path[end].first][path[end].second] = 1;
            solMatrix[path[prev].first][path[prev].second] = 1;
            end = prev;
            prev = end -1;
        }else{
            prev--;
        }
    }
}

// Algoritmo que evalua las posibles soluciones del algoritmo branch and bound
// Orden O(n)
void nodeNeighbor(int row, int column, int &nodesNext, vector<pair<int, int>> directions, vector<vector<int>> mazeMatrix,
vector<vector <int>> &visitedNodes, queue<pair<int, int>> &queueRC, vector<pair<int, int>> &path){
    for(int i = 0; i < 4; i++){
        int r = row + directions[i].first;
        int c = column + directions[i].second;

        if(r < 0 || c < 0){
            continue;
        }
        if(r >= mazeMatrix.size() || c >= mazeMatrix[r].size()){
            continue;
        }
        if(visitedNodes[r][c] == 1){
            continue;
        }
        if(mazeMatrix[r][c] == 0){
            continue;
        }
        queueRC.push({r, c});
        visitedNodes[r][c] = 1;
        nodesNext++;
        path.push_back({r, c});
    }
}

// Funcion que realiza el recorrido BFS por la matriz de adyacencia
// Orden O(n^2)
void bnBMaze(int M, int N, vector<vector <int>> mazeMatrix){
    queue<pair<int, int>> queueRC;
    vector<pair<int, int>> path;
    vector<vector <int>> visitedNodes;
    vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int i = 0;
    int j = 0;
    int stepsCount = 0;
    int nodesLeft = 1;
    int nodesNext = 0;
    bool isEnd = false;

    for(int i = 0; i < M; i++){
        vector <int> temp;
        for(int j = 0; j < N; j++){
            temp.push_back(0);
        }
        visitedNodes.push_back(temp);
    }
    
    queueRC.push({i, j});
    visitedNodes[i][j] = 1;
    path.push_back({i, j});
    while(!queueRC.empty()){
        int r = queueRC.front().first;
        int c = queueRC.front().second;
        queueRC.pop();
        if(r == mazeMatrix.size() - 1 && c == mazeMatrix[r].size() - 1 && mazeMatrix[i][j] == 1){
            isEnd = true;
            break;
        }
        nodeNeighbor(r, c, nodesNext, directions, mazeMatrix, visitedNodes, queueRC, path);
        nodesLeft--;
        if(nodesLeft == 0){
            nodesLeft = nodesNext;
            nodesNext = 0;
            stepsCount++;
        }
    }
    if(isEnd){
        findPath(path, M, N);
    }else{
        cout << "No hay solución" << endl;
    }
    
}

int main(){
    int M, N, n;
    vector<vector <int>> mazeMatrix;
    vector<vector <int>> solMatrix;

    cout << "Ingrese la cantidad de filas: ";
    cin >> M;
    cout << "Ingrese la cantidad de columnas: ";
    cin >> N;
    cout << "Ingrese la matriz binaria del laberinto: ";

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

    cout << "Laberinto inicial" << endl;
    printMatrix(mazeMatrix);
    bool control = backtrackingMaze(mazeMatrix, solMatrix, 0, 0);
    cout << "Solución backtracking" << endl;
    if(control){
        printMatrix(solMatrix);
    }else{
        cout << "No hay solución" << endl;
    }
    cout << "Solución ramificación y poda" << endl;
    bnBMaze(M, N, mazeMatrix);
    

    return 0;
}