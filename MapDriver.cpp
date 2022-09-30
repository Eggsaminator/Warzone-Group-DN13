
#include <string>
#include <iostream>
#include "Map.h"

using namespace std;

int main() {
    cout << "hello world!";

    MapLoader mapLoader;
    mapLoader.loadMap("hello there");
    return 0;
}