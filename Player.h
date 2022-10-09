#pragma once
#include <string>
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
	void issueOrder(String name);
	OrderList* ordersList;
	string name;
	Hand* hand;
	vector<Territory*> territories;
private:
	
	
};