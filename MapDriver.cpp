
#include <string>
#include <iostream>
#include "Map.h"

using namespace std;

int main() {
    MapLoader mapLoader;
    Map map = mapLoader.loadMap("Canada.map");

    /*Map map;
    Continent cont1("cont1", 1);
    Territory terr1("terr1", &cont1);
    Territory terr2("terr2", &cont1);
    Territory terr3("terr3", &cont1);

    terr1.addAdjacency(&terr2);
    terr2.addAdjacency(&terr1);
    terr2.addAdjacency(&terr3);
    terr3.addAdjacency(&terr2);

    map.addTerritory(&terr1);
    map.addTerritory(&terr2);
    map.addTerritory(&terr3);

    map.addContinent(&cont1);//*/

    cout << map.validate();
    cin.get();

    return 0;
}