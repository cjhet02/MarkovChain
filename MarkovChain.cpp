#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
using namespace std;

struct cell {
    float prob; //the index at which the string is held in M
    string token; //the string represented by the cell
};

struct word {
    int index;  //the index the word is held at in M
    float occ;    //tracks the word's number of unique children
    string token;
};

int inVec(vector<cell> sub, string tok) { //returns index of a token in a specified subvector of M
    for (int i = 0; i < sub.size(); i++) {
        if (sub[i].token == tok)
            return i;
    }
    return -1; //return -1 if the token is not in the vector
}

int findTok(vector<word> sub, string tok) { //does the same thing as inVec
    for (int i = 0; i < sub.size(); i++) {   //different function because different vector type
        if (sub[i].token == tok)            //could've been hardcoded, but this is more readable
            return i;
    }
    return -1;
}

void genMatrix(vector<vector<cell>>& M, vector<word>& tokens, string filename) {
    string last = "";
    ifstream infile(filename);

    while (!infile.eof()) {
        string tok;

        do {
            infile >> tok;
        } while (tok == "" && !infile.eof());

        if (tok == "") //trailing whitespaces will slip through this while loop, so catch it here
            break;

        int tokInd = findTok(tokens, tok); //check if tokInd has been stored before

        if (tokInd == -1) { //if the string has not been seen yet
            tokens.push_back(word{ (int)M.size(), 0, tok }); //insert string into graph
            tokInd = (int)M.size();
            vector<cell> tempArr;
            M.push_back(tempArr);
        }

        int pVec = findTok(tokens, last); //get M index for parent's vector
        if (pVec != -1) { //accounts for the first token not having a parent
            int ind = inVec(M[pVec], tok);

            if (ind != -1)                          //if token is already in parent's vector
                M[pVec][ind].prob += 1;
            else
                M[pVec].push_back(cell{ 1.0, tok });

            tokens[pVec].occ += 1; //increment unique child count
        }
        last = tok;                                  //set new last variable for next iteration
    }

    for (int i = 0; i < M.size(); i++) {
        cout << tokens[i].token << " - " << tokens[i].occ << ": ";
        for (int j = 0; j < M[i].size(); j++) {
            M[i][j].prob = M[i][j].prob / tokens[i].occ;
            cout << M[i][j].token << " - " << M[i][j].prob * 100 << "% ";
        }

        cout << endl;
    }

    infile.close();
}

void genText(vector<vector<cell>> M, vector<word> tokens, int length) {
    int first = rand() % (int)M.size();
    int choice;
    string curWord = tokens[first].token;


    for (int i = 0; i < length; i++) {
        cout << curWord << " ";
        int curInd = findTok(tokens, curWord);
        int probSum = 0;
        int choice = rand() % 106;  // Over 100 to give a chance that the chain picks a random word

        if (M[curInd].size() == 0 || choice > 100) { // if no transitions available or creativity is chosen
            choice = rand() % 100;
            curWord = tokens[choice].token;

            for (int j = 0; j < (int)tokens.size(); j++) { //pick a token from the list, weighted by occurrences
                int tokProb = tokens[j].occ / tokens.size();
                probSum += (tokProb * 100);

                if (choice < probSum) {
                    curWord = tokens[j].token;
                }
            }
        }
        else {
            for (int j = 0; j < (int)M[curInd].size(); j++) {
                probSum += (M[curInd][j].prob * 100);

                if (choice < probSum) {
                    curWord = M[curInd][j].token;
                }
            }
        }
    }
    cout << curWord << endl;
}

int main() {
    srand(time(NULL));
    vector<vector<cell>> M; //holds struct for vertices
    vector<word> tokens; //holds a struct for faster string access
    string filename;
    int length;
    cout << "Enter cleaned data file name: ";
    cin >> filename;
    genMatrix(M, tokens, filename);
    cout << "\nEnter desired sentence length: ";
    cin >> length;
    cout << "\nEnter desired number of sentences: ";
    int num;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << endl;
        genText(M, tokens, length);
        cout << endl;
    }
}