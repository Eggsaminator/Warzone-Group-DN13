#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
class Territory;
class Player;
class Map;

class PlayerStrategy {
public:
	PlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
	virtual bool issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;
	Player* getPlayer();
	vector<Player*> getAllPlayers();
	Map* getMap();
private:
	Player* player;
	vector<Player*> allPlayers;
	Map* gameMap;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	HumanPlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
	bool issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
	bool issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	BenevolentPlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
	bool issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
	bool issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	CheaterPlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
	bool issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};