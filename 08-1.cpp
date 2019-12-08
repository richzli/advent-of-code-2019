#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string image;
    getline(cin, image);

    int minzero = 25 * 6;
    int ones = 0, twos = 0;

    int layersize = 25 * 6;
    for (size_t i = 0; i < image.length()/layersize; ++i) {
        string layer;
        layer = image.substr(layersize*i, layersize);
        size_t zeros = count(layer.begin(), layer.end(), '0');
        if (minzero > zeros) {
            minzero = zeros;
            ones = count(layer.begin(), layer.end(), '1');
            twos = count(layer.begin(), layer.end(), '2');
        }
    }
    
    printf("%d\n", ones * twos);

    return 0;
}