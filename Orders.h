#include <string>
#include <vector>
#include <sstream>
#pragma once
using namespace std;

class Player;
class Territory;

class Orders
{
private:
public:
	//assigning datas
	Orders();
	Orders(Orders& orders);
	~Orders();

	//critical methods
	friend ostream& operator << (ostream& os, const Deploy& air); //stream insertion operator
	string toString();

	/*
	//methods
	void execute();
	bool validate();*/
};

class OrderList {
private:
public:
	//orderlist should contain player so it can discern them
	Player* curUser;
	//order list for teh player
	vector<Orders*> orders;
	//overall data present in the order list
	int numArmyUnit = 0;
	Territory* souTerritory;
	Territory* tarTerritory;

	//assigning datas
	OrderList();
	OrderList(Player* user, vector<Orders*> order);
	OrderList(OrderList& orderlist);
	~OrderList();

	//critical methods
	bool remove();
	bool move();

	//extra methods
	void addOrder(Orders* order);

	/*
	//methods
	//friend ostream& operator << (ostream& os, const OrderList& air);
	string toString();
	
	void execute();
	bool validate();*/
};


inline ostream& operator << (ostream& os, OrderList const& air);

class Deploy : public Orders
{
private:
public:
	//name of the order
	const string name = "deploy";
	//data needed for the order
	int numArmyUnit = 0;
	Territory* tarTerritory;

	//assigning datas
	Deploy();
	Deploy(int armyNum, Territory* tarT);
	Deploy(Deploy& deploy);
	~Deploy();

	//critical methods
	bool validate();
	void execute();

	/*
	//methods
	friend ostream& operator << (ostream& os, const Deploy& air);
	string toString();
	bool validate();
	void execute();*/
};



class Advance : public Orders
{
private:
public:
	//name of the order
	const string name = "advance";
	//data needed for the order
	int numArmyUnit = 0;
	Territory* souTerritory;
	Territory* tarTerritory;

	//assigning datas
	Advance();
	Advance(int numArmyUnit, Territory* souTerritory, Territory* tarTerritory);
	Advance(Advance& advance);
	~Advance();

	//critical methods
	bool validate();
	void execute();

	/*
	//methods
	friend ostream& operator << (ostream& os, const Advance& air);
	string toString();
	bool validate();
	void execute();*/
};

class Bomb : public Orders// usable only if user has Bomb card on hand
{
private:	
public:
	//name of the order
	const string name = "bomb";
	//data needed for the order
	Territory* tarTerritory;

	//assigning datas
	Bomb();
	Bomb(Territory* tarTerritory);
	Bomb(Bomb& bomb);
	~Bomb();

	//critical methods
	bool validate();
	void execute();
	/*
	//methods
	friend ostream& operator << (ostream& os, const Bomb& air);
	string toString();
	bool validate();
	void execute();*/
};

class Blockade : public Orders// usable if user has blockade card on hand - validate()
{
private:
public:
	//name of the order
	const string name = "blockade";
	//data needed for the order
	Territory * tarTerritory;

	//assigning datas
	Blockade();
	Blockade(Territory* tarTerritory);
	Blockade(Blockade& blockade);
	~Blockade();

	//critical methods
	bool validate();
	void execute();

	/*
	//methods
	friend ostream& operator << (ostream& os, const Blockade& air);
	string toString() const;
	bool validate();
	void execute();*/
};

class Airlift : public Orders // usable only if user has Airlift card on hand
{
private:
public:
	//name of the order
	const string name = "airlift";
	//data needed for the order
	int numArmyUnit = 0;
	Territory* souTerritory;
	Territory* tarTerritory;

	//assigning datas
	Airlift();
	Airlift(int numArmyUnit, Territory* souTerritory, Territory* tarTerritory);
	Airlift(Airlift& airlift);

	//critical methods
	bool validate();
	void execute();

	/*
	//methods
	friend ostream& operator << (ostream& os, const Airlift& air);
	string toString();
	bool validate();
	void execute();*/
};

class Negotiate : public Orders// usable if user has Diplomacy card in hand
{
private:
public:
	//name of the order
	const string name = "negotiate";
	//data needed for the order
	Territory* tarTerritory;

	//assigning datas
	Negotiate();
	Negotiate(Territory* tarTerritory);
	Negotiate(Negotiate& negotiate);
	~Negotiate();

	//critical methods
	bool validate();
	void execute();

	/*
	//methods
	friend ostream& operator << (ostream& os, const Negotiate& air);
	string toString();*/
};

//string toString();