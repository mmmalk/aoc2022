#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#define DEBUG true

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

vector<pair<char, char>> giveGuide(const string &inputFile);

int main() {

    int totalScore = 0;
    hand yourHand;
    hand opponentHand;
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
                break;
            case 'Y':
                yourHand = hand::paper;
                break;
            case 'Z':
                yourHand = hand::scissors;
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

        if (DEBUG) {
            cout << pair.first << " : " << pair.second << endl;
            cout << opponentHand << " : " << yourHand << endl;
            cout << "from result: " << (resolve(opponentHand, yourHand)) << " from your hand: " << yourHand << endl;
            cout << "total so far: " << totalScore << endl;
        }

    }
    cout << "score total: " << totalScore << endl;

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

/* Notation:
 * opponent         you
 * A = rock        X = rock
 * B = paper       Y = paper
 * C = scissors    Z = scissors
 */
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
                {'B', 'Z'}

        };
    }
    return guide;
};