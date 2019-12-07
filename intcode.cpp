#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

#define vi vector<int>
#define pii pair<int, int>

//                     1  2  3  4  5  6  7  8
const int lens[] = {0, 3, 3, 1, 1, 2, 2, 3, 3};

vector<pair<vi, int>> instances;
list<int> inputs;

#define oa(i) ops.at(i)

vi read() {
    vi ops;

    string input;
    getline(cin, input);

    size_t i = 0;
    while ((i = input.find(",")) != string::npos) {
        ops.push_back(stoi(input.substr(0, i)));
        input.erase(0, i+1);
    }
    ops.push_back(stoi(input));

    return ops;
}

int get(vi ops, int mode, int i) {
    if (mode == 0) {
        return oa(i);
    } else if (mode == 1) {
        return i;
    } 
    return -1;
}

int run(pair<vi, int> instance) {
    vi ops = instance.first;
    int index = instance.second;

    while (ops.at(index) % 100 != 99) {
        int instruction = ops.at(index);
        int op = instruction % 100;
        int len = lens[op];

        int modes[len];
        for (int i = 0; i < len; ++i) {
            modes[i] = (instruction / ((int) pow(10, i+2))) % 10;
        }
        
        int params[len];
        for (int i = 0; i < len; ++i) {
            params[i] = get(ops, modes[i], index+i+1);
        }
        
        index += 1 + len;
        if (op == 1) {
            oa(params[2]) = oa(params[0]) + oa(params[1]);
        } else if (op == 2) {
            oa(params[2]) = oa(params[0]) * oa(params[1]);
        } else if (op == 3) {
            int input = inputs.front();
            inputs.pop_front();
            oa(params[0]) = input;
        } else if (op == 4) {
            instance.first = ops;
            instance.second = index;
            return oa(params[0]);
        } else if (op == 5) {
            if (oa(params[0]) != 0) {
                index = oa(params[1]);
            }
        } else if (op == 6) {
            if (oa(params[0]) == 0) {
                index = oa(params[1]);
            }
        } else if (op == 7) {
            if (oa(params[0]) < oa(params[1])) {
                oa(params[2]) = 1;
            } else {
                oa(params[2]) = 0;
            }
        } else if (op == 8) {
            if (oa(params[0]) == oa(params[1])) {
                oa(params[2]) = 1;
            } else {
                oa(params[2]) = 0;
            }
        }
    }
    return -1;
}

int main() {
    instances.push_back(pair<vi, int>(read(), 0));

    inputs.push_back(7);

    int output = run(instances.at(0));

    printf("%d\n", output);
}