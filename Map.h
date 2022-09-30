#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Player.h"

using namespace std;

/*
Map file format:
TerritoryName, xCoordinate, yCoordinate, Continent, AdjacencyList[]
*/

// Forward declarations

class Map;
class Continent;
class Territory;
class Player;

//

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
    vector<Territory*> getTerritories();
    bool validate();
    bool isConnected(vector<Territory*> graphTerritoryList);
    void traverse(Territory* startingTerritory, vector<Territory*> graphTerritoryList, map<Territory*, bool> visited);
private:
    vector<Territory*> territoryList;
    vector<Continent*> continentList;
};

class Continent {
public:
    Continent(string name);
    ~Continent();
    void addTerritory(Territory* territory);
    vector<Territory*> getTerritories();
private:
    string name;
    int value;
    vector<Territory*> territoryList;
};

class Territory {
public:
    Territory(string territoryName, Continent* newContinent);
    ~Territory();
    void addAdjacency(Territory* territory);
    static void addAdjacency(Territory* firstTerritory, Territory* secondTerritory);
    vector<Territory*> getAdjacencyList();
    void setContinent(Continent* newContinent);
    Continent* getContinent();
private:
    string name;
    Player* owner;
    int numArmies;
    Continent* continent;
    vector<Territory*> adjacencyList;
};