#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Player.h"

using namespace std;

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
    vector<string> readMapFile(string filePath);
private:
    vector<Territory*> getTerritories();
    string removeSubstringByDelimiter(string& largeString, char delimiter);
    const string CONTINENT_TITLE = "[Continents]";
    const string TERRITORY_TITLE = "[Territories]";
    const char CONTINENT_DELIMITER = '=';
    const char TERRITORY_DELIMITER = ',';
};

class Map {
public:
    Map();
    ~Map();
    void addTerritory(Territory* territory);
    void addContinent(Continent* continent);
    vector<Continent*> getContinents();
    vector<Territory*> getTerritories();
    Continent* getContinentByName(string continentName);
    Territory* getTerritoryByName(string territoryName);
    bool validate();
    bool isConnected(vector<Territory*> graphTerritoryList);
    void traverse(Territory* startingTerritory, vector<Territory*> graphTerritoryList, map<Territory*, bool>& visited);
private:
    vector<Territory*> territoryList;
    vector<Continent*> continentList;
};

class Continent {
public:
    Continent(string name, int val);
    ~Continent();
    void addTerritory(Territory* territory);
    vector<Territory*> getTerritories();
    string getName();
private:
    string name;
    int value;
    vector<Territory*> territoryList;
};

class Territory {
public:
    Territory(string territoryName, Continent* newContinent);
    Territory();
    ~Territory();
    void addAdjacency(Territory* territory);
    static void addAdjacency(Territory* firstTerritory, Territory* secondTerritory);
    vector<Territory*> getAdjacencyList();
    void setContinent(Continent* newContinent);
    Continent* getContinent();
    string getName();
    void setOwner(Player* newOwner);
    void setOwner(Player* newOwner, int newNumArmies);
    void setArmies(int newNumArmies);
    void addArmies(int newNumArmies);
private:
    string name;
    Player* owner;
    int numArmies;
    Continent* continent;
    vector<Territory*> adjacencyList;
};


void testLoadMaps();