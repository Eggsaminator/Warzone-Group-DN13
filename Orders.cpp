#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Player.h"

/*----------------------------------------------------------------------order class---------------------------------------------------------------------*/
Orders::Orders() {

}

Orders::~Orders() {

}

ostream& operator << (ostream& os, const Orders& order) {
	return os;
}

string Orders::toString() const{
	return "\norder string: ";
}
/*----------------------------------------------------------------------orderlist class---------------------------------------------------------------------*/
OrderList::OrderList() {

}

OrderList::OrderList(Player* user, vector<Orders*> o) {
	curUser = user;
	orders = o;
}

OrderList::OrderList(OrderList& order) {
	curUser = order.curUser;
	orders = order.orders;
}

void OrderList::move(int i, int j) {
	if (i < 0 || i >= orders.size() || j < 0 || j >= orders.size()) {
		cout << "\nIndexes specified not in range of vector size";
	}
	else {
		if (i > j) {
			rotate(orders.rend() - i - 1, orders.rend() - i, orders.rend() - j);
		}
		else {
			rotate(orders.begin() + i, orders.begin() + 1, orders.begin() + j + 1);
		}
		cout << "\nOrder position successfully switched";
	}
}

void OrderList::remove(int i) {
	if (i < 0 || i >= orders.size()) {
		cout << "\nSpecified location is outside the range";
	}else {
		orders.erase(orders.begin() + i);
		cout << "\nOrder removed";
	}
}

void OrderList::addOrder(Orders* order) {
	this->orders.push_back(order);
}

string OrderList::toString() const{
	//calls toString() method in Order class for the order data
	string str;
	for (size_t i = 0; i < orders.size(); i++) {
		str = str + orders.at(i)->toString();
	}
	return str;
}

/*----------------------------------------------------------------------deploy class---------------------------------------------------------------------*/
Deploy::Deploy() {

}

Deploy::Deploy(int naw, Territory* tt) {
	numArmyUnit = naw;
	tarTerritory = tt;
}

Deploy::Deploy(Deploy& deploy) {
	numArmyUnit = deploy.numArmyUnit;
	tarTerritory = &(*deploy.tarTerritory);
}

Deploy::~Deploy() {

}

bool Deploy::validate() {
	cout << "\nvalidate for deploy order";
	return true;
}

bool Deploy::execute() {
	cout << "\nexecute for deploy order\n";
	executed = true;
	return executed;
}

string Deploy::toString() const{
	string s1 = name;
	string s2 = to_string(numArmyUnit);
	return string("\ntesting deploy: " + s1 + " " + s2);
}

/*----------------------------------------------------------------------advance class---------------------------------------------------------------------*/
Advance::Advance() {

}

Advance::Advance(int naw, Territory* st, Territory* tt) {
	numArmyUnit = naw;
	souTerritory = st;
	tarTerritory = tt;
}

Advance::Advance(Advance& advance) {
	numArmyUnit = advance.numArmyUnit;
	souTerritory = &(*advance.souTerritory);
	tarTerritory = &(*advance.tarTerritory);
}

Advance::~Advance() {

}

bool Advance::validate() {
	cout << "\nvalidate for advance order";
	return true;
}

bool Advance::execute() {
	cout << "\nexecute for advance order\n";
	executed = true;
	return executed;
}

string Advance::toString() const {
	string s1 = name;
	string s2 = to_string(numArmyUnit);
	return string("\ntesting advance: " + s1 + " " + s2);
}

/*----------------------------------------------------------------------bomb class---------------------------------------------------------------------*/
Bomb::Bomb() {

}

Bomb::Bomb(Territory* tt) {
	tarTerritory = tt;
}

Bomb::Bomb(Bomb& bomb) {
	tarTerritory = &(*bomb.tarTerritory);
}

Bomb::~Bomb() {

}

bool Bomb::validate() {
	//if user has card "bomb" return true
	cout << "\nvalidate for bomb order";
	return true;
}

bool Bomb::execute() {
	cout << "\nexecute for bomb order\n";
	executed = true;
	return executed;
}

string Bomb::toString() const {
	string s1 = name;
	return string("\ntesting bomb: " + s1);
}

/*----------------------------------------------------------------------blockade class---------------------------------------------------------------------*/
Blockade::Blockade() {

}

Blockade::Blockade(Territory* tt) {
	tarTerritory = tt;
}

Blockade::Blockade(Blockade& blockade) {
	tarTerritory = &(*blockade.tarTerritory);
}

Blockade::~Blockade() {

}

bool Blockade::validate() {
	//if user has card "blockade" return true
	cout << "\nvalidate for blockade order";
	return true;
}

bool Blockade::execute() {
	cout << "\nexecute for blockade order\n";
	executed = true;
	return executed;
}

string Blockade::toString() const {
	string s1 = name;
	return string("\ntesting blockade: " + s1);
}

/*----------------------------------------------------------------------airlift class---------------------------------------------------------------------*/
Airlift::Airlift() {

}

Airlift::Airlift(int naw, Territory* st, Territory* tt) {
	numArmyUnit = naw;
	souTerritory = st;
	tarTerritory = tt;
}

Airlift::Airlift(Airlift& airlift) {
	numArmyUnit = airlift.numArmyUnit;
	souTerritory = &(*airlift.souTerritory);
	tarTerritory = &(*airlift.tarTerritory);
}

Airlift::~Airlift() {

}

bool Airlift::validate() {
	//if user has card "airlift" return true
	cout << "\nvalidate for airlift order";
	return true;
}

bool Airlift::execute() {
	cout << "\nexecute for airlift order\n";
	executed = true;
	return executed;
}

string Airlift::toString() const {
	string s1 = name;
	string s2 = to_string(numArmyUnit);
	return string("\ntesting advance: " + s1 + " " + s2);
}

/*----------------------------------------------------------------------negotiate class---------------------------------------------------------------------*/
Negotiate::Negotiate() {

}

Negotiate::Negotiate(Territory* tt) {
	tarTerritory = tt;
}

Negotiate::Negotiate(Negotiate& negotiate) {
	tarTerritory = &(*negotiate.tarTerritory);
}

Negotiate::~Negotiate() {

}

bool Negotiate::validate() {
	//if user has card "diplomacy" return true
	cout << "\nvalidate for negotiate order";
	return true;
}

bool Negotiate::execute() {
	cout << "\nvalidate for negotiate order\n";
	executed = true;
	return executed;
}

string Negotiate::toString() const {
	string s1 = name;
	return string("\ntesting negotiate: " + s1);
}
