#include <iostream>
#include <string>
#include <map>
#include <algorithm>


using namespace std;


const string rucksack1 = "vJrwpWtwJgWrhcsFMMfFFhFp";
const string rucksack2 = "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL";
const string rucksack3 = "PmmdzqPrVvPwwTWBwg";
const string rucksack4 = "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn";
const string rucksack5 = "ttgJtRGJQctTZtZT";
const string rucksack6 = "CrZsJsPPZsGzwwsLwLmpwMDw";
const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


map<char, int> constructPriorityList();
map<char, int> findCommon(const string& input);

int main(){

    map<char, int> priority = constructPriorityList();

    cout << rucksack1.substr(0, rucksack1.size()/2) << endl;
    cout << rucksack1.substr(rucksack1.size()/2, rucksack1.size()) << endl;
    cout << rucksack1.find('v') << endl;

    auto commonsMap = findCommon(rucksack1);
    auto tmpMap = findCommon(rucksack2);
    commonsMap.insert(tmpMap.begin(), tmpMap.end());
    for(const auto &p : commonsMap){
        cout << priority[p.first] << endl;
        cout << p.first << " : " << p.second << " - " << priority[p.first] << endl;
    }
    return EXIT_SUCCESS;
}

//associates every character from a-Z with value from 1 to 52
map<char, int> constructPriorityList(){
    map<char, int> resultMap;
    int val = 1;
    for(char c: alphabet){
        resultMap.insert({c, val});
        val++;
    }
    return resultMap;
}

//takes one line/'rucksack' at the time
map<char, int> findCommon(const string& input){
    map<char, int> resultMap;
    int half = static_cast<int>(input.size()) / 2;
    string compartment1 = input.substr(0, half);
    string compartment2 = input.substr(half, input.size());

    cout << compartment1 << " + " << compartment2 << endl;
    auto f= compartment1.find('e');
    cout << (f != std::string::npos) << endl; //if not found
    for(char c1: compartment1){
        int count = 0;
        for(char c2: compartment2){

            if(c1 == c2){
                count++;
            }
        }
        if(count != 0){
            resultMap.insert({c1, count});
        }
    }

    return resultMap;
}