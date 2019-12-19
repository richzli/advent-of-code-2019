#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <string>
using namespace std;

#define vi vector<long long>
#define tviii tuple<vi, long long, long long>

//                     1  2  3  4  5  6  7  8  9
const int lens[] = {0, 3, 3, 1, 1, 2, 2, 3, 3, 1};

vector<tviii> instances;
list<long long> inputs;

#define oa(i) ops.at(i)

vi read() {
    vi ops;

    string input;
    getline(cin, input);

    size_t i = 0;
    while ((i = input.find(",")) != string::npos) {
        ops.push_back(stoll(input.substr(0, i)));
        input.erase(0, i+1);
    }
    ops.push_back(stoi(input));

    return ops;
}

long long get_param(vi& ops, int mode, int i, int base) {
    if (mode == 0) {
        while (i >= int(ops.size())) {
            ops.push_back(0);
        }
        while (oa(i) >= int(ops.size())) {
            ops.push_back(0);
        }
        return oa(i);
    } else if (mode == 1) {
        while (i >= int(ops.size())) {
            ops.push_back(0);
        }
        return i;
    } else if (mode == 2) {
        while (base + i >= int(ops.size())) {
            ops.push_back(0);
        }
        while (base+oa(i) >= int(ops.size())) {
            ops.push_back(0);
        }
        return base+oa(i);
    }
    return -1;
}

pair<int, long long> run(tviii& instance) {
    vi& ops = get<0>(instance);
    long long& index = get<1>(instance);
    long long& base = get<2>(instance);

    while (oa(index) % 100 != 99) {
        long long instruction = ops.at(index);
        int op = int(instruction % 100);
        int len = lens[op];

        int modes[len];
        for (int i = 0; i < len; ++i) {
            modes[i] = (instruction / (int (pow(10, i+2)+0.5))) % 10;
        }
        
        long long params[len];
        for (int i = 0; i < len; ++i) {
            params[i] = get_param(ops, modes[i], index+i+1, base);
        }
        
        index += 1 + len;
        if (op == 1) {
            oa(params[2]) = oa(params[0]) + oa(params[1]);
        } else if (op == 2) {
            oa(params[2]) = oa(params[0]) * oa(params[1]);
        } else if (op == 3) {
            long long input = inputs.front();
            inputs.pop_front();
            oa(params[0]) = input;
        } else if (op == 4) {
            return pair<int, long long>(0, oa(params[0]));
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
        } else if (op == 9) {
            base += oa(params[0]);
        }
    }
    
    return pair<int, long long>(-1, -1);
}

bool check(int x, int y) {
    instances.push_back(instances.at(0));
    inputs.push_back(x);
    inputs.push_back(y);

    pair<int, long long> output = run(instances.at(1));

    instances.pop_back();

    if (output.second == 1) {
        return true;
    }
    return false;
}

bool checkbox(int x, int y) {
    return check(x, y) && check(x+99, y) && check(x, y+99) && check(x+99, y+99);
}

int main() {
    instances.push_back(tviii(read(), 0, 0));

    bool found = false;

    int x = 9;

    for (int i = 14; !found; ++i) {
        // cout << "tried y=" << i << "  ";
        for (int j = x; check(j, i); --j) {
            // cout << "(" << j << ", " << i << ") ";
            if (checkbox(j, i)) {
                cout << j << " " << i;
                found = true;
                break;
            }
        }
        for (++x; check(x, i); ++x) {
            // cout << "(" << x << ", " << i << ") ";
            if (checkbox(x, i)) {
                cout << x << " " << i;
                found = true;
                break;
            }
        }
        --x;
    }
}