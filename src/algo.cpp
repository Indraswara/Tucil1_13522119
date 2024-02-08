#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>


using namespace std;

struct Path{
    int row;
    int col;
};

struct Reward{
    vector<string> sequence; 
    int prize; 
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

void dfs(vector<vector<string>>& board, vector<Path> path, int curRow, int curCol, int currDepth, int buffer, bool isHorizontal){

    if(curRow < 0 || curRow >= board.size() || curCol < 0 || curCol >= board[0].size()){
        return;
    }

    for(int i = 0; i < path.size(); i++){
        if(curRow == path[i].row && curCol == path[i].col){
            return;
        };
    }

    if(currDepth == buffer){
        return;
    }

    path.push_back({curRow, curCol});

    for(int i = 0; i < path.size(); i++){
        cout << board[path[i].row][path[i].col] << " ";
    }
    cout << endl;

    bool isExist;
    if(isHorizontal){
        for(int i = 1; i < board.size(); i++){
            dfs(board, path, curRow + i, curCol, currDepth + 1, buffer, false);
            dfs(board, path, curRow - i, curCol, currDepth + 1, buffer, false);
        }
    }
    else{
        for(int i = 1; i < board[0].size();i++){
            dfs(board, path, curRow, curCol + i, currDepth + 1, buffer, true);
            dfs(board, path, curRow, curCol - i, currDepth + 1, buffer, true);
        }

    }
    path.pop_back();
}

void comparing(vector<Reward> base, vector<string> current){
    int length; 
    int point = 0;
    for(int i = 0; i < base.size(); i++){
        length = 0;
        for(int k = 0; k < base[i].sequence.size(); k++){
            for(int j = 0; j < current.size(); j++){
                if(base[i].sequence[k] == current[j]){
                    length++;
                    cout << "ketemu: " << base[i].sequence[k] << endl;
                    if(length == base[i].sequence.size()){
                        cout << "yey dapat point" << endl;
                        point += base[i].prize;
                    }
                }
            }
        }
    }
    cout << point << endl;
    cout << length;
}

int main(){

    // vector<vector<string>> matrix; 
    vector<string> currentCombination = {"AP", "CD", "EF", "GH"};

    vector<Reward> matrix;
    matrix = {
        {{"AP", "CD", "EF", "GH"}, 100}, 
        {{"CD", "EF"}, 20}, 
        {{"89", "OP", "PO", "DF"}, 30}, 
        {{"45", "7Y", "8U", "02"}, 25}
    };

    
    comparing(matrix, currentCombination);
    // for(int i = 0; i < matrix[0].size(); i++){
    //     dfs(matrix, path, 0, i, 0, 10, true);
    // }


    

    return 0;
}
