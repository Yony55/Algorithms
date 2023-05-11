#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

void printMatrix(vector<vector <int>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

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
        cout << path[end].first << endl;
        cout << path[end].second << endl;
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
                cout << "--" << endl;
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
            //path.erase(path.begin() + prev);
            prev--;
        }
    }
    cout << "si salio del cliclo" << endl;
}

void nodeNeighbor(int row, int column, int &nodesNext, vector<int> dirRow, vector<int> dirColumn, vector<vector<int>> mazeMatrix,
vector<vector <int>> &visitedNodes, queue<int> &rowQ, queue<int> &columnQ, vector<pair<int, int>> &path){
    for(int i = 0; i < 4; i++){
        int r = row + dirRow[i];
        int c = column + dirColumn[i];
        cout << "R1: " + to_string(r) << " " << "C1: " + to_string(c) << endl;

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
        rowQ.push(r);
        columnQ.push(c);
        cout << "R2: " + to_string(r) << " " << "C2: " + to_string(c) << endl;
        visitedNodes[r][c] = 1;
        nodesNext++;
        path.push_back({r, c});
    }
}

void bnBMaze(int M, int N, vector<vector <int>> mazeMatrix){
    queue<int> rowQ;
    queue<int> columnQ;
    vector<vector <int>> visitedNodes;
    vector<int> dirRow{-1, 1, 0, 0};
    vector<int> dirColumn{0, 0, 1, -1};
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
    cout << "-" << endl;
    printMatrix(visitedNodes);
    cout << "-" << endl;
    
    rowQ.push(i);
    columnQ.push(j);
    visitedNodes[i][j] = 1;
    vector<pair<int, int>> path;
    path.push_back({i, j});
    while(!rowQ.empty()){
        int r = rowQ.front();
        rowQ.pop();
        int c = columnQ.front();
        columnQ.pop();
        cout << r << " " << c << endl;
        //cout << rowQ.back() << " " << columnQ.back() << endl;
        cout << "-" << endl;
        printMatrix(visitedNodes);
        cout << "-" << endl;
        if(r == mazeMatrix.size() - 1 && c == mazeMatrix[r].size() - 1 && mazeMatrix[i][j] == 1){
            isEnd = true;
            break;
        }
        nodeNeighbor(r, c, nodesNext, dirRow, dirColumn, mazeMatrix, visitedNodes, rowQ, columnQ, path);
        nodesLeft--;
        if(nodesLeft == 0){
            nodesLeft = nodesNext;
            nodesNext = 0;
            stepsCount++;
        }
    }
    if(isEnd){
        cout << "end" << endl;
        for(int i = 0; i < path.size(); i++){
            cout << path[i].first << " " << path[i].second << endl;
        }
        findPath(path, M, N);
    }else{
        cout << " not end" << endl;
    }
    
}

int main(){
    int M, N, n;
    vector<vector <int>> mazeMatrix;

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

    bnBMaze(M, N, mazeMatrix);

    return 0;
}