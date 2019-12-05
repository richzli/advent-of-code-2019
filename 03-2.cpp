#include <cstdio>
#include <cstdlib>
using namespace std;

const int SIZE = 20000;
const int ORIGIN = SIZE / 4;
int wireOne[SIZE][SIZE];

int dist(int x, int y) {
    return abs(ORIGIN-x) + abs(ORIGIN-y);
}

void printG() {
    for (int i = ORIGIN + 9; i >= ORIGIN; --i) {
        for (int j = ORIGIN; j < ORIGIN + 10; ++j) {
            printf("%02d ", wireOne[j][i]);
        }
        printf("\n");
    }
}

int main() {
    // this feels so inefficient but i can't think of any other way... i'm bad   
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            wireOne[i][j] = -1;
        }
    }
    
    int counter = 1;
    int x = ORIGIN, y = ORIGIN;
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
                wireOne[x][y] = counter;
                ++counter;
            }
        } else if (direction == 'R') {
            int newX = x + distance;
            for (x += 1; x < newX; ++x) { 
                wireOne[x][y] = counter;
                ++counter;
            }
        } else if (direction == 'D') {
            int newY = y - distance;
            for (y -= 1; y > newY; --y) {
                wireOne[x][y] = counter;
                ++counter;
            }
        } else if (direction == 'U') {
            int newY = y + distance;
            for (y += 1; y < newY; ++y) {
                wireOne[x][y] = counter;
                ++counter;
            }
        }
        wireOne[x][y] = counter;
        ++counter;
    }

    //printG();
    int closest = 10*SIZE;

    counter = 0, x = ORIGIN, y = ORIGIN;
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
                if (wireOne[x][y] != -1) {
                    if (counter + wireOne[x][y] < closest) {
                        closest = counter + wireOne[x][y];
                    }
                }
                ++counter;
            }
        } else if (direction == 'R') {
            int newX = x + distance;
            for (x += 1; x < newX; ++x) { 
                if (wireOne[x][y] != -1) {
                    if (counter + wireOne[x][y] < closest) {
                        closest = counter + wireOne[x][y];
                    }
                }
                ++counter;
            }
        } else if (direction == 'D') {
            int newY = y - distance;
            for (y -= 1; y > newY; --y) {
                if (wireOne[x][y] != -1) {
                    if (counter + wireOne[x][y] < closest) {
                        closest = counter + wireOne[x][y];
                    }
                }
                ++counter;
            }
        } else if (direction == 'U') {
            int newY = y + distance;
            for (y += 1; y < newY; ++y) {
                if (wireOne[x][y] != -1) {
                    if (counter + wireOne[x][y] < closest) {
                        closest = counter + wireOne[x][y];
                    }
                }
                ++counter;
            }
        }

        if (wireOne[x][y] != -1) {
            if (counter + wireOne[x][y] < closest) {
                closest = counter + wireOne[x][y];
            }
        }
        ++counter;
    }

    printf("%d", closest);

    return 0;
}