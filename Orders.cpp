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
	player = "user";
}

OrderList::OrderList(string user) {
	player = user;
}

OrderList::OrderList(string user, vector<Orders*> o) {
	player = user;
	orders = o;
}

OrderList::OrderList(OrderList& order) {
	player = order.player;
	orders = order.orders;
}

OrderList::~OrderList() {
	player = "";
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
		return (os << "\nDisplaying order list for player " << o.player << "\n----" << str << "\n----\n");
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

Deploy::Deploy(string p, int naw, Territory* tt) {
	player = p;
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
	//done except for designating which player's territory to look
	cout << "\nvalidate for deploy order\n";
	cout << tarTerritory->getOwner() << "|" << player << endl;
	//check if deploy has already been executed
	if (executed != true) {
		//check if target territory belongs to the player
		if (tarTerritory->getOwner() == player) {
			validated = true;
			cout << "target territory belongs to the player" << endl;
		}
	}
	return validated;
}

bool Deploy::execute() {
	cout << "\nexecute for deploy order\n";
	//check if validated it true
	if (validated == true) {
		//execution
		tarTerritory->addArmies(numArmyUnit);
		//end execution
		executed = true;
	}
	return executed;
}

ostream& operator << (ostream& os, const Deploy& d){
	if (d.executed == true) {
		return (os << "\nDisplaying order: " <<d.name << " Army count: " << d.numArmyUnit << " Target Location: " << d.tarTerritory->getName() << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << d.name << " Army count: " << d.numArmyUnit << " Target Location: " << d.tarTerritory->getName());
}

string Deploy::toString() const{
	stringstream ss;
	ss << (*this);
	return ss.str();
}

/*----------------------------------------------------------------------advance class---------------------------------------------------------------------*/
Advance::Advance() {

}

Advance::Advance(string p, int naw, Territory* st, Territory* tt) {
	player = p;
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
	bool ownSource = false, adjacent = false;

	//check if validated it true
	if (validated != true) {
		//check if source territory belongs to the player
		if (souTerritory->getOwner() == player) {
			ownSource = true;
			cout << "source territory belongs to the player" << endl;
		}
		//check if target territory is adjacent to the source territory
		for (int i = 0; i < souTerritory->getAdjacencyList().size(); i++) {
			if (souTerritory->getAdjacencyList().at(i) == tarTerritory) {
				adjacent = true;
				cout << "target territory is adjacent to the source territory" << endl;
			}
		}
		//check if advance order is valid
		if (ownSource == true && adjacent == true) {
			validated = true;
			cout << "advance order is valid" << endl;
		}
	}
	return validated;
}

bool Advance::execute() {
	cout << "\nexecute for advance order\n";
	Player* testPlayer = new Player("player");
	if (validated == true) {
		//execution
		//if both ter belong to player
		if (souTerritory->getOwner() == player && tarTerritory->getOwner() == player) {
			souTerritory->addArmies(-numArmyUnit);
			tarTerritory->addArmies(numArmyUnit);
		}

		//take over
		if (tarTerritory->getArmies() == 0) {
			tarTerritory->setOwner(testPlayer);
		}
		//end execution
		executed = true;
	}
	return executed;
}

ostream& operator << (ostream& os, const Advance& ad){
	if (ad.executed == true) {
		return (os << "\nDisplaying order: " << ad.name << " Army count: " << ad.numArmyUnit << " Source Location " << ad.souTerritory->getName() << " Target Location: " << ad.tarTerritory->getName() << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << ad.name << " Army count: " << ad.numArmyUnit << " Source Location " << ad.souTerritory->getName() << " Target Location: " << ad.tarTerritory->getName());
}

string Advance::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

/*----------------------------------------------------------------------bomb class---------------------------------------------------------------------*/
Bomb::Bomb() {

}

Bomb::Bomb(string p, Territory* tt) {
	player = p;
	tarTerritory = tt;
}

Bomb::Bomb(Bomb& bomb) {
	tarTerritory = &(*bomb.tarTerritory);
}

Bomb::~Bomb() {
	tarTerritory = nullptr;
}

bool Bomb::validate() {
	cout << "\nvalidate for bomb order\n";
	bool target = false, adjacent = false;

	//check if bomb order has already been executed
	if (executed != true) {
		//check if target territory does not belong to the player
		if (tarTerritory->getOwner() != player) {
			target = true;
			cout << "target territory belongs to an opponent" << endl;
		}
		//check if a territory adjacent to the target territory blelong to the owner of the order
		//this ensures that the target territory is adjacent to the player's territory
		for (int i = 0; i < tarTerritory->getAdjacencyList().size(); i++) {
			if (tarTerritory->getAdjacencyList().at(i)->getOwner() == player) {
				adjacent = true;
				cout << "target territory is adjacent to a player's territory" << endl;
			}
		}
		//check if order bomb is valid
		if (target == true && adjacent == true) {
			validated = true;
			cout << "bomb order is valid" << endl;
		}
	}
	return validated;
}

bool Bomb::execute() {
	cout << "\nexecute for bomb order\n";
	if (validated == true) {
		//execution
		tarTerritory->setArmies(2);
		//end execution
		executed = true;
	}
	return executed;
}

ostream& operator << (ostream& os, const Bomb& b){
	if (b.executed == true) {
		return (os << "\nDisplaying order: " << b.name << " Target Location: " << b.tarTerritory->getName() << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << b.name << " Target Location: " << b.tarTerritory->getName());
}

string Bomb::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

/*----------------------------------------------------------------------blockade class---------------------------------------------------------------------*/
Blockade::Blockade() {

}

Blockade::Blockade(string p, Territory* tt) {
	player = p;
	tarTerritory = tt;
}

Blockade::Blockade(Blockade& blockade) {
	tarTerritory = &(*blockade.tarTerritory);
}

Blockade::~Blockade() {
	tarTerritory = nullptr;
}

bool Blockade::validate() {
	cout << "\nvalidate for blockade order\n";
	//check if blockade order has already been executed
	if (executed != true) {
		//check if target territory belongs to the player
		if (tarTerritory->getOwner() == player) {
			validated = true;
		}
	}
	return validated;
}

bool Blockade::execute() {
	cout << "\nexecute for blockade order\n";
	if (validated == true) {
		//execution

		//end execution
		executed = true;
	}
	return executed;
}

ostream& operator << (ostream& os, const Blockade& bl){
	if (bl.executed == true) {
		return (os << "\nDisplaying order: " << bl.name << " Target Location: " << bl.tarTerritory->getName() << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << bl.name << " Target Location: " << bl.tarTerritory->getName());
}

string Blockade::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

/*----------------------------------------------------------------------airlift class---------------------------------------------------------------------*/
Airlift::Airlift() {

}

Airlift::Airlift(string p, int naw, Territory* st, Territory* tt) {
	player = p;
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
	cout << "\nvalidate for airlift order\n";
	//done except for specifying player
	bool source = false;
	bool target = false;

	//check if airlift order has already been executed
	if (executed != true) {
		//check if the source territory belongs to the player
		if (souTerritory->getOwner() == player) {
			source = true;
			cout << "source territory belongs to the player" << endl;
		}
		//check if the target territory belongs to the player
		if (tarTerritory->getOwner() == player) {
			target = true;
			cout << "target territory belongs to the player" << endl;
		}
		//check if the airlift order is valid
		if (source == true && target == true) {
			validated = true;
			cout << "airlift order is valid" << endl;
		}
	}
	return validated;
}

bool Airlift::execute() {
	cout << "\nexecute for airlift order\n";
	if (validated == true) {
		//execution
		souTerritory->addArmies(-numArmyUnit);
		tarTerritory->addArmies(numArmyUnit);
		//end execution
		executed = true;
	}
	return executed;
}

ostream& operator << (ostream& os, const Airlift& ai) {
	if (ai.executed == true) {
		return (os << "\nDisplaying order: " << ai.name << " Army count: " << ai.numArmyUnit << " Source Location " << ai.souTerritory->getName() << " Target Location: " << ai.tarTerritory->getName() << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << ai.name << " Army count: " << ai.numArmyUnit << " Source Location " << ai.souTerritory->getName() << " Target Location: " << ai.tarTerritory->getName());
}

string Airlift::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

/*----------------------------------------------------------------------negotiate class---------------------------------------------------------------------*/
Negotiate::Negotiate() {
}

Negotiate::Negotiate(string p, Territory* tt) {
	player = p;
	tarTerritory = tt;
}

Negotiate::Negotiate(Negotiate& negotiate) {
	tarTerritory = &(*negotiate.tarTerritory);
}

Negotiate::~Negotiate() {
	tarTerritory = nullptr;
}

bool Negotiate::validate() {
	cout << "\nvalidate for negotiate order\n";

	//check if negotiate order has already been executed
	if (executed != true) {
		//check if target territory does not belong to the player
		if (tarTerritory->getOwner() != player) {
			validated = true;
		}
	}
	return validated;
}

bool Negotiate::execute() {
	cout << "\nexecute for negotiate order\n";
	if (validated == true) {
		//execution

		//end execution
		executed = true;
	}
	return executed;
}

ostream& operator << (ostream& os, const Negotiate& n) {
	if (n.executed == true) {
		return (os << "\nDisplaying order: " << n.name << " Target Location: " << n.tarTerritory->getName() << " order has already been executed");
	}
	return (os << "\nDisplaying order: " << n.name << " Target Location: " << n.tarTerritory->getName());
}

string Negotiate::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}
