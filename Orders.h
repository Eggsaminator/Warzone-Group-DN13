#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#pragma once
using namespace std;

class Player;
class Territory;

class Orders
{
private:
public:
	//critical methods
	friend ostream& operator << (ostream& os, const Orders& order); //stream insertion operator
	virtual string toString() const;

	virtual bool validate();
	virtual bool execute();
	virtual string getName();

};

class OrderList 
{
private:
public:
	string player;
	//orderlist should contain player so it can discern them
	//order list for teh player
	vector<Orders*> orders;
	//overall data present in the order list
	int numArmyUnit = 0;
	Territory* souTerritory;
	Territory* tarTerritory;

	//assigning datas
	OrderList();
	OrderList(string user);
	OrderList(string user, vector<Orders*> order);
	OrderList(OrderList& orderlist);
	~OrderList();

	//critical methods
	void move(int i, int j);
	void remove(int i);

	//extra methods
	friend ostream& operator << (ostream& os, const OrderList& order);
	void addOrder(Orders* order);
	virtual string toString() const;
};

class Deploy : public Orders
{
private:
public:
	Player* player;
	//name of the order
	const string name = "deploy";
	//data needed for the order
	int numArmyUnit = 0;
	Territory* tarTerritory;
	bool validated;
	bool executed;

	//assigning datas
	Deploy();
	Deploy(Player* p, int armyNum, Territory* tarT);
	Deploy(Deploy& deploy);
	~Deploy();

	//critical methods
	bool validate();
	bool execute();
	string getName();

	//extra methods
	friend ostream& operator << (ostream& os, const Deploy& order);
	virtual string toString() const;
};



class Advance : public Orders
{
private:
public:
	Player* player;
	//name of the order
	const string name = "advance";
	//data needed for the order
	int numArmyUnit = 0;
	Territory* souTerritory;
	Territory* tarTerritory;
	bool validated = false;
	bool executed = false;

	//assigning datas
	Advance();
	Advance(Player* p, int numArmyUnit, Territory* souTerritory, Territory* tarTerritory);
	Advance(Advance& advance);
	~Advance();

	//critical methods
	bool validate();
	bool execute();
	string getName();

	//extra methods
	friend ostream& operator << (ostream& os, const Advance& order);
	virtual string toString() const;
};

class Bomb : public Orders// usable only if user has Bomb card on hand
{
private:	
public:
	Player* player;
	//name of the order
	const string name = "bomb";
	//data needed for the order
	Territory* tarTerritory;
	bool validated = false;
	bool executed = false;

	//assigning datas
	Bomb();
	Bomb(Player* p, Territory* tarTerritory);
	Bomb(Bomb& bomb);
	~Bomb();

	//critical methods
	bool validate();
	bool execute();
	string getName();

	//extra methods
	friend ostream& operator << (ostream& os, const Bomb& order);
	virtual string toString() const;
};

class Blockade : public Orders// usable if user has blockade card on hand - validate()
{
private:
public:
	Player* player;
	//name of the order
	const string name = "blockade";
	//data needed for the order
	Territory * tarTerritory;
	bool validated = false;
	bool executed = false;

	//assigning datas
	Blockade();
	Blockade(Player* p, Territory* tarTerritory);
	Blockade(Blockade& blockade);
	~Blockade();

	//critical methods
	bool validate();
	bool execute();
	string getName();

	//extra methods
	friend ostream& operator << (ostream& os, const Blockade& order);
	virtual string toString() const;
};

class Airlift : public Orders // usable only if user has Airlift card on hand
{
private:
public:
	Player* player;
	//name of the order
	const string name = "airlift";
	//data needed for the order
	int numArmyUnit = 0;
	Territory* souTerritory;
	Territory* tarTerritory;
	bool validated = false;
	bool executed = false;

	//assigning datas
	Airlift();
	Airlift(Player* p, int numArmyUnit, Territory* souTerritory, Territory* tarTerritory);
	Airlift(Airlift& airlift);
	~Airlift();

	//critical methods
	bool validate();
	bool execute();
	string getName();

	//extra methods
	friend ostream& operator << (ostream& os, const Airlift& order);
	virtual string toString() const;
};

class Negotiate : public Orders// usable if user has Diplomacy card in hand
{
private:
public:
	Player* player;
	Player* tarPlayer;
	//name of the order
	const string name = "negotiate";
	//data needed for the order
	bool validated = false;
	bool executed = false;

	//assigning datas
	Negotiate();
	Negotiate(Player* p, Player* tp);
	Negotiate(Negotiate& negotiate);
	~Negotiate();

	//critical methods
	bool validate();
	bool execute();
	string getName();

	//extra methods
	friend ostream& operator << (ostream& os, const Negotiate& order);
	virtual string toString() const;
};

void testOrdersList();
void testOrderExecution();