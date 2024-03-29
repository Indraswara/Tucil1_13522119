#include <iostream> 
#include <string> 
#include <limits>
#include <vector> 
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <climits>
#include <sys/stat.h>

using namespace std; 
using namespace std::chrono;

int maxPrize = 0;
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

bool isExist(string name){
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

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

    return -1;
}

int inputInt(string msg){
    string input; 
    while (true) {
        cout << msg;
        cin >> input;
        try {
            int number = stoi(input);

            if(number >= 0){
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

    return -1;
}

string randomToken(vector<string> tokens){
    int index = 0 + (rand() % (tokens.size() - 1));
    return tokens[index];
}

vector<vector<string>> board(int cols, int rows, vector<string> token){
    vector<vector<string>> board; 

    for(int i = 0; i < rows; i++){
        vector<string> temp; 
        for(int j = 0; j < cols; j++){
            temp.push_back(randomToken(token));
        }
        board.push_back(temp);
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
        int value = 1 + (rand() % 100);
        result.push_back({temp, value});
    }
    return result;
}

void comparing(vector<string>& currentCombination, vector<Reward>& matrix, vector<Path> path) {
    int point = 0; 
    for (auto& reward : matrix) {
        vector<string>& combination = reward.sequence;

        auto it = search(currentCombination.begin(), currentCombination.end(), combination.begin(), combination.end());
        if (it != currentCombination.end()) {
            point += reward.prize;
            if(point > maxPrize){
                finalePath.clear();
                maxPrize = point;
                minMove = path.size();
                // minMove = depth;
                for(int i = 0; i < path.size(); i++){
                    finalePath.push_back({path[i].row, path[i].col, currentCombination[i]});
                }
            }
            if(point == maxPrize && path.size() < minMove){
                finalePath.clear(); 
                minMove = path.size();
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
    comparing(currentPos, base, path);

    if(currDepth == buffer){
        return;
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

void file(string filename, auto duration){
    filename += ".txt";
    fstream savingData; 
    savingData.open(filename, ios::out);
    
    savingData << maxPrize << endl;
    for(int i =0; i < finalePath.size(); i++){
        savingData << finalePath[i].finalToken << " ";
    }
    savingData << "\n";
    for(int i = 0; i < finalePath.size(); i++){
        savingData << "(" << finalePath[i].col + 1 << "," << finalePath[i].row + 1 << ")" << "\n";
    }
    
    savingData << "\n";
    savingData << duration << " ms";
    savingData.close();
}

void saving(auto duration){
    string fileName; 
    string filePath;
    cout << "simpan hasil dalam bentuk file? (y/n) ";
    char choose; 
    cin >> choose;
    while(choose != 'y' && choose != 'n' && choose != 'Y' && choose != 'N'){
        cout << "input invalid, masukkan ulang" << endl;
        cout << ">> "; 
        cin >> choose; 
    }
    if(choose == 'y' || choose == 'Y'){
        cout << "Masukkan nama file: "; 
        filePath = "./test/"; 
        cin >> fileName; 
        filePath += fileName;
        file(filePath, duration);
        cout << fileName << " telah tersimpan di folder test" << endl;
    }
}

void isFound(auto duration, vector<vector<string>> board, vector<Reward> rewardSequence){
    if(maxPrize < 0){
        maxPrize = 0;
    }
    if(minMove == INT_MAX){
        minMove = 0;
    }
    if(finalePath.size() != 0){
        cout<< " _______   ______    __    __  .__   __.  _______  " << endl
            << "|   ____| /  __  \\  |  |  |  | |  \\ |  | |       \\ " << endl
            << "|  |__   |  |  |  | |  |  |  | |   \\|  | |  .--.  |" << endl
            << "|   __|  |  |  |  | |  |  |  | |  . `  | |  |  |  |" << endl
            << "|  |     |  `--'  | |  `--'  | |  |\\   | |  '--'  |" << endl
            << "|__|      \\______/   \\______/  |__| \\__| |_______/ " << endl;
            cout << endl;
        cout << "Result" << endl;
        cout << "Matriks: " << endl;
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Reward Sequence: " << endl;
        for(int i = 0; i < rewardSequence.size(); i++){
            for(int j = 0; j < rewardSequence[i].sequence.size(); j++){
                cout << rewardSequence[i].sequence[j] << " ";
            }
            cout << "(" << rewardSequence[i].prize << ")" << endl;
        }
        cout << "Token combination: ";
        for(int i = 0; i < finalePath.size(); i++){
            cout << finalePath[i].finalToken << " "; 
        }       
        cout << endl;
        for(int i = 0; i < finalePath.size(); i++){
            cout << "(" << finalePath[i].col + 1 << "," << finalePath[i].row + 1 << ")" << endl;
        }
    }
    else{
        cout << endl;
        cout << "##    ##  #######  ########    ########  #######  ##     ## ##    ## ########" << endl;
        cout << "###   ## ##     ##    ##       ##       ##     ## ##     ## ###   ## ##     ##" << endl;
        cout << "## ## ## ##     ##    ##       ######   ##     ## ##     ## ## ## ## ##     ##" << endl;
        cout << "##  #### ##     ##    ##       ##       ##     ## ##     ## ##  #### ##     ##" << endl;
        cout << "##    ##  #######     ##       ##        #######   #######  ##    ## ########" << endl;
        cout << endl;
    }
    cout << "Optimum reward: " << endl;
    cout << "total prize: " <<  maxPrize << endl;
    cout  << "minimum buffer taken: " << minMove << endl;

    cout << "\nExecution Time: " << duration.count() << " milliseconds" << endl;
    saving(duration.count());
}

int main(){
    cout<< "                __                        " << endl
        << " _      _____  / /________  ____ ___  ___ " << endl
        << "| | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\" << endl
        << "| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/" << endl
        << "|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/ " << endl;

    while(true){
        cout << "    ____                       __           " << endl
              << "   / __ )________  ____ ______/ /_          " << endl
              << "  / __  / ___/ _ \\/ __ `/ ___/ __ \\         " << endl
              << " / /_/ / /  /  __/ /_/ / /__/ / / /         " << endl
              << "/_____/_/   \\___/\\__,_/\\___/_/ /_/      __" << endl
              << "   / __ \\_________  / /_____  _________  / /" << endl
              << "  / /_/ / ___/ __ \\/ __/ __ \\/ ___/ __ \\/ / " << endl
              << " / ____/ /  / /_/ / /_/ /_/ / /__/ /_/ / /  " << endl
              << "/_/   /_/   \\____/\\__/\\____/\\___/\\____/_/   " << endl;
        //reset global variable
        cout << "choose input method: " << endl;
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
            cout << "Token harus kombinasi 1 angka 1 huruf, 2 angka, atau 2 huruf" << endl;
            cout << "Contoh: A8, BG, 97" << endl;
            cout << "Masukkan token: ";
            for(int i = 0; i < jumlahTokenUnik; i++){
                string seq; 
                while(true){
                    cin >> seq; 
                    if(seq.size() != 2){
                        cout << "Panjang token tidak sama dengan 2" << endl;
                        cout << "Masukkan token ulang: ";
                    }
                    else{
                        break;
                    }
                }
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
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            // result 
            isFound(duration, boardGame, rewardSequence);
        }

        else if(input == 2){
            bool isValid = 1;
            vector<vector<string>> matriks;
            string line; 
            string filePath = "test/";
            string fileName;
            vector<string> lines;
            fstream myData;
            
            cout << "Pastikan file ada di dalam folder test" << endl;
            cout << "tambahkan ekstensi file\ncontoh: data.txt\n";
            cout << "Masukkan nama file: "; 
            cin >> fileName; 
            filePath += fileName; 
            while(!isExist(filePath)){
                cout << "file tidak ada di folder test" << endl; 
                cout << "Masukkan nama file: "; 
                cin >> fileName; 
                filePath = "test/"; 
                filePath += fileName;
            }
            cout << "\n\nMemproses file "  << fileName << endl;

            myData.open(filePath); 
            if(myData.is_open()){
                while(getline(myData, line)){
                    lines.push_back(line);
                }
            }
            myData.close();
            try{
                buffer = stoi(lines[0]);
            }catch(const invalid_argument& e){
                cerr << "file tidak sesuai format: buffer bukanlah angka";
                isValid = 0;
            }
            string tempString; 
            int lengthBreak;
            for(int i = 0; i < lines[1].size(); i++){
                if(lines[1][i] == ' '){
                    lengthBreak = i;
                    break;
                }
                tempString += (lines[1][i]);
            }

            try{
                rowsMatriks = stoi(tempString);
            }catch(const invalid_argument& e){
                cerr << "file tidak sesuai format: rowsMatriks bukanlah angka\n";
                isValid = 0;
            }
            tempString.clear(); 
            for(int i = lengthBreak + 1; i < lines[1].size(); i++){
                if(lines[1][i] == ' ' || lines[1][i] == '\r'){
                    break;
                }
                tempString += (lines[1][i]);
            }

            try{
                colsMatriks = stoi(tempString);
                tempString.clear();
            }catch(const invalid_argument& e){
                cerr << "file tidak sesuai format: colsMatriks bukanlah angka\n";
                isValid = 0;
            }
            
            string myStr;
            vector<string> temp; 
            if(rowsMatriks > lines.size()){
                cout << "file tidak sesuai format: rowMatriks terlalu banyak\n";
                isValid = 0;
            }

            if(isValid){
                for(int i = 2; i <= rowsMatriks + 1; i++){
                    if(isValid){
                        temp.clear();
                        for(int j = 0; j < lines[i].size(); j++){
                            if(isValid){
                                if(lines[i][j] != ' '){
                                    myStr.push_back(lines[i][j]);
                                    if(myStr.back() == '\r'){
                                        myStr.pop_back();
                                    }
                                }
                                if(lines[i][j] == ' ' || j == lines[i].size() - 1){
                                    if(myStr.size() != 2){
                                        isValid = 0;
                                        cout << "file tidak sesuai format: token matriks tidak sesuai" << endl;
                                        break;
                                    }
                                    temp.push_back(myStr);
                                    myStr.clear();
                                }
                            }
                            
                        }
                        matriks.push_back(temp);
                        if(matriks[i-2].size() != colsMatriks){
                            cout << "file tidak sesuai format: jumlah kolom tidak sesuai dengan input" << endl;
                            isValid = 0;
                            break;
                        }
                    }
                }
            }
            
            if(isValid){
                try{
                    jumlahSekuens = stoi(lines[rowsMatriks + 2]);
                }catch(const invalid_argument& e){
                    cerr << "file tidak sesuai format: jumlah sekuens bukanlah angka";
                    isValid = 0;
                }
            }

            vector<Reward> rewardSequence; 
            if(isValid){
                for(int f = rowsMatriks + 3; f < lines.size(); f++){
                    Reward tempReward; 
                    //ini reward
                    if(isValid){
                        temp.clear();
                        //ini sequence
                        for(int j = 0; j < lines[f].size(); j++){
                            if(lines[f][j] != ' '){
                                myStr.push_back(lines[f][j]);
                                if(myStr.back() == '\r'){
                                    myStr.pop_back();
                                }
                            }
                            if(lines[f][j] == ' ' || j == lines[f].size() - 1){
                                if(myStr.size() != 2){
                                    cout << "file tidak sesuai format: sequence token tidak berjumlah 2" << endl;
                                    isValid = 0;
                                }
                                temp.push_back(myStr);
                                myStr.clear();
                            }
                        }
                        tempReward.sequence = temp;

                        f += 1; 
                        try{
                            tempReward.prize = stoi(lines[f]); 
                        }
                        catch(const invalid_argument& e){
                            cerr << "file tidak sesuai format: baris matriks tidak sesuai dengan input" << endl;
                            cerr << "file tidak sesuai format: reward sequence bukanlah angka" << endl;
                            isValid = 0;
                        }
                        rewardSequence.push_back(tempReward);
                    }
                }
            }
            
            if(rewardSequence.size() != jumlahSekuens && isValid){
                cout << "file tidak sesuai format: jumlah sekuens tidak sesuai" << endl;
                isValid = 0;
            }
            
            if(isValid){
                // main execution  
                auto start = high_resolution_clock::now();
                vector<string> currentPos; 
                vector<Path> path;
                for(int i = 0; i < colsMatriks; i++){
                    dfs(matriks, rewardSequence, path, currentPos, 0, i, 0, buffer, true);
                }
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                isFound(duration, matriks, rewardSequence);

            }else{
                cout << "\ncek kesalahan satu per satu" << endl;
            }

            // result 
        }
        else{
            break;
        }
    }
    return 0;
}