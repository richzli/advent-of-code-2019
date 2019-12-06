#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

map<string, vector<string>> orbits;
map<string, string> parents;

int dfs(string node, int level) {
    int total = level;
    if (orbits.count(node) == 1) {
        for (auto next : orbits.at(node)) {
            total += dfs(next, level + 1);
        }
    }
    return total;
}

int main() {
    orbits.clear();
    
    while (true) {
        string AAA, BBB, input;
        getline(cin, input);

        // cout << input << endl;

        if (input == "-------") {
            break;
        }

        AAA = input.substr(0, 3);
        BBB = input.substr(4, 7);


        if (orbits.count(AAA) == 1) {
            orbits.at(AAA).push_back(BBB);
        } else {
            orbits.insert(pair<string, vector<string>>(AAA, vector<string>{BBB}));
        }

        parents.insert(pair<string, string>(BBB, AAA));
    }

    string root = orbits.begin()->first;
    while (parents.count(root) == 1) {
        root = parents.at(root);
    }

    printf("%d", dfs(root, 0));

    return 0;
}