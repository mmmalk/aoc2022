#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#define DEBUG1 false
#define DEBUG2 false

using namespace std;

// states of the game's result
enum result {
    win = 6,
    draw = 3,
    loss = 0
};
// what 'hand' you picked
enum hand {
    rock = 1,
    paper = 2,
    scissors = 3,
    nil = -1
};


// implements the winner on 2-dimensional array
result resolve(int opponent, int you);
hand getYourHand(int opponent, int result);

vector<pair<char, char>> giveGuide(const string &inputFile);

int main() {

    int totalScore = 0;
    int otherScore = 0;
    hand yourHand;
    hand opponentHand;
    result supposedResult;
    const string fileName = "./rps.txt";
    auto guide = giveGuide(fileName);

    for (auto pair: guide) {
        switch (pair.first) {
            case 'A':
                opponentHand = hand::rock;
                break;
            case 'B':
                opponentHand = hand::paper;
                break;
            case 'C':
                opponentHand = hand::scissors;
                break;
            default:
                opponentHand = hand::nil;
        }
        switch (pair.second) {
            case 'X':
                yourHand = hand::rock;
                supposedResult = result::loss;
                break;
            case 'Y':
                yourHand = hand::paper;
                supposedResult = result::draw;
                break;
            case 'Z':
                yourHand = hand::scissors;
                supposedResult = result::win;
                break;
            default:
                yourHand = hand::nil;
        }

        if (opponentHand == -1 || yourHand == -1) {
            cout << "Faulty data" << endl;
            cout << "opponent's character: " << pair.first << endl;
            cout << "your character: " << pair.second << endl;
            return EXIT_FAILURE;
        }
        totalScore += yourHand;
        totalScore += resolve(opponentHand, yourHand);

        otherScore += supposedResult;
        otherScore += getYourHand(opponentHand, supposedResult);

        if (DEBUG1) {
            cout << pair.first << " : " << pair.second << endl;
            cout << opponentHand << " : " << yourHand << endl;
            cout << "from result: " << (resolve(opponentHand, yourHand)) << " from your hand: " << yourHand << endl;
            cout << "total so far: " << totalScore << endl;
        }
        if(DEBUG2){
            cout << pair.first << " : " << pair.second << endl;
            cout << opponentHand << " : " << supposedResult << endl;
            cout << "so your hand should be: " << (getYourHand(opponentHand, supposedResult)) << endl;
        }

    }
    cout << "score total based on hand: " << totalScore << endl;
    cout << "score total based on result: " << otherScore << endl;

    return EXIT_SUCCESS;
}

result resolve(int opponent, int you) {
    if ((you % 3) == (opponent - 1)) {
        return result::loss;
    } else if (opponent == you) {
        return result::draw;
    } else {
        return result::win;
    }
}

hand getYourHand(int opponent, int result) {
    if(result == result::draw){
        return hand(opponent);
    } else if(opponent == hand::scissors){
        if(result == result::win){
            return hand::rock;
        } else{
            return hand::paper;
        }
    } else if(opponent == hand::rock){
        if (result == result::win){
            return hand::paper;
        } else {
            return hand::scissors;
        }
    } else if (opponent == hand::paper){
        if (result == result::win){
            return hand::scissors;
        } else {
            return hand::rock;
        }
    }

    return hand::nil;
}

vector<pair<char, char>> giveGuide(const string &inputFile) {
    ifstream is(inputFile);
    stringstream ss;
    string line;
    const char *lineChars;
    vector<pair<char, char>> guide;
    if (is) {
        ss << is.rdbuf();
        is.close();
        while (getline(ss, line)) {
            lineChars = line.c_str();
            // since data is always C Z
            guide.push_back({lineChars[0], lineChars[2]});
        }
    } else {
        cout << "file " << inputFile << " not found in the same directory" << endl;
        cout << "falling back to example data from the problem definition" << endl;

        guide = {
                {'A', 'Y'},
                {'B', 'X'},
                {'C', 'Z'},
        };
    }
    return guide;
};