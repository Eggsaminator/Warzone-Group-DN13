#pragma once
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

class OrderList;
class Player;
class Map;
class Territory;

class PlayerStrategy {
public:
	PlayerStrategy(Player* p);
	virtual OrderList* issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;
	friend ostream& operator << (ostream& os, const PlayerStrategy& strategy);
protected:
	vector<Territory*> getAdjacentEnemyTerritories(Territory* origin);
	Territory* getStrongestTerritory();
	Player* player;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	HumanPlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
	OrderList* issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
private:
	vector<Player*> allPlayers;
	Map* gameMap;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy(Player* player);
	~AggressivePlayerStrategy();
	AggressivePlayerStrategy(AggressivePlayerStrategy* strategy);

	OrderList* issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
private:
	vector<Card*>* getAggressiveCards();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	BenevolentPlayerStrategy(Player* player);
	~BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(BenevolentPlayerStrategy* strategy);

	OrderList* issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
private:
	Territory* getWeakestTerritory();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy(Player* player);
	~NeutralPlayerStrategy();
	NeutralPlayerStrategy(NeutralPlayerStrategy* strategy);

	OrderList* issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
private:
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	CheaterPlayerStrategy(Player* player);
	~CheaterPlayerStrategy();
	CheaterPlayerStrategy(CheaterPlayerStrategy* strategy);

	OrderList* issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
private:
};