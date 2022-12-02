#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

const string elvenCaloriesList =
        "1000\n"
        "2000\n"
        "3000\n"
        "\n"
        "4000\n"
        "\n"
        "5000\n"
        "6000\n"
        "\n"
        "7000\n"
        "8000\n"
        "9000\n"
        "\n"
        "10000";

int main (){


    map<int, int> elvenCaloriesMap;
    string line;
    ifstream is("./caories.txt");
    stringstream ss;
    if(is){
        ss << is.rdbuf();
        is.close();
    } else {
        cout << "file calories.txt not found in the same directory" << endl;
        cout << "falling back to example data from the problem definition" << endl;
        ss << elvenCaloriesList;
    }

    int elf = 0;
    int total = 0;

    while (getline(ss, line)){
        if (line.empty()) {
            elvenCaloriesMap.insert(pair<int, int>(elf, total));
            elf++;
            total = 0;
            continue;
        } else if(!ss.good()){
            total += stoi(line);
            elvenCaloriesMap.insert(pair<int, int>(elf, total));
            break;
        }
        total += stoi(line);
    }

    int mostCaloriesElf = 0;
    int mostCalories = 0;

    int totalCaloriesSum = 0;
    vector<pair<int, int>> topThreeCalories;

    for (const auto &pair: elvenCaloriesMap){
        cout << pair.first + 1 << ":" << pair.second << endl;
        if(pair.second > mostCalories){
            if(topThreeCalories.size() == 3){
                topThreeCalories.pop_back();
            }
            mostCalories = pair.second;
            mostCaloriesElf = pair.first + 1;

            topThreeCalories.insert(topThreeCalories.begin(), pair);
        }

    }

    cout << "Most calories: " << mostCalories << endl;
    cout << "On elf number: " << mostCaloriesElf << endl;

    cout << "top three:" << endl;
    for(const auto &pair: topThreeCalories){
        cout << pair.first + 1 << " : " << pair.second << endl;
        totalCaloriesSum += pair.second;
    }

    cout << "Total of the top-3 sums is: " << totalCaloriesSum << endl;

	return 0;
}