#include <cstdio>
using namespace std;

bool check(int num) {
    char buf[6];
    sprintf(buf, "%d", num);

    bool pair = false;
    char curr = buf[0];
    for (int i = 1; i < 6; ++i) {
        if (buf[i] < curr) {
            return false;
        } else if (buf[i] == curr) {
            pair = true;
        }
        curr = buf[i];
    }

    return pair;
}

int main() {
    int count = 0;
    for (int i = 273025; i <= 767253; ++i) {
        if (check(i)) {
            printf("%d ", i);
            ++count;
        }
    }

    printf("\n%d", count);

    return 0;
}