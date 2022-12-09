#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const string pairs="2-4,6-8\n"
                   "2-3,4-5\n"
                   "5-7,7-9\n"
                   "2-8,3-7\n"
                   "6-6,4-6\n"
                   "2-6,4-8\n"
                   ;

vector<pair<pair<int, int>, pair<int, int>>> buildVector(stringstream &ss);

int main(){

    stringstream ss;
    ss << pairs;

    auto cleanUpDetails= buildVector(ss);


    return EXIT_SUCCESS;
}

vector<pair<pair<int, int>, pair<int, int>>> buildVector(stringstream &ss){

    vector<pair<pair<int, int>, pair<int, int>>> pairVector;
    string line;

    while(getline(ss, line)){

        auto comma = static_cast<int>(line.find(','));

        string substr1 = line.substr(0, comma);
        string substr2 = line.substr(comma + 1, line.size());

        auto pair1delim = static_cast<int>(substr1.find('-'));
        auto pair2delim = static_cast<int>(substr2.find('-'));

        pair<int, int> pair1;
        pair<int, int> pair2;
        pair1 = make_pair(stoi(substr1.substr(0, pair1delim)),
                          stoi(substr1.substr(pair1delim + 1, substr1.size())));
        pair2 = make_pair(stoi(substr2.substr(0, pair2delim)),
                          stoi(substr2.substr(pair2delim + 1, substr2.size())));

        auto pairElement = make_pair(pair1, pair2);
        pairVector.push_back(pairElement);

    }

    return pairVector;
}