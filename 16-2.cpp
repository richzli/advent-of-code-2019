#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> d;
vector<int> sums;

void fft() {
    vector<int> neww;
    vector<int> newwsums;

    neww.push_back(0);
    newwsums.push_back(0);

    int ds = d.size();
    
    for (int i = 1; i < ds; ++i) {
        long sum = 0l;
        int ind = 0;
        int phase = 1;
        while (ind <= ds) {
            ind += i;
            if (ind > ds) {
                break;
            }
            sum += phase * (sums.at(min(ind+i-1, ds-1))-sums.at(ind-1));
            phase *= -1;
            ind += i;
        }
        neww.push_back(abs(sum % 10));
        newwsums.push_back(newwsums.at(i-1) + neww.at(i));
    }
    d = neww;
    sums = newwsums;
}

int main() {
    char digits[1000];
    scanf("%s", digits);
    
    d.push_back(0);

    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; digits[j] != 0; ++j) {
            d.push_back(digits[j]-48);
        }
    }

    for (size_t i = 0; i < d.size(); ++i) {
        if (i == 0) {
            sums.push_back(d.at(0));
        } else {
            sums.push_back(sums.at(i-1) + d.at(i));
        }
    }

    for (int i = 0; i < 100; ++i) {
        printf("%d ", i);
        fft();
    }

    int offset = 5976684;

    for (int i = offset; i < offset + 8; ++i) {
        printf("%d", d.at(i));
    }
}