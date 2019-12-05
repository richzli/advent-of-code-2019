#include <cstdio>
#include <vector>
using namespace std;

#define vi vector<int>

int run(vi ops) {
    int i = 0;
    while (true) {
        int instruction = ops.at(i);
        int op = instruction % 100;

        if (op == 99) {
            break;
        }

        //printf("|%d %d %d %d %d| ", i, instruction, ops.at(i+1), ops.at(i+2), ops.at(i+3));

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
            int mode = instruction/100;
            
            int out;
            if (mode == 0) {
                out = ops.at(ops.at(i+1));
            } else if (mode == 1) {
                out = ops.at(i+1);
            }
            printf("%d\n", out);

            i += 2;
        } else if (op == 5) {
            int modes[] = {(instruction/100)%10, (instruction/1000)%10};

            int comp;
            if (modes[0] == 0) {
                comp = ops.at(ops.at(i+1));
            } else if (modes[0] == 1) {
                comp = ops.at(i+1);
            }

            int dest;
            if (modes[1] == 0) {
                dest = ops.at(ops.at(i+2));
            } else if (modes[1] == 1) {
                dest = ops.at(i+2);
            }

            //printf("{%d %d} ", comp, dest);

            if (comp != 0) {
                i = dest;
            } else {
                i += 3;
            }
        } else if (op == 6) {
            int modes[] = {(instruction/100)%10, (instruction/1000)%10};

            int comp;
            if (modes[0] == 0) {
                comp = ops.at(ops.at(i+1));
            } else if (modes[0] == 1) {
                comp = ops.at(i+1);
            }

            int dest;
            if (modes[1] == 0) {
                dest = ops.at(ops.at(i+2));
            } else if (modes[1] == 1) {
                dest = ops.at(i+2);
            }

            if (comp == 0) {
                i = dest;
            } else {
                i += 3;
            }
        } else if (op == 7) {
            int modes[] = {(instruction/100)%10, (instruction/1000)%10, (instruction/10000)%10};

            int first, second;
            if (modes[0] == 0) {
                first = ops.at(ops.at(i+1));
            } else if (modes[0] == 1) {
                first = ops.at(i+1);
            }
            if (modes[1] == 0) {
                second = ops.at(ops.at(i+2));
            } else if (modes[1] == 1) {
                second = ops.at(i+2);
            }

            int dest = ops.at(i+3);

            if (first < second) {
                ops.at(dest) = 1;
            } else {
                ops.at(dest) = 0;
            }

            i += 4;
        } else if (op == 8) {
            int modes[] = {(instruction/100)%10, (instruction/1000)%10, (instruction/10000)%10};

            int first, second;
            if (modes[0] == 0) {
                first = ops.at(ops.at(i+1));
            } else if (modes[0] == 1) {
                first = ops.at(i+1);
            }
            if (modes[1] == 0) {
                second = ops.at(ops.at(i+2));
            } else if (modes[1] == 1) {
                second = ops.at(i+2);
            }

            int dest = ops.at(i+3);

            if (first == second) {
                ops.at(dest) = 1;
            } else {
                ops.at(dest) = 0;
            }

            i += 4;
        }
    }

    return ops.at(0);
}

int main() {
    vi ops;

    while (true) {
        int op;
        scanf("%d,", &op);

        if (op == -2) {
            break;
        }

        ops.push_back(op);
    }

    //printf("%d\n", ops.size());
    run(ops);

    return 0;
}