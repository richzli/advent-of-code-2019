#include <cstdio>
#include <vector>
using namespace std;

#define vi vector<int>

int run(vi ops, int noun, int verb) {
    ops.at(1) = noun;
    ops.at(2) = verb;

    int i = 0;
    while (true) {
        int op = ops.at(i);

        if (op == 99) {
            break;
        }

        int out = ops.at(i+3);
        int a = ops.at(ops.at(i+1));
        int b = ops.at(ops.at(i+2));

        if (op == 1) {
            ops.at(out) = a + b;
        } else if (op == 2) {
            ops.at(out) = a * b;
        }

        i += 4;
    }

    return ops.at(0);
}

int main() {
    vi ops;

    while (true) {
        int op;
        scanf("%d,", &op);

        if (op == -1) {
            break;
        }

        ops.push_back(op);
    }

    bool done = false;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            vi computer;
            computer = ops;

            int result;
            result = run(computer, i, j);

            if (result == 19690720) {
                printf("%d%d", i, j);
                done = true;
                break;
            }
        }
        if (done) {
            break;
        }
    }
}