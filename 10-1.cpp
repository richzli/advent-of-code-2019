#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

vector<vector<bool>> asteroids;
vector<double> angles;
map<double, pair<int, int>> directions;

double get_angle(pair<int, int> direction) {
    int x = -direction.first;
    int y = direction.second;
    if (atan2(y, x) < 0) {
        return atan2(y, x) + 2*3.14159265358979323846;
    }
    return atan2(y, x);
}

pair<int, int> zap(pair<int, int> coords, pair<int, int> direction) {
    int i = 1;
    while (0 <= coords.first + direction.first*i &&
    coords.first + direction.first*i < asteroids.at(i).size() &&
    0 <= coords.second + direction.second*i &&
    coords.second + direction.second*i < asteroids.size()) {
        if (asteroids.at(coords.first + direction.first*i).at(coords.second + direction.second*i)) {
            return pair<int, int>(coords.first + direction.first*i, coords.second + direction.second*i);
        }
        ++i;
    }
    return pair<int, int>(-1, -1);
}

pair<int, int> reduce(pair<int, int> diff) {
    int d;
    if (diff.first == 0) {
        d = abs(diff.second);
    } else if (diff.second == 0) {
        d = abs(diff.first);
    } else {
        d = __gcd(abs(diff.first), abs(diff.second));
    }

    return pair<int, int>(diff.first/d, diff.second/d);
}

bool is_blocked(pair<int, int> coords, vector<pair<int, int>> blockers) {
    for (pair<int, int> b : blockers) {
        if (asteroids.at(coords.first+b.first).at(coords.second+b.second)) {
            return true;
        }
    }
    return false;
}

vector<pair<int, int>> get_blocker_coords(pair<int, int> diff) {
    int d;
    if (diff.first == 0) {
        d = abs(diff.second);
    } else if (diff.second == 0) {
        d = abs(diff.first);
    } else {
        d = __gcd(abs(diff.first), abs(diff.second));
    }
    vector<pair<int, int>> blockers;

    for (int i = 1; i < d; ++i) {
        blockers.push_back(pair<int, int>(diff.first/d*i, diff.second/d*i));
    }

    return blockers;
}

int main() {
    while (true) {
        string line;
        getline(cin, line);
        
        if (line == "-") {
            break;
        }

        vector<bool> row;
        for (char c : line) {
            if (c == '#') {
                row.push_back(true);
            } else {
                row.push_back(false);
            }
        }
        asteroids.push_back(row);
    }

    pair<int, int> seen(0, 0);
    int numseen = 0;

    for (size_t i = 0; i < asteroids.size(); ++i) {
        for (size_t j = 0; j < asteroids.at(0).size(); ++j) {
            if (!asteroids.at(i).at(j)) {
                continue;
            }
            int s = 0;

            for (size_t k = 0; k < asteroids.size(); ++k) {
                for (size_t l = 0; l < asteroids.at(0).size(); ++l) {
                    if ((i == k && j == l) || !asteroids.at(k).at(l)) {
                        continue;
                    }
                    
                    if (!is_blocked(pair<int, int>(i, j), get_blocker_coords(pair<int, int>(k-i, l-j)))) {
                        //cout << i << "," << j << " to " << k << "," << l << " || ";
                        //cout << k-i << "," << l-j << endl;
                        ++s;
                    }
                }
            }

            if (s > numseen) {
                numseen = s;
                seen = pair<int, int>(i, j);
            }
        }
    }

    cout << seen.second << "," << seen.first << " " << numseen << endl << endl;

    for (size_t i = 0; i < asteroids.size(); ++i) {
        for (size_t j = 0; j < asteroids.at(0).size(); ++j) {
            if (i == seen.first && j == seen.second) {
                continue;
            }

            if (asteroids.at(i).at(j)) {
                pair<int, int> d = reduce(pair<int, int>(i-seen.first, j-seen.second));
                float angle = get_angle(d);
                angles.push_back(angle);
                if (directions.find(angle) == directions.end()) {
                    directions.insert(pair<float, pair<int, int>>(angle, d));
                }
            }
        }
    }

    std::sort(angles.begin(), angles.end());
    angles.erase(unique(angles.begin(), angles.end()), angles.end());

    int count = 0;
    while (count < 200) {
        for (float angle : angles) {
            pair<int, int> next = zap(seen, directions.find(angle)->second);
            if (next.first != -1) {
                asteroids.at(next.first).at(next.second) = false;
                ++count;
                //cout << count << " " << angle << " " << next.second << "," << next.first << endl;
            }

            if (count == 200) {
                cout << next.second << "," << next.first;
                break;
            }
        }
    }

    return 0;
}