#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Player.h"

/*----------------------------------------------------------------------order class---------------------------------------------------------------------*/
ostream& operator << (ostream& os, const Orders& order) {
	return (os << "\norder class called");
}

string Orders::toString() const{
	stringstream ss;
	ss << (*this);
	return ss.str();
}

bool Orders::validate() {
	cout << "\nOrder class of validate()\n";
	return false;
}

bool Orders::execute() {
	cout << "\nOrder class of Execute()\n";
	return false;
}

/*----------------------------------------------------------------------orderlist class---------------------------------------------------------------------*/
OrderList::OrderList() {
	player = "";

}

OrderList::OrderList(string user) {
	player = user;
}

OrderList::OrderList(string user, vector<Orders*> o) {
	player = user;
	orders = o;
}

OrderList::OrderList(OrderList& order) {
	curUser = order.curUser;
	orders = order.orders;
}

OrderList::~OrderList() {
	curUser = nullptr;
	for (size_t i = 0; i < orders.size(); i++) {
		delete orders.at(i);
	}
	orders.clear();
}

void OrderList::move(int i, int j) {
	if (i < 0 || i >= orders.size() || j < 0 || j >= orders.size()) {
		cout << "\nIndexes specified not in range of vector size\n";
	}
	else {
		if (i > j) {
			rotate(orders.rend() - i - 1, orders.rend() - i, orders.rend() - j);
		}
		else {
			rotate(orders.begin() + i, orders.begin() + 1, orders.begin() + j + 1);
		}
		cout << "\nOrder position moved\n";
	}
}

void OrderList::remove(int i) {
	if (i < 0 || i >= orders.size()) {
		cout << "\nSpecified location is outside the range\n";
	}else {
		orders.erase(orders.begin() + i);
		cout << "\nOrder removed\n";
	}
}

void OrderList::addOrder(Orders* order) {
	this->orders.push_back(order);
}

ostream& operator << (ostream& os, const OrderList& o) {
	string str;

		for (size_t i = 0; i < o.orders.size(); i++) {
			str = str + o.orders.at(i)->toString();
		}
		return (os << o.player << str);
}

string OrderList::toString() const{
	//calls toString() method in Order class for the order data
	stringstream ss;
	ss << (*this);
	return ss.str();
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
	numArmyUnit = 0;
	tarTerritory = nullptr;
}

bool Deploy::validate() {
	cout << "\nvalidate for deploy order\n";
	return true;
}

bool Deploy::execute() {
	cout << "\nexecute for deploy order\n";
	executed = true;
	return executed;
}

ostream& operator << (ostream& os, const Deploy& d){
	if (d.executed == true) {
		return (os << "\nDisplaying order: " <<d.name << " Army count: " << d.numArmyUnit << " Target Location: " << d.tarTerritory << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << d.name << " Army count: " << d.numArmyUnit << " Target Location: " << d.tarTerritory);
}

string Deploy::toString() const{
	stringstream ss;
	ss << (*this);
	return ss.str();
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
	numArmyUnit = 0;
	souTerritory = nullptr;
	tarTerritory = nullptr;
}

bool Advance::validate() {
	cout << "\nvalidate for advance order\n";
	return true;
}

bool Advance::execute() {
	cout << "\nexecute for advance order\n";
	executed = true;
	return executed;
}

ostream& operator << (ostream& os, const Advance& ad){
	if (ad.executed == true) {
		return (os << "\nDisplaying order: " << ad.name << " Army count: " << ad.numArmyUnit << " Source Location " << ad.souTerritory << " Target Location: " << ad.tarTerritory << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << ad.name << " Army count: " << ad.numArmyUnit << " Source Location " << ad.souTerritory << " Target Location: " << ad.tarTerritory);
}

string Advance::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
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
	tarTerritory = nullptr;
}

bool Bomb::validate() {
	//if user has card "bomb" return true
	cout << "\nvalidate for bomb order\n";
	return true;
}

bool Bomb::execute() {
	cout << "\nexecute for bomb order\n";
	executed = true;
	return executed;
}

ostream& operator << (ostream& os, const Bomb& b){
	if (b.executed == true) {
		return (os << "\nDisplaying order: " << b.name << " Target Location: " << b.tarTerritory << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << b.name << " Target Location: " << b.tarTerritory);
}

string Bomb::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
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
	tarTerritory = nullptr;
}

bool Blockade::validate() {
	//if user has card "blockade" return true
	cout << "\nvalidate for blockade order\n";
	return true;
}

bool Blockade::execute() {
	cout << "\nexecute for blockade order\n";
	executed = true;
	return executed;
}

ostream& operator << (ostream& os, const Blockade& bl){
	if (bl.executed == true) {
		return (os << "\nDisplaying order: " << bl.name << " Target Location: " << bl.tarTerritory << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << bl.name << " Target Location: " << bl.tarTerritory);
}

string Blockade::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
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
	numArmyUnit = 0;
	souTerritory = nullptr;
	tarTerritory = nullptr;
}

bool Airlift::validate() {
	//if user has card "airlift" return true
	cout << "\nvalidate for airlift order\n";
	return true;
}

bool Airlift::execute() {
	cout << "\nexecute for airlift order\n";
	executed = true;
	return executed;
}

ostream& operator << (ostream& os, const Airlift& ai) {
	if (ai.executed == true) {
		return (os << "\nDisplaying order: " << ai.name << " Army count: " << ai.numArmyUnit << " Source Location " << ai.souTerritory << " Target Location: " << ai.tarTerritory << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << ai.name << " Army count: " << ai.numArmyUnit << " Source Location " << ai.souTerritory << " Target Location: " << ai.tarTerritory);
}

string Airlift::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
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
	tarTerritory = nullptr;
}

bool Negotiate::validate() {
	//if user has card "diplomacy" return true
	cout << "\nvalidate for negotiate order\n";
	return true;
}

bool Negotiate::execute() {
	cout << "\nexecute for negotiate order\n";
	executed = true;
	return executed;
}

ostream& operator << (ostream& os, const Negotiate& n) {
	if (n.executed == true) {
		return (os << "\nDisplaying order: " << n.name << " Target Location: " << n.tarTerritory << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << n.name << " Target Location: " << n.tarTerritory);
}

string Negotiate::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}
