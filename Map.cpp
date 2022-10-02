#include "Map.h"

MapLoader::MapLoader() {

}

MapLoader::~MapLoader() {

}

Map MapLoader::loadMap(string filePath) {

    Map newMap;
    vector<string> mapFile = readMapFile(filePath);
    map<Territory*, vector<string>> adjacencyLists;

    int mode = 0;
    for (int i = 0; i < mapFile.size(); i++) {
        if (mapFile[i] == CONTINENT_TITLE) {
            mode = 1;
            continue;
        }
        if (mapFile[i] == TERRITORY_TITLE) {
            mode = 2;
            continue;
        }

        // Skip empty lines
        if (mapFile[i].size() == 0) {
            cout << "Empty line!" << endl;
            continue;
        }
        
        // Create continents
        if (mode == 1) {
            size_t delimiterPos = mapFile[i].find(CONTINENT_DELIMITER);
            if (delimiterPos == string::npos) {
                throw std::invalid_argument("Invalid map file: improper continent format detected");
            }
            string continentName = mapFile[i].substr(0, delimiterPos);
            mapFile[i].erase(0, delimiterPos + 1);
            int continentValue = stoi(mapFile[i]);

            cout << "Continent created: " << continentName << ": " << continentValue << endl;

            // ERROR! Gets overwritten
            Continent* cont = new Continent(continentName, continentValue);
            newMap.addContinent(cont);
            continue;
        }

        // Create territories
        if (mode == 2) {
            // Territory name
            size_t delimiterPos = mapFile[i].find(TERRITORY_DELIMITER);
            if (delimiterPos == string::npos) {
                throw std::invalid_argument("Invalid map file: improper territory format detected");
            }
            string territoryName = mapFile[i].substr(0, delimiterPos);
            mapFile[i].erase(0, delimiterPos + 1);

            // X-coordinate
            delimiterPos = mapFile[i].find(TERRITORY_DELIMITER);
            if (delimiterPos == string::npos) {
                throw std::invalid_argument("Invalid map file: improper territory format detected");
            }
            mapFile[i].erase(0, delimiterPos + 1);

            // Y-coordinate
            delimiterPos = mapFile[i].find(TERRITORY_DELIMITER);
            if (delimiterPos == string::npos) {
                throw std::invalid_argument("Invalid map file: improper territory format detected");
            }
            mapFile[i].erase(0, delimiterPos + 1);

            // Continent name
            delimiterPos = mapFile[i].find(TERRITORY_DELIMITER);
            if (delimiterPos == string::npos) {
                throw std::invalid_argument("Invalid map file: improper territory format detected");
            }
            string continentName = mapFile[i].substr(0, delimiterPos);
            mapFile[i].erase(0, delimiterPos + 1);

            // Adjacency list
            vector<string> adjacencyList;
            while ((delimiterPos = mapFile[i].find(TERRITORY_DELIMITER)) != std::string::npos) {
                adjacencyList.push_back(mapFile[i].substr(0, delimiterPos));
                mapFile[i].erase(0, delimiterPos + 1);
            }
            adjacencyList.push_back(mapFile[i]);

            // Get continent from continent name
            Continent* cont = newMap.getContinentByName(continentName);
            if (cont == nullptr) {
                throw std::invalid_argument("Invalid map file: improper territory format detected - continent not found");
            }

            cout << "Created territory " << territoryName << " in continent " << continentName << "with adjacencies: ";
            for (int j = 0; j < adjacencyList.size(); j++) {
                cout << adjacencyList[j] << ", ";
            }
            cout << endl;

            Territory* terr = new Territory(territoryName, cont);
            newMap.addTerritory(terr);
            adjacencyLists.insert(pair<Territory*, vector<string>>(terr, adjacencyList));
            continue;
        }
    }

    // Add adjacencies, now that all territories are constructed
    map<Territory*, vector<string>>::iterator it;
    for (it = adjacencyLists.begin(); it != adjacencyLists.end(); ++it) {
        //cout << it->second.size() << endl;
        for (int j = 0; j < it->second.size(); j++) {
            cout << it->second[j] << endl;
            Territory* adjTerr = newMap.getTerritoryByName(it->second[j]);
            if (adjTerr == nullptr) {
                throw std::invalid_argument("Invalid map file: improper territory format detected - territory not found");
            }

            it->first->addAdjacency(adjTerr);
        }
    }

    return newMap;
}

vector<string> MapLoader::readMapFile(string filePath) {
    ifstream file(filePath);
    string str;
    vector<string> fileContents;
    while(getline(file, str)) {
        fileContents.push_back(str);
    }

    return fileContents;
}

vector<Territory*> MapLoader::getTerritories() {
    vector<Territory*> territories;

    return territories;
}

Map::Map() {

}

Map::~Map() {

}

void Map::addTerritory(Territory* territory) {
    territoryList.push_back(territory);
}

void Map::addContinent(Continent* continent) {
    continentList.push_back(continent);
}

vector<Territory*> Map::getTerritories() {
    return territoryList;
}

Continent* Map::getContinentByName(string continentName) {
    for (int i = 0; i < continentList.size(); i++) {
        if (continentList[i]->getName() == continentName) {
            return continentList[i];
        }
    }
    return nullptr;
}

Territory* Map::getTerritoryByName(string territoryName) {
    for (int i = 0; i < territoryList.size(); i++) {
        if (territoryList[i]->getName() == territoryName) {
            return territoryList[i];
        }
    }
    return nullptr;
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

void Map::traverse(Territory* startingTerritory, vector<Territory*> graphTerritoryList, map<Territory*, bool>& visited) {
    if (!visited[startingTerritory]) {
        visited[startingTerritory] = true;
    }

    vector<Territory*> adjacencies = startingTerritory->getAdjacencyList();
    for (int i = 0; i < adjacencies.size(); i++) {
        // Filter adjacent tiles by those in the territory list
        bool isPresent = false;
        for (int j = 0; j < graphTerritoryList.size(); j++) {
            if (adjacencies[i] == graphTerritoryList[j]) {
                isPresent = true;
            }
        }

        // If not in the list, skip visiting the node
        if (!isPresent) {
            continue;
        }

        // Ensure the node has yet to be visited
        if(!visited[adjacencies[i]]) {
            // Check those territories
            traverse(adjacencies[i], graphTerritoryList, visited);
        }
    }
}

Continent::Continent(string continentName, int val) {
    name = continentName;
    value = val;
}

Continent::~Continent() {

}

string Continent::getName() {
    return name;
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

Territory::~Territory() {

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

string Territory::getName() {
    return name;
}