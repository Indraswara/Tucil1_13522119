#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Path{
    int row;
    int col;
};



void printMatrix(vector<vector<int>> matrix){

    cout << "[";
    for( int i = 0; i < matrix.size(); i++){
        cout << "[";
        for(int j = 0; j < matrix[0].size(); j++){
            cout << matrix[i][j];
            if(j != matrix[0].size() - 1){
                cout << " ";
            }
        }
        cout << "]";
        if(i != matrix.size() -1){
            cout << "\n";
        }
    }
    cout << "]";

}

bool dfs(vector<vector<string>>& board, vector<Path> path, int curRow, int curCol, int currDepth, int buffer, bool isHorizontal){

    if(curRow < 0 || curRow >= board.size() || curCol < 0 || curCol >= board[0].size()){
        return false;
    }

    for(int i = 0; i < path.size(); i++){
        if(curRow == path[i].row && curCol == path[i].col){
            return false;
        };
    }

    if(currDepth == buffer){
        return false;
    }

    path.push_back({curRow, curCol});

    for(int i = 0; i < path.size(); i++){
        cout << board[path[i].row][path[i].col] << " ";
    }
    cout << endl;

    bool isExist;
    if(isHorizontal){
        for(int i = 1; i < board.size(); i++){
            isExist =   dfs(board, path, curRow + i, curCol, currDepth + 1, buffer, false) || 
                        dfs(board, path, curRow - i, curCol, currDepth + 1, buffer, false);
        }
    }
    else{
        for(int i = 1; i < board[0].size();i++){
            isExist =   dfs(board, path, curRow, curCol + i, currDepth + 1, buffer, true) || 
                        dfs(board, path, curRow, curCol - i, currDepth + 1, buffer, true);
        }

    }
    path.pop_back();
    return isExist;
}

int main(){

    vector<vector<string>> matrix; 
    vector<int> currentCombination;

    matrix = {
        {"AB", "CD", "EF", "GH"}, 
        {"5F", "6T", "GT", "6D"}, 
        {"89", "OP", "PO", "DF"}, 
        {"45", "7Y", "8U", "02"}
    };

    vector<Path> path; 
    for(int i = 0; i < matrix[0].size(); i++){
        dfs(matrix, path, 0, i, 0, 10, true);
    }
    // backtrack(matrix, currentCombination, 0, 0, 4);

    return 0;
}