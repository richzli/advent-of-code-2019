#include <cstdio>
#include <vector>
using namespace std;

#define vi vector<int>

int run(vi ops) {
    int i = 0;
    while (true) {
        int instruction = ops.at(i);
        int op = instruction % 100;

        printf("%d %d %d %d %d\n", instruction, op, ops.at(i+1), ops.at(i+2), ops.at(i+3));

        if (op == 99) {
            break;
        }

        if (op == 1) {
            int modes[] = {(instruction/100)%10, (instruction/1000)%10, (instruction/10000)%10};

            int a, b;
            if (modes[0] == 0) {
                a = ops.at(ops.at(i+1));
            } else if (modes[0] == 1) {
                a = ops.at(i+1);
            }
            if (modes[1] == 0) {
                b = ops.at(ops.at(i+2));
            } else if (modes[1] == 1) {
                b = ops.at(i+2);
            }
            int out = ops.at(i+3);
            ops.at(out) = a + b;
            i += 4;
        } else if (op == 2) {
            int modes[] = {(instruction/100)%10, (instruction/1000)%10, (instruction/10000)%10};

            int a, b;
            if (modes[0] == 0) {
                a = ops.at(ops.at(i+1));
            } else if (modes[0] == 1) {
                a = ops.at(i+1);
            }
            if (modes[1] == 0) {
                b = ops.at(ops.at(i+2));
            } else if (modes[1] == 1) {
                b = ops.at(i+2);
            }
            int out = ops.at(i+3);
            ops.at(out) = a * b;

            i += 4;
        } else if (op == 3) {
            int out = ops.at(i+1);
            int in;
            scanf("%d", &in);
            ops.at(out) = in;

            i += 2;
        } else if (op == 4) {
            int out = ops.at(i+1);
            printf("%d\n", ops.at(out));

            i += 2;
        }
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

    run(ops);

    return 0;
}