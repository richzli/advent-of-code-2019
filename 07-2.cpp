#include <cstdio>
#include <iostream>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#define vi vector<int>
#define pii pair<int, int>

//                     1  2  3  4  5  6  7  8
const int lens[] = {0, 3, 3, 1, 1, 2, 2, 3, 3};

vi ops;
vi inputs;

#define oa(i) opps.at(i)

void read() {
    ops = vi();

    string input;
    getline(cin, input);

    size_t i = 0;
    while ((i = input.find(",")) != string::npos) {
        ops.push_back(stoi(input.substr(0, i)));
        input.erase(0, i+1);
    }
    ops.push_back(stoi(input));
}

int get(vi opps, int mode, int i) {
    if (mode == 0) {
        return oa(i);
    } else if (mode == 1) {
        return i;
    } 
    return -1;
}

pair<int, int> run(int index, vi opps) {
    while (opps.at(index) % 100 != 99) {
        int instruction = opps.at(index);
        int op = instruction % 100;
        int len = lens[op];

        int modes[len];
        for (int i = 0; i < len; ++i) {
            modes[i] = (instruction / ((int) pow(10, i+2))) % 10;  
        }
        
        int params[len];
        for (int i = 0; i < len; ++i) {
            params[i] = get(opps, modes[i], index+i+1);
        }

        index += 1 + len;
        if (op == 1) {
            oa(params[2]) = oa(params[0]) + oa(params[1]);
        } else if (op == 2) {
            oa(params[2]) = oa(params[0]) * oa(params[1]);
        } else if (op == 3) {
            int input;
            input = inputs.at(0);
            inputs.erase(inputs.begin());
            // printf("%d ", input);
            oa(params[0]) = input;
        } else if (op == 4) {
            return pii(oa(params[0]), index);
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
}

int main() {
    read();
    vector<pair<vi, int>> amps {pair<vi, int>(ops, 0), pair<vi, int>(ops, 0), pair<vi, int>(ops, 0), pair<vi, int>(ops, 0), pair<vi, int>(ops, 0)};

    int powers[] {5, 6, 7, 8, 9};

    int maxpower = 0;

    do {
        int power = 0;
        for (int i = 0; i < sizeof(powers)/sizeof(*powers); ++i) {
            inputs.push_back(powers[i]);
            inputs.push_back(power);

            pii outputs = run(0, amps.at(i).first);
            power = outputs.first;
            amps.at(i).second = outputs.second;
        }
        
        int ind = 0;
        while (amps.at(ind).first.at(amps.at(ind).second) != 99) {
            inputs.push_back(power);
            
            pii outputs = run(amps.at(ind).second, amps.at(ind).first);
            power = outputs.first;
            amps.at(ind).second = outputs.second;

            ++ind;
            ind %= 5;
        }

        if (maxpower < power) {
            maxpower = power;
        }

        
    } while (next_permutation(powers, powers + 5));
    printf("%d\n", maxpower);
}