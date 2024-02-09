#include <iostream> 
#include <string> 
#include <limits>
#include <vector> 
#include <algorithm>
#include <random>
#include <chrono>

using namespace std; 
using namespace std::chrono;

int maxPrize = 0;
// int minMove = INT_MAX; 
int checker = 0;

struct Path{
    int row; 
    int col; 
};


struct Reward{
    vector<string> sequence; 
    int prize;
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

void comparing(vector<Reward> Reward, vector<string> current){
    int length; 
    int point = 0;
    for(int i = 0; i < Reward.size(); i++){
        length = 0;
        for(int j = 0; j < current.size(); j++){
            for(int k = 0; k < Reward[i].sequence.size(); k++){
                if(Reward[i].sequence[k] == current[j]){
                    length++;
                    j++;
                    if(length == Reward[i].sequence.size()){
                        point += Reward[i].prize;
                    }
                }
            }
        }
        if(point > maxPrize){
            maxPrize = point;
        }
    }
}

void comparing2(vector<string>& currentCombination, vector<Reward>& matrix) {
    int point = 0; 
    for (auto& reward : matrix) {
        vector<string>& combination = reward.sequence;

        auto it = search(currentCombination.begin(), currentCombination.end(), combination.begin(), combination.end());
        if (it != currentCombination.end()) {
            point += reward.prize;
            if(point > maxPrize){
                maxPrize = point;
            }
        }
    }
}

void dfs(vector<vector<string>>& board, vector<Reward> base, vector<Path> path, vector<string> currentPos, int curRow, int curCol, int currDepth, int buffer, bool isHorizontal){
    if(curRow < 0 || curRow >= board.size() || curCol < 0 || curCol >= board[0].size()){
        return;
    }

    for(int i = 0; i < path.size(); i++){
        if(curRow == path[i].row && curCol == path[i].col){
            return;
        };
    }

    path.push_back({curRow, curCol});
    currentPos.push_back(board[curRow][curCol]);
    if(currentPos.size() == buffer){
        comparing2(currentPos, base);
    }

    if(currDepth == buffer){
        return;
    }



    if(maxPrize == 50 && checker == 0){
        for(int i = 0; i < path.size(); i++){
            cout << currentPos[i] <<  " ";
        }
        for(int j = 0; j < path.size(); j++){
            cout << "(" << path[j].col + 1 << "," << path[j].row + 1 << ")" << endl;
        }
        cout << endl;
        checker = 1;
    }

    if(isHorizontal){
        for(int i = 1; i < board.size(); i++){
            dfs(board, base, path, currentPos, curRow + i, curCol, currDepth + 1, buffer, false);
            dfs(board, base, path, currentPos, curRow - i, curCol, currDepth + 1, buffer, false);
        }
    }
    else{
        for(int i = 1; i < board[0].size();i++){
            dfs(board, base, path, currentPos, curRow, curCol + i, currDepth + 1, buffer, true);
            dfs(board, base, path, currentPos, curRow, curCol - i, currDepth + 1, buffer, true);
        }
    }
    path.pop_back();
    currentPos.pop_back();
    
}

void cli(int jumlahTokenUnik, vector<string> token, int rowsMatriks, int colsMatriks, int jumlahSekuens, int maksSekuens){

}

void file(string filename){

}


int exe(){
    int jumlahTokenUnik, buffer, rowsMatriks, colsMatriks, jumlahSekuens, maksSekuens; 
    vector<string> token; 

    buffer = 7; 
    rowsMatriks = 6; 
    colsMatriks = 6; 
    vector<vector<string>> matriks = {
        {"7A", "55", "E9", "E9", "1C", "55"},
        {"55", "7A", "1C", "7A", "E9", "55"},
        {"55", "1C", "1C", "55", "E9", "BD"},
        {"BD", "1C", "7A", "1C", "55", "BD"},
        {"BD", "55", "BD", "7A", "1C", "1C"},
        {"1C", "55", "55", "7A", "55", "7A"}
    };
    jumlahSekuens = 3; 
    vector<Reward> sequence = {
        {{"BD", "E9", "1C"}, 15}, 
        {{"BD", "7A", "BD"}, 20}, 
        {{"BD", "1C", "BD", "55"}, 30}
    };

    vector<string> currentPos; 
    vector<Path> path;
    for(int i = 0; i < colsMatriks; i++){
        dfs(matriks, sequence, path, currentPos, 0, i, 0, buffer, true);
    }
    cout << maxPrize << endl;
    return 0;
}


int main(){
    auto start = high_resolution_clock::now();

    exe();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "\nExecution Time: " << duration.count() << " milliseconds" << endl;
    return 0;
}

// int main(){
//     cout << "permainan" << endl; 
//     while(true){
//         int jumlahTokenUnik, buffer, rowsMatriks, colsMatriks, jumlahSekuens, maksSekuens; 
//         vector<string> token; 
//         cout << "1. cli" << endl; 
//         cout << "2. file" << endl; 
//         cout << "3. quit" << endl; 
//         int input = inputer(1, 3);
//         if(input == 1){
//             jumlahTokenUnik = inputInt("Masukkan jumlah token unik: "); 
//             buffer = inputInt("Masukkan jumlah buffer: ");
//             rowsMatriks = inputInt("Masukkan jumlah baris matriks: "); 
//             colsMatriks = inputInt("Masukkan jumlah kolom matriks: "); 
//             jumlahSekuens = inputInt("Masukkan total sekuens: "); 
//             maksSekuens = inputInt("Masukkan jumlah maksimum sekuens: ");
            
//             for(int i = 0; i < jumlahTokenUnik; i++){
//                 string seq; 
//                 cin >> seq; 
//                 token.push_back(seq);
//             }

//             vector<vector<string>> boardGame = board(rowsMatriks, colsMatriks, token);

//             for(int i =0 ; i < jumlahSekuens; i++){
//                 vector<string> sequence; 
//                 sequence = seqGenerator(maksSekuens, token);
//                 for(int j = 0 ; j < sequence.size(); j++){
//                     cout << sequence[j] << " ";
//                 }
//                 cout << endl;
//             }


//         }
//         else if(input == 2){
//             cout << "file" << endl;
//         }
//         else{
//             break;
//         }
//     }
//     return 0;

// }