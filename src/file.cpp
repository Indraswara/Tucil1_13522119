#include <iostream> 
#include <fstream>
#include <string> 
#include <vector>
using namespace std; 

struct Reward{
    vector<string> sequence; 
    int prize; 
};

struct Path{
    int row; 
    int col; 
};


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

int main(){
    int jumlahTokenUnik, buffer, rowsMatriks, colsMatriks, jumlahSekuens, maksSekuens; 
    vector<vector<string>> matriks;
    string line; 
    vector<string> lines;
    fstream myData;
    myData.open("data.txt"); 

    if(myData.is_open()){
        while(getline(myData, line)){
            lines.push_back(line);
            cout << line << "\n";
        }

    }
    myData.close();

    cout << "translate" << endl;
    jumlahTokenUnik = stoi(lines[0]); 
    rowsMatriks = lines[1][0] - '0';
    colsMatriks = lines[1][2] - '0';

    string myStr;
    vector<string> temp; 

    for(int i = 2; i <= rowsMatriks + 1; i++){
        temp.clear();
        // cout << lines[i].size() << endl;
        for(int j = 0; j < lines[i].size(); j++){
            // cout << "lines" << lines[i].size() << endl;
                // cout << lines[i][j];
                if(lines[i][j] != ' '){
                    myStr.push_back(lines[i][j]);
                }
                if(lines[i][j] == ' ' || j == lines[i].size() - 1){
                    temp.push_back(myStr);
                    myStr.clear();
                }
        }
        matriks.push_back(temp);
    }

    jumlahSekuens = stoi(lines[rowsMatriks + 2]);
    vector<Reward> rewardSequence; 
    for(int f = rowsMatriks + 3; f < lines.size(); f++){
        //ini reward
        Reward tempReward; 
        temp.clear();
        myStr.clear();

        //ini sequence
        for(int j = 0; j < lines[f].size(); j++){
            if(lines[f][j] != ' '){
                myStr.push_back(lines[f][j]);
            }
            if(lines[f][j] == ' ' || j == lines[f].size() - 1){
                temp.push_back(myStr);
                myStr.clear();
            }
        }
        tempReward.sequence = temp;

        f += 1; 
        tempReward.prize = stoi(lines[f]); 
        rewardSequence.push_back(tempReward);
    }

    cout << jumlahTokenUnik << endl;
    cout << rowsMatriks << endl;
    cout << colsMatriks << endl;
    cout << "{" << endl;
    for(int i = 0 ; i < rowsMatriks; i++){
        cout << "{";
        for(int j = 0; j < colsMatriks; j++){
            cout << matriks[i][j] << "";
            if(j != colsMatriks - 1){
                cout << ",";
            }
        }
        cout << "}";
        
        if(i != rowsMatriks - 1){
            cout << "," << endl;
        }
    }
    cout << "\n}" << endl;
    cout << matriks.size() << endl;
    cout << matriks[0].size() << endl;

    for(int i = 0; i < rewardSequence.size(); i++){
        for(int j = 0; j < rewardSequence[i].sequence.size();j++){
            cout << rewardSequence[i].sequence[j] << " ";
        }
        cout << rewardSequence[i].prize << endl; 
    }

    for(int i = 0; i < matriks[2].size(); i++){
        cout << matriks[2][i] << " ";
    }
    // vector<Path> path;
    // for(int i = 0; i < colsMatriks; i++){
    //     dfs(matriks, path, 0, i, 0, 7, false);
    // }

    return 0;
}