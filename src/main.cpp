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
int checker = 0;
int minMove = INT_MAX; 

struct Path{
    int row; 
    int col; 
};

struct Reward{
    vector<string> sequence; 
    int prize;
};

struct PathVal{
    int row; 
    int col; 
    string finalToken;
};

vector<Path> globalPath; 
vector<string> globalCurrPos;
vector<PathVal> finalePath;

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
    string str(length,0);
    generate_n( str.begin(), length, randchar );
    return str;
}

vector<vector<string>>board(int cols, int rows, vector<string> token){
    vector<vector<string>> board; 

    for(int i = 0; i < rows; i++){
        vector<string> temp; 
        for(int j = 0; j < cols; j++){
            temp.push_back(random_string(token[0].size()));
        }
        board.push_back(temp);
    }

    // place token onto the matrix as a safe way; 
    random_device rd; 
    mt19937 gen(rd());
    uniform_int_distribution<int> rowDis(0, rows - 1); 
    uniform_int_distribution<int> colDis(0, cols - 1);

    for(int i = 0; i < token.size(); i++){
        int row = rowDis(gen); 
        int col = colDis(gen);
        //cout << row << " " << col << endl;
        board[row][col] = token[i];
    }
    return board;
}

vector<Reward> seqGenerator(int maksSequence, vector<string> token, int jumlahSequence){

    int min = 2;
    vector<Reward> result;
    for(int i = 0; i < jumlahSequence; i++){
        vector<string> temp;
        random_device rd; 
        mt19937 gen(rd());
        uniform_int_distribution<int> resultDis(0, token.size() - 1); 
        uniform_int_distribution<int> resultLength(min, maksSequence);
        int length = resultLength(gen);
        for(int i = 0 ; i < length; i++){
            int index = resultDis(gen);
            temp.push_back(token[index]);
            // cout << gen << index << endl;
        }
        int value = 1 + (rand() & 100);
        result.push_back({temp, value});
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

void comparing2(vector<string>& currentCombination, vector<Reward>& matrix, vector<Path> path, int depth) {
    int point = 0; 
    for (auto& reward : matrix) {
        vector<string>& combination = reward.sequence;

        auto it = search(currentCombination.begin(), currentCombination.end(), combination.begin(), combination.end());
        if (it != currentCombination.end()) {
            point += reward.prize;
            if(point > maxPrize && depth < minMove){
                finalePath.clear();
                maxPrize = point;
                minMove = depth;
                for(int i = 0; i < path.size(); i++){
                    finalePath.push_back({path[i].row, path[i].col, currentCombination[i]});
                }
            }
        }
    }
}

void dfs(vector<vector<string>>& board, vector<Reward> base, vector<Path> path, vector<string> currentPos, int curRow, int curCol, int currDepth, int buffer, bool isHorizontal){
    int prizeTotal = 0;
    for(int i = 0; i < base.size(); i++){
        prizeTotal += base[i].prize;
    }
    if(prizeTotal == maxPrize){
        return;
    }

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
    comparing2(currentPos, base, path, currDepth);

    if(currDepth == buffer){
        return;
    }
    // if(currentPos.size() == buffer){
    // }

    //debug
    // if(maxPrize == 50 && checker == 0){
    //     for(int i = 0; i < path.size(); i++){
    //         cout << currentPos[i] <<  " ";
    //     }
    //     for(int j = 0; j < path.size(); j++){
    //         cout << "(" << path[j].col + 1 << "," << path[j].row + 1 << ")" << endl;
    //     }
    //     cout << endl;
    //     checker = 1;
    // }

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

void file(string filename){

}


int test(){
    globalCurrPos.clear();
    globalPath.clear();
    finalePath.clear();
    maxPrize = INT_MIN; 
    minMove = INT_MAX;
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

    vector<vector<string>> matriks2 = {
        {"AB", "56", "87", "AB", "FF", "FF"}, 
        {"87", "FF", "C7", "87", "C7", "FF"}, 
        {"C7", "AB", "C7", "AB", "FF", "C7"}, 
        {"87", "87", "C7", "FF", "FF", "FF"},
        {"56", "56", "FF", "FF", "FF", "AB"},
        {"87", "C7", "FF", "56", "87", "AB"}
    };
    jumlahSekuens = 3; 
    vector<Reward> sequence = {
        {{"BD", "E9", "1C"}, 15}, 
        {{"BD", "7A", "BD"}, 20}, 
        {{"BD", "1C", "BD", "55"}, 30}
    };
    jumlahSekuens = 5; 
    vector<Reward> sequence2 = {
        {{"56", "C7", "FF"}, 49},
        {{"FF", "C7", "C7", "AB"}, 97},
        {{"56", "AB", "87", "AB", "87"}, 45},
        {{"87", "AB"}, 74},
        {{"56", "FF", "C7", "87", "C7"}, 45}
    };

    vector<string> currentPos; 
    vector<Path> path;
    for(int i = 0; i < colsMatriks; i++){
        dfs(matriks2, sequence2, path, currentPos, 0, i, 0, buffer, true);
    }
    cout << "maxprize: " << maxPrize << endl;
    cout << "minimal move: " << minMove << endl;
    return 0;
}



int main(){
    auto start = high_resolution_clock::now();

    test();

    for(int i = 0; i < finalePath.size(); i++){
        cout << finalePath[i].finalToken << " "; 
    }
    cout << endl; 
    for(int i = 0; i < finalePath.size(); i++){
        cout << "(" << finalePath[i].col + 1 << "," << finalePath[i].row + 1 << ")" << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "\nExecution Time: " << duration.count() << " milliseconds" << endl;
    return 0;
}

int main(){
    cout << "Breach Protocol Game" << endl; 
    while(true){
        //reset global variable
        globalCurrPos.clear();
        globalPath.clear();
        finalePath.clear();
        maxPrize = INT_MIN; 
        minMove = INT_MAX;

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
            cout << "Masukkan token: ";
            for(int i = 0; i < jumlahTokenUnik; i++){
                string seq; 
                cin >> seq; 
                token.push_back(seq);
            }

            // generate sequence reward and matriks board
            vector<vector<string>> boardGame = board(rowsMatriks, colsMatriks, token);
            vector<Reward> rewardSequence = seqGenerator(maksSekuens, token, jumlahSekuens);

            // reward debug
            for(int i = 0; i < rewardSequence.size(); i++){
                cout << "{{";
                for(int j = 0 ; j < rewardSequence[i].sequence.size(); j++){
                    cout << rewardSequence[i].sequence[j];
                    if(j != rewardSequence[i].sequence.size() - 1){
                        cout << ",";
                    }
                }
                cout << "}, ";
                cout << rewardSequence[i].prize;
                cout << "}";
                cout << endl;
            }

            auto start = high_resolution_clock::now();
            // main execution  
            vector<string> currentPos; 
            vector<Path> path;
            for(int i = 0; i < colsMatriks; i++){
                dfs(boardGame, rewardSequence, path, currentPos, 0, i, 0, buffer, true);
            }

            // result 
            cout << "Result" << endl;
            for(int i = 0; i < finalePath.size(); i++){
                cout << finalePath[i].finalToken << " "; 
            }       
            cout << endl;
            for(int i = 0; i < finalePath.size(); i++){
                cout << "(" << finalePath[i].col + 1 << "," << finalePath[i].row + 1 << ")" << endl;
            }
            cout << "Optimum reward: " << endl;
            cout << "total prize: " <<  maxPrize << endl;
            cout << "minimum buffer taken: " << minMove + 1 << endl;

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);

            cout << "\nExecution Time: " << duration.count() << " milliseconds" << endl;
            
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