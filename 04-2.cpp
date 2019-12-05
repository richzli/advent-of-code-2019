#include <cstdio>
using namespace std;

bool check(int num) {
    char buf[6];
    sprintf(buf, "%d", num);

    bool pair = false;
    int run = 1;
    char curr = buf[0];
    for (int i = 1; i < 6; ++i) {
        if (buf[i] < curr) {
            return false;
        } else if (buf[i] == curr) {
            ++run;
        } else {
            if (run == 2) {
                pair = true;
            }
            run = 1;
        }
        curr = buf[i];
    }

    if (run == 2) {
        pair = true;
    }

    return pair;
}

int main() {
    int count = 0;
    for (int i = 273025; i <= 767253; ++i) {
        if (check(i)) {
            //printf("%d ", i);
            ++count;
        }
    }

    printf("%d", count);

    return 0;
}