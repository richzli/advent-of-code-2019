#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <set>
#include <map>
#include <string>
using namespace std;

#define vi vector<long long>
#define pii pair<int, int>
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

#define ppiiii pair<pii, int>

vector<pii> directions{pii(0, 1), pii(1, 0), pii(0, -1), pii(-1, 0)};
map<pii, int> direc_indices{ppiiii(pii(0, 1), 0), ppiiii(pii(1, 0), 1), ppiiii(pii(0, -1), 2), ppiiii(pii(-1, 0), 3)};

int modd(int n, int m) {
    n %= m;
    if (n < 0) {
        n += m;
    }
    return n;
}

pii turn(pii direction, int t) {
    if (t == 0) {
        t = -1;
    }
    return directions.at(modd(direc_indices.find(direction)->second+t, 4));
}

int main() {
    instances.push_back(tviii(read(), 0, 0));

    pii curr(0, 0);
    pii direction(0, 1);
    set<pii> traveled;
    set<pii> white;

    inputs.push_back(0);

    while (true) {
        // cout << inputs.front() << " | " << curr.first << " " << curr.second << " | ";

        pair<int, long long> first = run(instances.at(0));

        // cout << first.second << " ";

        if (first.first == -1) {
            break;
        }

        pair<int, long long> second = run(instances.at(0));

        // cout << second.second << endl;

        if (second.first == -1) {
            break;
        }

        traveled.insert(curr);

        if (first.second == 0) {
            if (white.find(curr) != white.end()) {
                white.erase(curr);
            }
        } else {
            white.insert(curr);
        }

        direction = turn(direction, second.second);
        curr = pii(curr.first + direction.first, curr.second + direction.second);

        if (white.find(curr) == white.end()) {
            inputs.push_back(0);
        } else {
            inputs.push_back(1);
        }
    }

    cout << traveled.size();
}