#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <array>
#include <sstream>
#include <fstream>
#include <vector>

#define COMPARTMENT false

using namespace std;

const string rucksack = "vJrwpWtwJgWrhcsFMMfFFhFp\n"
                        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n"
                        "PmmdzqPrVvPwwTWBwg\n"
                        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n"
                        "ttgJtRGJQctTZtZT\n"
                        "CrZsJsPPZsGzwwsLwLmpwMDw\n";
const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


map<char, int> constructPriorityList();

vector<char> findCommon(const string &input1, const string &input2);

vector<char> findCommonFromThree(const string &rucksack1, const string &rucksack2, const string &rucksack3);

int main() {

    stringstream ss;
    string line;
    auto is = ifstream("./rucksack.txt");

    if (is) {
        ss << is.rdbuf();
        is.close();
    } else {
        cout << "file rucksack.txt not found in the same directory" << endl;
        cout << "falling back to example data from the problem definition" << endl;
        ss << rucksack;
    }
    map<char, int> priority = constructPriorityList();
    int prioSum = 0;

    if (COMPARTMENT) {
        vector<char> compartmentCommon;
        while (getline(ss, line)) {
            int half = static_cast<int>(line.size()) / 2;
            auto tmp = findCommon(line.substr(0, half), line.substr(half, line.size()));
            compartmentCommon.insert(compartmentCommon.end(), tmp.begin(), tmp.end());
        }


        for (const auto &c: compartmentCommon) {
            cout << "found: " << c << ", priority:" << priority[c] << endl;
            prioSum += priority[c];
        }
    } else {
        int linecount = 0;
        vector<char> rucksackCommon;
        array<string, 3> rucksacks{"", "", ""};
        while (getline(ss, line)) {
            rucksacks[(linecount % 3)] = line;
            linecount++;
            if (linecount % 3 == 0) {
                auto tmp = findCommonFromThree(rucksacks[0], rucksacks[1], rucksacks[2]);
                rucksackCommon.insert(rucksackCommon.end(), tmp.begin(), tmp.end());
            }

        }
        cout << linecount << " lines read" << endl;
        for (const auto &item: rucksackCommon) {
            cout << item << endl;
            prioSum += priority[item];
        }
    }
    cout << "sum of all priorities: " << prioSum << endl;
    return EXIT_SUCCESS;
}

//associates every character from a-Z with value from 1 to 52
map<char, int> constructPriorityList() {
    map<char, int> resultMap;
    int val = 1;
    for (char c: alphabet) {
        resultMap.insert({c, val});
        val++;
    }
    return resultMap;
}

//takes one line/'rucksack' at the time
vector<char> findCommon(const string &input1, const string &input2) {
    vector<char> result;

    for (char c1: input1) {
        for (char c2: input2) {
            if (c1 == c2 && find(result.begin(), result.end(), c1) == result.end()) {
                    result.push_back(c1);
            }
        }
    }

    return result;
}

// jesus this is not optimal, this is truly not optimal.
vector<char> findCommonFromThree(const string &rucksack1, const string &rucksack2, const string &rucksack3) {
    vector<char> result;
    auto tmp1 = findCommon(rucksack1, rucksack2);
    auto tmp2 = findCommon(rucksack2, rucksack3);
    result = findCommon(string(tmp1.begin(), tmp1.end()), string(tmp2.begin(), tmp2.end()));

    return result;
}