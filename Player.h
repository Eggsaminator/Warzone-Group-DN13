#pragma once
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

class Player {

public:
	Player();
	Player(string name);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder(string name);


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

	void setTerritoriesToAttack(vector<Territory*>);
	void setTerritoriesToDefend(vector<Territory*>);

private:
	string name;
	Hand* hand;
	int reinforcementPool = 50;
	int reinforcementPoolLeftToDeploy = 0;
	vector<Territory*> territories;
	vector<Territory*> territoriesToAttack;
	vector<Territory*> territoriesToDefend;
};

void testPlayers();