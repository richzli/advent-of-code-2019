#include <cstdio>
#include <cstdlib>
using namespace std;

bool wireOne[40000][40000];

int dist(int x, int y) {
    return abs(20000-x) + abs(20000-y);
}

void printG() {
    for (int i = 20000; i < 20010; ++i) {
        for (int j = 20000; j < 20010; ++j) {
            if (wireOne[i][j]) {
                printf("X");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main() {
    // this feels so inefficient but i can't think of any other way... i'm bad   
    for (size_t i = 0; i < 40000; ++i) {
        for (size_t j = 0; j < 40000; ++j) {
            wireOne[i][j] = false;
        }
    }
    
    int x = 20000, y = 20000;
    while (true) {
        char direction;
        int distance;
        scanf("%c%d,", &direction, &distance);
        if (direction == 'S') {
            break;
        }

        if (direction == 'L') {
            int newX = x - distance;
            for (x -= 1; x > newX; --x) {
                wireOne[x][y] = true;
            }
        } else if (direction == 'R') {
            int newX = x + distance;
            for (x += 1; x < newX; ++x) { 
                wireOne[x][y] = true;
            }
        } else if (direction == 'D') {
            int newY = y - distance;
            for (y -= 1; y > newY; --y) {
                wireOne[x][y] = true;
            }
        } else if (direction == 'U') {
            int newY = y + distance;
            for (y += 1; y < newY; ++y) {
                wireOne[x][y] = true;
            }
        }
        wireOne[x][y] = true;
    }

    int closest = dist(40000, 40000);

    x = 20000, y = 20000;
    while (true) {
        char direction;
        int distance;
        scanf("%c%d,", &direction, &distance);

        if (direction == 'S') {
            break;
        }

        if (direction == 'L') {
            int newX = x - distance;
            for (x -= 1; x > newX; --x) {
                if (wireOne[x][y]) {
                    if (dist(x, y) < closest) {
                        closest = dist(x, y);
                    }
                }
            }
        } else if (direction == 'R') {
            int newX = x + distance;
            for (x += 1; x < newX; ++x) { 
                if (wireOne[x][y]) {
                    if (dist(x, y) < closest) {
                        closest = dist(x, y);
                    }
                }
            }
        } else if (direction == 'D') {
            int newY = y - distance;
            for (y -= 1; y > newY; --y) {
                if (wireOne[x][y]) {
                    if (dist(x, y) < closest) {
                        closest = dist(x, y);
                    }
                }
            }
        } else if (direction == 'U') {
            int newY = y + distance;
            for (y += 1; y < newY; ++y) {
                if (wireOne[x][y]) {
                    if (dist(x, y) < closest) {
                        closest = dist(x, y);
                    }
                }
            }
        }

        if (wireOne[x][y]) {
            if (dist(x, y) < closest) {
                closest = dist(x, y);
            }
        }
    }

    printf("%d", closest);

    return 0;
}