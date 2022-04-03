#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

struct cell {
    float prob; //the index at which the string is held in M
    string token; //the string represented by the cell
};

struct word {
    int index;  //the index the word is held at in M
    float occ;    //tracks times the word has occurred, for calculations
};

void genMatrix(vector<vector<cell>>& M, map<string, word>& tokens, string filename) {
    string last = "";
    ifstream infile(filename);

    while (!infile.eof()) {
        string tok;
        infile >> tok;

        if (tokens.find(tok) == tokens.end()) { //if key is not in map
            tokens.insert(make_pair(tok, word{ (int)M.size(), 1 })); //insert string into map and graph
            vector<cell> tempArr;
            M.push_back(tempArr);
            cell tempCell{ 0.0, tok };
            M[tokens[last].index].push_back(tempCell);
        }
        for (int i = 0; i < M[tokens[last].index].size(); i++) { //find current token in parent's vector and increment count
            if (M[tokens[last].index][i].token == tok) {
                M[tokens[last].index][i].prob += 1;
                tokens[last].occ += 1;
            }
        }
        last = tok;                                  //set new last variable for next iteration
    }
    tokens.erase("");
    map<string, word>::iterator iter = tokens.begin();
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[i].size(); j++) {
            cout << M[i][j].token << ": " << M[i][j].prob << "/" << iter->second.occ;
            M[i][j].prob = M[i][j].prob / iter->second.occ;
            cout << M[i][j].token << ": " << M[i][j].prob << " ";
        }
        cout << endl;
        iter++;
    }
}

string chooseNext(vector<cell> sub) { //sub being a sub-vector of M
    //srand (time(0));
    int choice = rand() % 100;
    //cout << "choice = " << choice << endl;
    int probSum = 0;
    for (int i = 0; i < (int)sub.size(); i++) {
        probSum += (sub[i].prob * 100);
        //cout << "i: " << i << " sum: " << probSum << endl;
        if (choice < probSum) {
            //cout << "chose: " << sub[i].token << endl;
            return sub[i].token;
        }
    }
    return "";
}

void genText(vector<vector<cell>> M, map<string, word> tokens, int length) {
    srand(time(0));
    int first = rand() % (int)M.size();

    map<string, word>::iterator iter = tokens.begin();
    advance(iter, first);
    string curWord = iter->first;

    for (int i = 0; i < length; i++) {
        cout << curWord << " ";
        curWord = chooseNext(M[tokens[curWord].index]);
    }
    cout << endl;
}

int main() {
    vector<vector<cell>> M; //holds struct for vertices
    map<string, word> tokens; //holds a struct for faster string access
    genMatrix(M, tokens, "testIn.txt");
    genText(M, tokens, 10);
}
