#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

vector<int> d;
const int phase[4]{0, 1, 0, -1};

void fft() {
    vector<int> neww;

    int ds = d.size();
    
    for (int i = 0; i < ds; ++i) {
        long sum = 0l;
        int ind = -1;
        int ind2 = 0;
        while (ind < ds) {
            for (int j = 0; j <= i; ++j) {
                if (ind == -1) {
                    ind += 1;
                    continue;
                } else {
                    sum += phase[ind2] * d.at(ind);
                }
                ind += 1;
                if (ind >= ds) {
                    break;
                }
            }
            ind2 += 1;
            ind2 %= 4;
        }
        neww.push_back(abs(sum % 10));
    }
    d = neww;
}

int main() {
    char digits[1000];
    scanf("%s", digits);
    
    for (int i = 0; digits[i] != 0; ++i) {
        d.push_back(digits[i]-48);
    }

    for (int i = 0; i < 100; ++i) {
        fft();
    }

    for (int i = 0; i < 8; ++i) {
        printf("%d", d.at(i));
    }
}