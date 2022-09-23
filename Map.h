#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

/*
Map file format:
TerritoryName, xCoordinate, yCoordinate, Continent, AdjacencyList[]
*/

class MapLoader {
public:
    MapLoader();
    ~MapLoader();
    Map loadMap(string filePath);
private:
    vector<Territory*> getTerritories();
};

class Map {
public:
    Map();
    ~Map();
    void addTerritory(string name);
    bool validate();
private:
};

struct Continent {
    int value;
    vector<Territory*> territoryList;
};

class Territory {
public:
    Territory(string name);
    ~Territory();
    void addAdjacency(Territory territory);
    static void addAdjacency(Territory firstTerritory, Territory secondTerritory);
private:
    string name;
    Player* owner;
    Continent* continent;
    vector<Territory*> adjacencyList;
};