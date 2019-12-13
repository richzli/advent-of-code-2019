#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int change(int base, int movd) {
    if (base == movd) {
        return 0;
    } else {
        return (base-movd)/abs(base-movd);
    }
}

int main() {
    int moons[2][4][3];

    for (int i = 0; i < 4; ++i) {
        int x, y, z;
        scanf("<x=%d, y=%d, z=%d>\n", &x, &y, &z);
        
        moons[0][i][0] = x;
        moons[0][i][1] = y;
        moons[0][i][2] = z;

        for (int j = 0; j < 3; ++j) {
            moons[1][i][j] = 0;
        }
    }

    int initial_state[4][3];

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            initial_state[i][j] = moons[0][i][j];
        }
    }

    // important thing to notice is that the three axes are independent of each other

    long long x_repeat = -1, y_repeat = -1, z_repeat = -1;

    int counter = 0;
    while (x_repeat == -1 || y_repeat == -1 || z_repeat == -1) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 3; ++k) {
                    moons[1][j][k] += change(moons[0][i][k], moons[0][j][k]);
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                moons[0][i][j] += moons[1][i][j];
            }
        }

        ++counter;

        if (x_repeat == -1) {
            bool f = true;
            for (int i = 0; i < 4 && f; ++i) {
                if (moons[0][i][0] != initial_state[i][0] || moons[1][i][0] != 0) {
                    f = false;
                }
            }
            if (f) {
                x_repeat = counter;
            }
        }

        if (y_repeat == -1) {
            bool f = true;
            for (int i = 0; i < 4 && f; ++i) {
                if (moons[0][i][1] != initial_state[i][1] || moons[1][i][1] != 0) {
                    f = false;
                }
            }
            if (f) {
                y_repeat = counter;
            }
        }

        if (z_repeat == -1) {
            bool f = true;
            for (int i = 0; i < 4 && f; ++i) {
                if (moons[0][i][2] != initial_state[i][2] || moons[1][i][2] != 0) {
                    f = false;
                }
            }
            if (f) {
                z_repeat = counter;
            }
        }
    }

    long long g1 = __gcd(x_repeat, y_repeat);
    long long p1 = x_repeat * y_repeat / g1;

    long long g2 = __gcd(p1, z_repeat);
    long long p = p1 * z_repeat / g2;

    cout << p;

    return 0;
}