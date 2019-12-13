#include <cstdio>
#include <cmath>
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

    for (int steps = 0; steps < 1000; ++steps) {
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
    }

    int energy = 0;
    for (int i = 0; i < 4; ++i) {
        int pot = 0;
        int kin = 0;
        for (int j = 0; j < 3; ++j) {
            pot += abs(moons[0][i][j]);
            kin += abs(moons[1][i][j]);
        }
        energy += pot * kin;
    }

    printf("%d", energy);

    return 0;
}