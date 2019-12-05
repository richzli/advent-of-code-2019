#include <cstdio>
using namespace std;

int main() {

    int total = 0;
    
    while (true) {
        int mass;
        scanf("%d", &mass);

        if (mass == 0) {
            break;
        }

        total += (mass / 3) - 2;
    }

    printf("%d", total);

    return 0;
}