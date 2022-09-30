#include "Map.h"

Map MapLoader::loadMap(string filePath) {
    Map map;
    return map;
}

vector<Territory*> MapLoader::getTerritories() {
    vector<Territory*> territories;

    return territories;
}

void Map::addTerritory(string name) {
    return;
}

bool Map::validate() {
    // Assume the map is valid then attempt to disprove it
    bool isValid = true;

    // Check that the map is a connected graph
    if (!isConnected(territoryList)) {
        isValid = false;
        return isValid;
    }

    // Check that the continents are connected subgraphs
    for (int i = 0; i < continentList.size(); i++) {
        if (!isConnected(continentList[i]->getTerritories())) {
            isValid = false;
            return isValid;
        }
    }

    // Check that each territory belongs to one and only one continent
    for (int i = 0; i < territoryList.size(); i++) {
        if (territoryList[i]->getContinent() == nullptr) {
            isValid = false;
            return isValid;
        }
    }

    return isValid;
}

bool Map::isConnected(vector<Territory*> graphTerritoryList) {
    map<Territory*, bool> visited;
    for (int i = 0; i < graphTerritoryList.size(); i++) {
        visited[graphTerritoryList[i]] = false;
    }

    traverse(graphTerritoryList[0], graphTerritoryList, visited);

    // Check if any node has not been visited
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[graphTerritoryList[i]]) {
            return false;
        }
    }
    return true;
}

void Map::traverse(Territory* startingTerritory, vector<Territory*> graphTerritoryList, map<Territory*, bool> visited) {
    if (!visited[startingTerritory]) {
        visited[startingTerritory] = true;
    }

    vector<Territory*> adjacencies = startingTerritory->getAdjacencyList();
    for (int i = 0; i < adjacencies.size(); i++) {
        // Ensure the node has yet to be visited
        if(visited[adjacencies[i]]) {
            continue;
        }

        // Ensure all checked adjacent tiles are within the list of territories to check
        for (int j = 0; j < graphTerritoryList.size(); j++) {
            if (adjacencies[i] == graphTerritoryList[j]) {
                // Check those territories
                traverse(adjacencies[i], graphTerritoryList, visited);
            }
        }
    }
}

Continent::Continent(string continentName) {
    name = continentName;
}

void Continent::addTerritory(Territory* territory) {
    territoryList.push_back(territory);
}

vector<Territory*> Continent::getTerritories() {
    return territoryList;
}

Territory::Territory(string territoryName, Continent* newContinent) {
    name = territoryName;
    setContinent(newContinent);
}

void Territory::addAdjacency(Territory* territory) {
    adjacencyList.push_back(territory);
}

void Territory::addAdjacency(Territory* firstTerritory, Territory* secondTerritory) {
    firstTerritory->addAdjacency(secondTerritory);
}

vector<Territory*> Territory::getAdjacencyList() {
    return adjacencyList;
}

void Territory::setContinent(Continent* newContinent) {
    continent = newContinent;
    newContinent->addTerritory(this);
}

Continent* Territory::getContinent() {
    return continent;
}