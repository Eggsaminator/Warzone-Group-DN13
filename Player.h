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
	
	vector<Territory*> getTerritories();
	void setTerritories(vector<Territory*> newTerritories);

	void addArmy(int army);
	void removeArmy(int army);
	int getReinforcementPool();
private:
	string name;
	Hand* hand;
	vector<Territory*> territories;
	int reinforcement_pool;
};

void testPlayers();