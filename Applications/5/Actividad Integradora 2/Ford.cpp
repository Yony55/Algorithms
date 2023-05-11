#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;
 
void printMatrix(vector<vector <int>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool bfs(vector<vector<int>> residualGraph, int s, int t, vector<int>& previous){
    int n = residualGraph.size();
    vector<bool> visitedNodes(n, false);
    queue<int> q;
    q.push(s);
    visitedNodes[s] = true;
    previous[s] = - 1;

    while(!q.empty()) {
        int i = q.front();
        q.pop();
        for (int j = 0; j < n; j++) {
            if(visitedNodes[j] == false && residualGraph[i][j] != 0){
                if(j == t){
                    previous[j] = i;
                    return true;
                }
                q.push(j);
                previous[j] = i;
                visitedNodes[j] = true;
            }
        }
    }

    return false;
}
 
// Returns the maximum flow from s to t in the given graph
int fordFulkerson(vector<vector<int>> flowGraph, int s, int t){
    int n = flowGraph.size();
    vector<vector<int>> residualGraph = flowGraph;
    vector<int> previous(n);
    int maxFlow = 0;
    while (bfs(residualGraph, s, t, previous)) {
        int flow = 1000;
        for (int i = t; i != s; i = previous[i]) {
            int j = previous[i];
            flow = min(flow, residualGraph[j][i]);
        }
 
        for(int i = t; i != s; i = previous[i]){
            int j = previous[i];
            residualGraph[j][i] -= flow;
            residualGraph[i][j] += flow;
        }
 
        maxFlow += flow;
    }

    return maxFlow;
}
 
// Driver program to test above functions
int main(){
    int rows, n;
    vector<vector<int>> flowGraph(rows);
    cin >> rows;
    for(int i = 0; i < rows; i++){
        vector <int> temp;
        for(int j = 0; j < rows; j++){
            cin >> n;
            temp.push_back(n);
        }
        flowGraph.push_back(temp);
    }

    int t = flowGraph.size() - 1;
    cout << "The maximum possible flow is "
         << fordFulkerson(flowGraph, 0, 3);
 
    return 0;
}