#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Card;
class OrderList;
class Player;
class Territory;

class PlayerStrategy {
public:
	PlayerStrategy(Player* player);
	virtual OrderList* issueOrder() = 0;
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDefend() = 0;
	friend ostream& operator << (ostream& os, const PlayerStrategy& strategy);
protected:
	vector<Territory*> getAdjacentEnemyTerritories(Territory* origin);
	Territory* getStrongestTerritory();
	Player* player;
private:
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	HumanPlayerStrategy();
	HumanPlayerStrategy(Player* player);
	~HumanPlayerStrategy();
	HumanPlayerStrategy(HumanPlayerStrategy* strategy);

	OrderList* issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
private:
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy();
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
	BenevolentPlayerStrategy();
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
	NeutralPlayerStrategy();
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
	CheaterPlayerStrategy();
	CheaterPlayerStrategy(Player* player);
	~CheaterPlayerStrategy();
	CheaterPlayerStrategy(CheaterPlayerStrategy* strategy);

	OrderList* issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
private:
};