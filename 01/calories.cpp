#include <iostream>
#include <string>
#include <map>
#include <sstream>

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

int main (int argc, char *argv[]){


    map<int, int> elvenCaloriesMap;
    string line;
    stringstream ss(elvenCaloriesList);

    int elf = 0;
    int total = 0;

    while (getline(ss, line)){
        if (line == "") {
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

    for (const auto &pair: elvenCaloriesMap){
        cout << pair.first + 1 << ":" << pair.second << endl;
        if(pair.second > mostCalories){
            mostCalories = pair.second;
            mostCaloriesElf = pair.first + 1;
        }

    }

    cout << "Most calories: " << mostCalories << endl;
    cout << "On elf number: " << mostCaloriesElf << endl;

	return 0;
}