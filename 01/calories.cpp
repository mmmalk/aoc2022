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

int main() {


    map<int, int> elvenCaloriesMap;
    string line;
    ifstream is("./calories.txt");
    stringstream ss;
    if (is) {
        ss << is.rdbuf();
        is.close();
    } else {
        cout << "file calories.txt not found in the same directory" << endl;
        cout << "falling back to example data from the problem definition" << endl;
        ss << elvenCaloriesList;
    }

    int elf = 0;
    int total = 0;

    while (getline(ss, line)) {
        if (line.empty()) {
            elvenCaloriesMap.insert(pair<int, int>(total, elf));
            elf++;
            total = 0;
            continue;
        } else if (!ss.good()) { // last line missed otherwise
            total += stoi(line);
            elvenCaloriesMap.insert(pair<int, int>(total, elf));
            break;
        }
        total += stoi(line);
    }

    int limit = 0;
    int totalCalories = 0;
    int maxCalories = 0;
    int maxCalorieElf = 0;

    for (auto i = elvenCaloriesMap.rbegin(); i != elvenCaloriesMap.rend(); ++i) {
        cout << i->second + 1 << ":" << i->first << endl;
        totalCalories += i->first;
        if (i->first > maxCalories) {
            maxCalories = i->first;
            maxCalorieElf = i->second + 1;
        }
        if (limit == 2) {
            break;
        }
        limit++;
    }

    cout << "max: elf number " << maxCalorieElf << " with " << maxCalories << " calories" << endl;
    cout << "total top-3 calories: " << totalCalories << endl;

    return 0;
}