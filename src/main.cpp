#include <iostream> 
#include <string> 
#include <limits>
#include <vector> 
#include <algorithm>
#include <random>

using namespace std; 


struct Path{
    int row; 
    int col; 
};

int inputer(int awal, int akhir){
    string input; 
    while (true) {
        cout << ">> ";
        cin >> input;
        try {
            int number = stoi(input);

            if(number >= awal && number <= akhir){
                return number;
            } 
            else{
                cout << "Input invalid, masukkan ulang" << endl;
            }
        } 
        catch (invalid_argument const &e) {
            cout << "Invalid input, masukkan ulang dengan angka" << endl;
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> input;
}

int inputInt(string msg){
    int input;
    cout << msg; 
    cin >> input; 
    return input;
}

string random_string(int length){
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

vector<vector<string>>board(int cols, int rows, vector<string> token){
    vector<vector<string>> board; 

    for(int i = 0; i < rows; i++){
        vector<string> temp; 
        for(int j = 0; j < cols; j++){
            temp.push_back(random_string(2));
        }
        board.push_back(temp);
    }

    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> rowDis(0, rows - 1); 
    uniform_int_distribution<int> colDis(0, cols - 1);

    for(int i = 0; i < token.size(); i++){
        int row = rowDis(gen); 
        int col = colDis(gen); 
        cout << row << " " << col << endl;
        board[row][col] = token[i];
    }
    return board;
}

vector<string> seqGenerator(int maksSequence, vector<string> token){
    int min = 2;
    vector<string> result;
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> resultDis(0, token.size() - 1); 
    uniform_int_distribution<int> resultLength(min, maksSequence);
    int length = resultLength(gen);
    for(int i = 0 ; i < length; i++){
        int index = resultDis(gen);
        result.push_back(token[index]);
        // cout << gen << index << endl;
    }
    return result;
}

void comparing(vector<vector<string>> base, vector<string> current){
    int length; 
    for(int i = 0; i < base.size(); i++){
        length = 0;
        for(int k = 0; k < base[i].size(); k++){
            for(int j = 0; j < current.size(); j++){
                if(base[i][k] == current[j]){
                    length++;
                    cout << "ketemu: " << base[i][k] << endl;
                    if(length == base[i].size()){
                        cout << "yey dapat point" << endl;
                    }
                }
            }
        }
    }
}

void dfs(vector<vector<string>>& board, vector<Path> path, vector<string> currentPos, int curRow, int curCol, int currDepth, int buffer, bool isHorizontal){

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

    // currentPos.push_back(board[path[curRow].row][path[curCol].col])
    // if(currentPos.size() == buffer){
    // }

    path.push_back({curRow, curCol});

    vector<string> base; 
    for(int i = 0; i < path.size(); i++){
        // cout << board[path[i].row][path[i].col] << " ";
        base.push_back(board[path[i].row][path[i].col]);
        cout << base[i] << endl;

    }
    cout << endl;

    bool isExist;
    if(isHorizontal){
        for(int i = 1; i < board.size(); i++){
            dfs(board, path, currentPos, curRow + i, curCol, currDepth + 1, buffer, false);
            dfs(board, path, currentPos, curRow - i, curCol, currDepth + 1, buffer, false);
        }
    }
    else{
        for(int i = 1; i < board[0].size();i++){
            dfs(board, path, currentPos, curRow, curCol + i, currDepth + 1, buffer, true);
            dfs(board, path, currentPos, curRow, curCol - i, currDepth + 1, buffer, true);
        }

    }
    path.pop_back();
}

void cli(int jumlahTokenUnik, vector<string> token, int rowsMatriks, int colsMatriks, int jumlahSekuens, int maksSekuens){

}

void file(string filename){

}

int main(){
    cout << "permainan" << endl; 
    while(true){
        int jumlahTokenUnik, buffer, rowsMatriks, colsMatriks, jumlahSekuens, maksSekuens; 
        vector<string> token; 
        cout << "1. cli" << endl; 
        cout << "2. file" << endl; 
        cout << "3. quit" << endl; 
        int input = inputer(1, 3);
        if(input == 1){
            jumlahTokenUnik = inputInt("Masukkan jumlah token unik: "); 
            buffer = inputInt("Masukkan jumlah buffer: ");
            rowsMatriks = inputInt("Masukkan jumlah baris matriks: "); 
            colsMatriks = inputInt("Masukkan jumlah kolom matriks: "); 
            jumlahSekuens = inputInt("Masukkan total sekuens: "); 
            maksSekuens = inputInt("Masukkan jumlah maksimum sekuens: ");
            
            for(int i = 0; i < jumlahTokenUnik; i++){
                string seq; 
                cin >> seq; 
                token.push_back(seq);
            }

            // vector<vector<string>> boardGame = board(rowsMatriks, colsMatriks, token);


            // cout << jumlahTokenUnik << endl; 
            // cout << buffer << endl;
            // cout << rowsMatriks << endl; 
            // cout << colsMatriks << endl; 
            // cout << jumlahSekuens << endl; 
            // cout << maksSekuens << endl;
            // for(int i = 0; i < jumlahTokenUnik; i++){
            //     cout << token[i] << " ";
            // }
            // for(int i = 0; i < boardGame.size(); i++){
            //     for(int j = 0; j < boardGame[i].size(); j++){
            //         cout << boardGame[i][j] << " ";
            //     }
            //     cout << endl;
            // }

            // for(int i =0 ; i < jumlahSekuens; i++){
            //     vector<string> sequence; 
            //     sequence = seqGenerator(maksSekuens, token);
            //     for(int j = 0 ; j < sequence.size(); j++){
            //         cout << sequence[j] << " ";
            //     }
            //     cout << endl;
            // }


        }
        else if(input == 2){
            cout << "file" << endl;
        }
        else{
            break;
        }
    }
    return 0;

}