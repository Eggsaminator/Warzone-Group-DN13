#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "PlayerStrategies.h"

class PlayerStrategy;

using namespace std;

class Player {

public:
	Player();
	Player(string name);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	OrderList* issueOrder();


	void addTerritory(Territory*);

	
	OrderList* getOrdersList();
	void setOrdersList(OrderList* newOrdersList);
	OrderList* ordersList;
	
	string getName();
	void setName(string newName);
	
	Hand* getHand();
	void setHand(Hand*);

	int getReinforcementPool();
	void setReinforcementPool(int armyUnits);

	int getReinforcementPoolLeftToDeploy();
	void setReinforcementPoolLeftToDeploy(int armyUnits);
	
	vector<Territory*> getTerritories();
	void setTerritories(vector<Territory*> newTerritories);

	void setTruce(Player* tp);
	string getTruce();
	void addOrder(Orders* o);
	void setConquered(bool tf);
	bool getConquered();

	void addArmy(int army);
	void removeArmy(int army);
	void setPlayerStrategy(PlayerStrategy* newStrategy);
private:
	string name;
	string nameT;
	Hand* hand;
	bool territoryConquered = false;
	int reinforcementPool = 50;
	int reinforcementPoolLeftToDeploy = 0;
	vector<Territory*> territories;
	PlayerStrategy* strategy;
};

void testPlayers();