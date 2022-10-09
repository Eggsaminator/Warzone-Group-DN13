
#include <string>
#include <iostream>
#include "Map.h"

using namespace std;

void testLoadMaps() {
    vector<string> mapList;
    // Map Canada.map is valid
    mapList.push_back("Canada.map");
    // Map StarWars.map exists in proper format, but the continent X WING FIGHTER is not connected.
    // (Can be seen in territories x3 and x4)
    mapList.push_back("StarWars.map");
    // Map badMap.map exists in proper format, but the territories 41, 42 and 43 are a closed loop.
    mapList.push_back("badMap.map");
    // Map badFile.txt is not a .map file. It's an auto-generated .rc file that I converted to a .txt.
    mapList.push_back("badFile.rc");

    MapLoader mapLoader;
    for (int i = 0; i < mapList.size(); i++) {
        try {
            Map map = mapLoader.loadMap(mapList[i]);
            if (map.validate()) {
                cout << "Map is valid." << endl;
            }
            else {
                cout << "Map is invalid." << endl;
            }
        }
        catch (invalid_argument) {
            cout << "Error. Exception caught. Map invalid." << endl;
        }
    }
}