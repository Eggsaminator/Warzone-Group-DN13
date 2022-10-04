#include <string>
#include <vector>
#pragma once
using namespace std;

class Player;
class Territory;


class Orders
{
private:
	string name;
public:
	//default constructor
	Orders();
	//parametized constructor
	//Orders(Orders& o);
	//copy constructor
	Orders(Orders& orders);

	vector<Orders> order = {};
	Player* curUser;

	//methods
	void execute();
	bool validate();
};

class OrderList : public Orders{
private:
	vector<Orders*> orders;
	// current user (player section)
	string curUser = "";
	//also needs territory (map section)

public:
	//default constructor
	OrderList();
	//parametized constructor
	OrderList(vector<Orders> o);
	//copy constructor
	OrderList(OrderList &orderlist);

	//methods
	bool remove();
	bool move();
};

class Deploy : public Orders
{
private:
	//name - current user - number of army units - target territory
	const string name = "deploy"; // may not need these (could be deleted later on if found)
	int numArmyUnit = 0;
public:
	//default constructor
	Deploy();
	//parametized constructor
	Deploy(Player* curUser, int numArmyUnit, Territory* tarTerritory);
	//copy constructor
	Deploy(Deploy& deploy);

	Player* curUser;
	Territory* tarTerritory;

	//methods
	bool validate();
	void execute();
};



class Advance
{

private:
	//name - current user(player) - number of army territory - source territory(vector from Map) - target territory(vector from Map)
	const string name = "advance";
	int numArmyUnit = 0;
public:
	//default constructor
	Advance();
	//parametized constructor
	Advance(Player* curUser, int numArmyUnit, Territory* souTerritory, Territory* tarTerritory);
	//copy constructor
	Advance(Advance& advance);

	Player* curUser;
	Territory* souTerritory;
	Territory* tarTerritory;

	//methods
	bool validate();
	void execute();
};

class Bomb// usable only if user has Bomb card on hand
{
private:
	//name - current user - target territory
	const string name = "bomb";
	
public:
	//default constructor
	Bomb();
	//parametized constructor
	Bomb(Player* curUser, Territory* tarTerritory);
	//copy constructor
	Bomb(Bomb& bomb);

	Player* curUser;
	Territory* tarTerritory;

	//methods
	bool validate();
	void execute();
};

class Blockade // usable if user has blockade card on hand - validate()
{
private:
	//name - current user - target territory
	const string name = "blockade";
public:
	//default constructor
	Blockade();
	//parametized constructor
	Blockade(Player* curUser, Territory* tarTerritory);
	//copy constructor
	Blockade(Blockade& blockade);

	Player* curUser;
	Territory* tarTerritory;

	//methods
	bool validate();
	void execute();
};

class Airlift// usable only if user has Airlift card on hand
{
private:
	//name - current user - number og army units - source territory - target territory
	const string name = "airlift";
	int numArmyUnit = 0;
public:
	//default constructor
	Airlift();
	//parametized constructor
	Airlift(Player* curUser, int numArmyUnit, Territory* souTerritory, Territory* tarTerritory);
	//copy constructor
	Airlift(Airlift& airlift);

	Player* curUser;
	Territory* souTerritory;
	Territory* tarTerritory;

	//methods
	bool validate();
	void execute();
};

class Negotiate// usable if user has Diplomacy card in hand
{
private:
	//name - current user - target players
	const string name = "negotiate";
	string tarUser = "";
public:
	//default constructor
	Negotiate();
	//parametized constructor
	Negotiate(Player* curUser, Territory* tarTerritory);
	//copy constructor
	Negotiate(Negotiate& negotiate);

	Player* curUser;
	Territory* souTerritory;
	Territory* tarTerritory;

	//methods
	bool validate();
	void execute();
};
