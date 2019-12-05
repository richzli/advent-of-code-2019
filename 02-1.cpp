#include <cstdio>
#include <vector>
using namespace std;

#define vi vector<int>

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

    printf("%d", ops.at(0));
}