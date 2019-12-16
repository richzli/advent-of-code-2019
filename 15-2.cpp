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

#include <map>
#define pii pair<int, int>

pii curr(0, 0);
list<pii> bfs;
map<pii, pii> parents;
map<pii, int> statuses;
map<pii, int> distances;

list<int> path_to_origin(pii point, bool backwards) {
    if (point == pii(0, 0)) {
        return list<int>();
    }

    pii parent = parents.find(point)->second;
    list<int> path = path_to_origin(parent, backwards);
    if (!backwards) {
        if (point.first < parent.first) {
            // the point is to the left of the parent, so move right
            path.push_front(4);
        } else if (point.first > parent.first) {
            // the point is to the right of the parent, so move left
            path.push_front(3);
        } else if (point.second < parent.second) {
            // the point is below the parent, so move up
            path.push_front(1);
        } else if (point.second > parent.second) {
            // the point is above the parent, so move down
            path.push_front(2);
        }
    } else {
        // now we want to move from parent to point
        if (point.first < parent.first) {
            path.push_back(3);
        } else if (point.first > parent.first) {
            path.push_back(4);
        } else if (point.second < parent.second) {
            path.push_back(2);
        } else if (point.second > parent.second) {
            path.push_back(1);
        }
    }
    
    return path;
}

vector<pii> neighbors(pii point) {
    return vector<pii>{pii(point.first, point.second+1), pii(point.first, point.second-1), pii(point.first-1, point.second), pii(point.first+1, point.second)};
}

list<int> dfss;
map<pii, bool> visited;
pii p;
int maxdist = 0;

int opposite(int direction) {
    if (direction == 1) {
        return 2;
    } else if (direction == 2) {
        return 1;
    } else if (direction == 3) {
        return 4;
    } else if (direction == 4) {
        return 3;
    }
}

pii move(pii point, int direction) {
    if (direction == 1) {
        return pii(point.first, point.second+1);
    } else if (direction == 2) {
        return pii(point.first, point.second-1);
    } else if (direction == 3) {
        return pii(point.first-1, point.second);
    } else if (direction == 4) {
        return pii(point.first+1, point.second);
    }
}

void dfs(pii point, int depth) {
    if (maxdist < depth) {
        maxdist = depth;
    }
    for (int i = 1; i < 5; ++i) {
        if (visited.find(move(point, i)) == visited.end()) {
            visited.insert(pair<pii, bool>(move(point, i), true));
            inputs.push_back(i);
            long long status = run(instances.at(1)).second;
            if (status != 0) {
                dfs(move(point, i), depth+1);
                inputs.push_back(opposite(i));
                run(instances.at(1));
            }
        }
    }
}

int main() {
    vi instructions = read();
    vi copy = instructions;
    instances.push_back(tviii(instructions, 0, 0));
    instances.push_back(tviii(copy, 0, 0));

    bfs.push_back(pii(0, 0));

    int dist = 0;

    while (true) {
        pii next = bfs.front();
        // cout << "NEXT IS " << next.first << ", " << next.second << endl;
        bfs.pop_front();

        if (statuses.find(next) != statuses.end()) {
            // already been visited
            continue;
        }

        list<int> pto = path_to_origin(curr, false);
        for (auto it = pto.begin(); it != pto.end(); ++it) {
            inputs.push_back(*it);
            run(instances.at(0));
        }

        list<int> otp = path_to_origin(next, true);
        int status_code = 1;
        for (auto it = otp.begin(); it != otp.end(); ++it) {
            inputs.push_back(*it);
            status_code = run(instances.at(0)).second;
        }

        // cout << "VISITED " << curr.first << ", " << curr.second << " WITH STATUS " << status_code << endl;

        curr = next;
        int currdist = distances.find(curr)->second;
        statuses.insert(pair<pii, int>(curr, status_code));

        if (status_code == 2) {
            dist = currdist;
            break;
        } else if (status_code == 1) {
            for (pii p : neighbors(curr)) {
                if (statuses.find(p) == statuses.end()) {
                    bfs.push_back(p);
                    // cout << "PUSHED BACK " << p.first << ", " << p.second << endl;
                    parents.insert(pair<pii, pii>(p, curr));
                    distances.insert(pair<pii, int>(p, currdist+1));
                }
            }
        } else if (status_code == 0) {
            curr = parents.find(curr)->second;
        }
        
        
    }

    inputs.clear();

    list<int> p = path_to_origin(curr, true);

    for (auto it = p.begin(); it != p.end(); ++it) {
        inputs.push_back(*it);
        run(instances.at(1));
    }

    dfs(pii(0, 0), 0);
    cout << maxdist;
}