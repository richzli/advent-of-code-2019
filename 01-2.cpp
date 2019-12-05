#include <cstdio>
using namespace std;

int main() {

    int total = 0;
    
    while (true) {
        int mass;
        scanf("%d", &mass);

        printf("-----\n");

        if (mass == 0) {
            break;
        }

        mass = (mass / 3) - 2;

        while (mass > 0) {
            total += mass;
            mass = (mass / 3) - 2;
        }
    }

    printf("%d", total);

    return 0;
}