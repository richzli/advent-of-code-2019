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

bool map[51][45];

#define pii pair<int, int>

pii rotate(pii dir) {
    if (dir == pii(0, -1)) {
        return pii(1, 0);
    } else if (dir == pii(1, 0)) {
        return pii(0, 1);
    } else if (dir == pii(0, 1)) {
        return pii(-1, 0);
    } else if (dir == pii(-1, 0)) {
        return pii(0, -1);
    }
    return pii(0, 0);
}

char direction_arrow(pii dir) {
    if (dir == pii(0, -1)) {
        return '<';
    } else if (dir == pii(1, 0)) {
        return 'v';
    } else if (dir == pii(0, 1)) {
        return '>';
    } else if (dir == pii(-1, 0)) {
        return '^';
    }
    return 'o';
}

char comp(pii dir1, pii dir2) {
    if (dir1 == dir2) {
        return 'F';
    } else if (dir1 == rotate(rotate(dir2))) {
        return 'B';
    } else if (rotate(dir1) == dir2) {
        return 'L';
    } else if (dir1 == rotate(dir2)) {
        return 'R';
    }
}

int main() {
    instances.push_back(tviii(read(), 0, 0));
    instances.push_back(instances.at(0));
    get<0>(instances.at(1)).at(0) = 2;

    int lines = 0;
    int chars = 0;

    while (true) {
        
        pair<int, long long> output = run(instances.at(0));

        if (output.first == -1) {
            break;
        }

        if (output.second == 10) {
            // cout << " " << lines;
            ++lines;
            chars = 0;
        } else {
            if (output.second == 46) {
                map[lines][chars] = false;
            } else {
                map[lines][chars] = true;
            }
            ++chars;
        }

        // cout << char(output.second);
    }

    vector<char> actions;

    pii currpos(8, 0), currdir(0, 1);
    pii d = currdir;

    /*
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 45; ++j) {
            cout << (map[i][j] ? "#" : " ");
        }
        cout << endl;
    }
    */

    actions.push_back('R');

    int turns = 0;
    int moves = 0;
    while (turns < 4) {
        int newr = currpos.first + currdir.first;
        int newc = currpos.second + currdir.second;
        // cout << currpos.first << " " << currpos.second << ", " << direction_arrow(currdir) << ", " << turns << ", " << newr << " " << newc << ", " << ((0 <= newr && 0 <= newc && 45 > newr && 50 > newc) ? map[newr][newc] : 2) << " / ";
        if (0 <= newr && 0 <= newc && 51 > newr && 45 > newc && map[newr][newc] && currdir != rotate(rotate(d))) {
            if (turns > 0) {
                actions.push_back(moves);
                moves = 0;
                actions.push_back(comp(d, currdir));
                turns = 0;
            }
            ++moves;
            currpos = pii(newr, newc);
            d = currdir;
        } else {
            currdir = rotate(currdir);
            ++turns;
        }
    }

    actions.push_back(moves);

    cout << endl;

    bool c = true;
    for (size_t i = 0; i < actions.size(); ++i) {
        if (c) {
            cout << actions.at(i) << " ";
        } else {
            cout << int(actions.at(i)) << " ";
        }
        c = !c;
    }

    cout << endl << endl;

    inputs = list<long long>{'A',',','B',',','A',',','B',',','C',',','C',',','B',',','C',',','B',',','A',10,
    'R',',','1','2',',','L',',','8',',','R',',','1','2',10,
    'R',',','8',',','R',',','6',',','R',',','6',',','R',',','8',10,
    'R',',','8',',','L',',','8',',','R',',','8',',','R',',','4',',','R',',','4',10,
    'n',10};
    
    while (true) {
        
        pair<int, long long> output = run(instances.at(1));

        if (output.first == -1) {
            break;
        }

        if (output.second > 1000) {
            cout << output.second << endl;
        }
    }
}