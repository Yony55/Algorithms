#include <bits/stdc++.h>
using namespace std;

queue<pair<int,int>>Q;
char arr[10000][10000];
int visited[10000][10000];
int visited2[10000][10000];

void solve(int n,int m,int startr,int startc,int endr,int endc){
    // int neighbor[][2]={{0,-1},{1,0},{0,1},{-1,0}};
    vector<pair<int,int>>neighbor={{0,-1},{1,0},{0,1},{-1,0}};
    Q.push({startr,startc});
    bool reached=false;
    while(!Q.empty()){
        for(int i=0;i<4;i++){
            int x=Q.front().first+neighbor[i].first,y=Q.front().second+neighbor[i].second;
            if(1<=x && x<=n && 1<=y && y<=m){
                if(arr[x][y]!='#' && (!(visited[x][y]))){
                    visited[x][y]=Q.front().first; visited2[x][y]=Q.front().second;
                    Q.push({x,y});
                }
            }
        }
        if(Q.front().first==endr && Q.front().second==endc){
            printf("reached\n");reached=true; break;// goto reached;
        }
        Q.pop();
    }
    if(!reached){
        cout<<"Not reached\n"; return;
    }
    visited[1][1]=1; visited2[1][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<"("<<visited[i][j]<<","<<visited2[i][j]<<") ";
        }
        cout<<endl;
    }
    // reached:
    vector<pair<int,int>>path;
    path.push_back({endr,endc});
    while(endr!=startr || endc!=startc){
        int endrr=endr,endcc=endc;
        path.push_back({visited[endr][endc],visited2[endr][endc]});
        endr=visited[endrr][endcc];   endc=visited2[endrr][endcc] ;
    }
    reverse(path.begin(),path.end());
    cout<<"Number cells visited in the shortest path is: "<<path.size()-2<<endl;
    for(int i=0;i<path.size();i++){
        cout<<path[i].first<<" "<<path[i].second<<endl;
    }
    return;
}

int main(){
    int n,m;
    cin>>n>>m;  // size of  matrix
    string str;
    for(int i=1;i<=n;i++){
        cin>>str;
        for(int j=1;j<=m;j++){
            arr[i][j]=str[j-1];
        }
    }
    int startr,startc,endr,endc;
    cin>>startr>>startc>>endr>>endc;
    solve(n,m,startr,startc,endr,endc);  // enter start_row,start_column, end_row,end_column
    return 0;
}
// youtube link -> https://www.youtube.com/watch?v=KiCBXu4P-2Y&list=PLDV1Zeh2NRsDGO4--qE8yH72HFL1Km93P&index=6
/*About reconstruction the path
To reconstruct the path from the start to the end you need to maintain additional information, namely a 2D matrix which tracks the cell which was used to reach the current cell. Let me call this matrix "prev", short for previous. Every time you advance to the next cell, keep track of which cell you came from in the prev matrix. Once you reach the end of the BFS, start reconstructing the path by beginning at the end node in the prev matrix and work your way to the start node. The obtained path will be in reverse order, so you will need to reverse it.
*/
/*Some inputs
// all the below cells have valid paths
2 2
00
#0
1 1 2 2

5 5
00#0#
#0##0
00000
###0#
0000#
1 1 5 1

6 7
0#00000
000#0#0
00#0000
0#000#0
#0#0#00
000000#
4 1 6 1

10 10
.#.......#
.#......#.
...#.#....
...#...#..
.#..###..#
...#...#..
#...#....#
..#...#.#.
...####...
.#......#.
1 1 10 6

*/