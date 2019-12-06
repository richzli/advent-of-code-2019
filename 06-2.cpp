#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

map<string, vector<string>> orbits;
map<string, int> levels;
map<string, string> parents;

map<string, vector<string>> up;

int dfs(string node, int level) {
    int total = level;
    if (orbits.count(node) == 1) {
        for (auto next : orbits.at(node)) {
            total += dfs(next, level + 1);
        }
    }
    levels.insert(pair<string, int>(node, level));
    return total;
}

void preprocess_lifter(string node) {
    int sz = orbits.size();
    sz = int (log2(sz));

    up.insert(pair<string, vector<string>>(node, vector<string>{parents.at(node)}));
    for (int i = 1; i <= sz; ++i) {
        up.at(node).push_back(up.at(up.at(node).at(i-1)).at(i-1));
    }

    if (orbits.count(node) == 1) {
        for (auto next : orbits.at(node)) {
            preprocess_lifter(next);
        }
    }
}

string lca(string first, string second) {
    int sz = orbits.size();
    sz = int (log2(sz));

    if (levels.at(first) > levels.at(second)) {
        string temp = second;
        second = first;
        first = temp;
    }

    while (levels.at(first) < levels.at(second)) {
        // cout << first << " " << second << endl;
        second = up.at(second).at(0);
    }
    
    if (second == first) {
        return second;
    }

    for (int i = sz; i >= 0; --i) {
        // cout << up.at(first).at(i) << " " << up.at(second).at(i) << endl;
        if (up.at(first).at(i) != up.at(second).at(i)) {
            first = up.at(first).at(i);
            second = up.at(second).at(i);
        }
    }

    return up.at(first).at(0);
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
    parents.insert(pair<string, string>(root, root));

    dfs(root, 0);

    preprocess_lifter(root);
    int l = levels.at(lca("YOU", "SAN"));

    printf("%d", (levels.at("YOU") + levels.at("SAN") - 2*l - 2));

    return 0;
}