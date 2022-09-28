#include <string>
#pragma once
using namespace std;

class Orders
{
private:
	// current user
	string curUser = "";
public:
	Orders();
	//Orders(const Orders& o);
	Orders(string curUser);
};

class OrderList {

};

class Deploy : public Orders
{
private:
	//name - current user - number of army units - target territory
	string name = "deploy";
	int numArmyUnit = 0;
public:
	Deploy();
	Deploy(string name, int numArmyUnit);
	void setCurrentUser(string curUser);
	void setName(string name);
	std::string getCurrentUser();
	std::string getName();
	bool validate();
	void execute();
};

inline string Deploy::getName() { return name; }


class Advance : public Orders
{

private:
	//name - current user - umber of army territory - source territory(vector from Map) - target territory(vector from Map)
	string name = "deploy";
	int numArmyUnit = 0;
public:
	Advance();
	Advance(string name, int numArmyUnit);
	bool validate();
	void execute();
};

class Bomb : public Orders // usable only if user has Bomb card on hand
{
private:
	//name - current user - target territory
	string name = "bomb";
	
public:
	Bomb();
	Bomb(string name);
	bool validate();
	void execute();
};

class Blockade : public Orders // usable if user has blockade card on hand - validate()
{
private:
	//name - current user - target territory
	string name = "blockade";
public:
	Blockade();
	Blockade(std::string name);
	bool validate();
	void execute();
};

class Airlift : public Orders // usable only if user has Airlift card on hand
{
private:
	//name - current user - number og army units - source territory - target territory
	string name = "airlift";
	int numArmyUnit = 0;
public:
	Airlift();
	Airlift(string name, int numArmyUnit);
	bool validate();
	void execute();
};

class Negotiate : public Orders // usable if user has Diplomacy card in hand
{
private:
	//name - current user - target players
	string name = "negotiate";
	string tarUser = "";
public:
	Negotiate();
	Negotiate(string tarUser, string name);
	bool validate();
	void execute();
};
