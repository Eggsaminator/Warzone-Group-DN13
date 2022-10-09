#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Player.h"

/*----------------------------------------------------------------------order class---------------------------------------------------------------------*/



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

bool OrderList::move() {

}

bool OrderList::remove() {

}

void OrderList::addOrder(Orders* order) {
	orders.push_back(order);
}

/*----------------------------------------------------------------------deploy class---------------------------------------------------------------------*/
Deploy::Deploy(int naw, Territory* tt) {
	numArmyUnit = naw;
	tarTerritory = tt;
}

Deploy::Deploy(Deploy& deploy) {
	numArmyUnit = deploy.numArmyUnit;
	tarTerritory = &(*deploy.tarTerritory);
}

bool Deploy::validate() {
	cout << "\nvalidate for deploy order";
	return true;
}

void Deploy::execute() {
	cout << "\nexecute for deploy order\n";
}

/*----------------------------------------------------------------------advance class---------------------------------------------------------------------*/
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

bool Advance::validate() {
	cout << "\nvalidate for advance order";
	return true;
}

void Advance::execute() {
	cout << "\nexecute for advance order\n";
}

/*----------------------------------------------------------------------bomb class---------------------------------------------------------------------*/
Bomb::Bomb(Territory* tt) {
	tarTerritory = tt;
}

Bomb::Bomb(Bomb& bomb) {
	tarTerritory = &(*bomb.tarTerritory);
}

bool Bomb::validate() {
	//if user has card "bomb" return true
	cout << "\nvalidate for bomb order";
	return true;
}

void Bomb::execute() {
	cout << "\nexecute for bomb order\n";
}

/*----------------------------------------------------------------------blockade class---------------------------------------------------------------------*/
Blockade::Blockade(Territory* tt) {
	tarTerritory = tt;
}

Blockade::Blockade(Blockade& blockade) {
	tarTerritory = &(*blockade.tarTerritory);
}

bool Blockade::validate() {
	//if user has card "blockade" return true
	cout << "\nvalidate for blockade order";
	return true;
}

void Blockade::execute() {
	cout << "\nexecute for blockade order\n";
}

/*----------------------------------------------------------------------airlift class---------------------------------------------------------------------*/
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

bool Airlift::validate() {
	//if user has card "airlift" return true
	cout << "\nvalidate for airlift order";
	return true;
}

void Airlift::execute() {
	cout << "\nexecute for airlift order\n";
}

/*----------------------------------------------------------------------negotiate class---------------------------------------------------------------------*/
Negotiate::Negotiate(Territory* tt) {
	tarTerritory = tt;
}

Negotiate::Negotiate(Negotiate& negotiate) {
	tarTerritory = &(*negotiate.tarTerritory);
}

bool Negotiate::validate() {
	//if user has card "diplomacy" return true
	cout << "\nvalidate for negotiate order";
	return true;
}

void Negotiate::execute() {
	cout << "\nvalidate for negotiate order\n";
}
