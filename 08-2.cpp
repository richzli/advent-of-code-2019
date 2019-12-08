#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string image;
    getline(cin, image);

    int layersize = 25 * 6;

    int decoded[25][6];

    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 6; ++j) {
            decoded[i][j] = 2;
        }
    }

    for (int i = (image.length()/layersize) - 1; i >= 0; --i) {
        string layer;
        layer = image.substr(layersize*i, layersize);
        
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 25; ++j) {
                char c = layer.at(25*i+j);
                if (c == '0') {
                    decoded[j][i] = 0;
                } else if (c == '1') {
                    decoded[j][i] = 1;
                }
            }
        }
    }

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 25; ++j) {
            printf("%c", decoded[j][i] == 1 ? '#' : ' ');
        }
        printf("\n");
    }

    return 0;
}