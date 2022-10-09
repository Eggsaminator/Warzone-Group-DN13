#include <iostream>
#include <algorithm>

#include <cstdlib>
#include <utility>
#include "Orders.h"
#include "Map.h"
#include "Player.h"

/*----------------------------------------------------------------------order class---------------------------------------------------------------------*/
Orders::Orders() {

}

Orders::~Orders() {

}

string Orders::toString() {
	return string("testing order");
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
	//todo
}

void OrderList::remove(int i) {
	//todo
}

void OrderList::addOrder(Orders* order) {
	this->orders.push_back(order);
}

string OrderList::toString() const{
	//calls toString() method in Order class for the order data
	string str;
	for (size_t i = 0; i < orders.size(); i++) {
		str = str + "\n" + orders.at(i)->toString(); //doesnt call ???
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

void Deploy::execute() {
	cout << "\nexecute for deploy order\n";
}

string Deploy::toString() const{
	return string("testing");
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

void Advance::execute() {
	cout << "\nexecute for advance order\n";
}

string Advance::toString() const {
	return string("testing");
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

void Bomb::execute() {
	cout << "\nexecute for bomb order\n";
}

string Bomb::toString() const {
	return string("testing");
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

void Blockade::execute() {
	cout << "\nexecute for blockade order\n";
}

string Blockade::toString() const {
	return string("testing");
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

void Airlift::execute() {
	cout << "\nexecute for airlift order\n";
}

string Airlift::toString() const {
	return string("testing");
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

void Negotiate::execute() {
	cout << "\nvalidate for negotiate order\n";
}

string Negotiate::toString() const {
	return string("testing");
}
