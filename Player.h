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
	//vector<Territory*> toDefend();
	//vector<Territory*> toAttack();
	//void issueOrder(Orders newOrder);
	vector<int*> getNums();
	void setNum(int newVal);

private:
	string name;
	//Hand* hand;
	//vector<Territory*> territories;
	vector<int*> nums;
};