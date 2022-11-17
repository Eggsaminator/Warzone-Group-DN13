#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "GameEngine.h"

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


string Orders::stringToLog() {
	return "Order Executed: " + this->toString() + "\n";
}

string Orders::getName() {
	return "";

}
/*----------------------------------------------------------------------orderlist class---------------------------------------------------------------------*/
OrderList::OrderList() {
	new LogObserver(this);
}

OrderList::OrderList(string user) {
	player = user;
	new LogObserver(this);
}

OrderList::OrderList(string user, vector<Orders*> o) {
	player = user;
	orders = o;
	new LogObserver(this);
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
	notify(this);
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

string OrderList::stringToLog(){
	return "Order Issued : " + orders.back()->getName() + "order, to the player " + player + "'s orders list" + "\n"; 
}

/*----------------------------------------------------------------------deploy class---------------------------------------------------------------------*/
Deploy::Deploy() {
	new LogObserver(this);
}

Deploy::Deploy(Player* p, int naw, Territory* tt) {
	player = p;
	numArmyUnit = naw;
	tarTerritory = tt;
	new LogObserver(this);
}

Deploy::Deploy(Deploy& deploy) {
	numArmyUnit = deploy.numArmyUnit;
	tarTerritory = &(*deploy.tarTerritory);
	new LogObserver(this);
}

Deploy::~Deploy() {
	player = nullptr;
	numArmyUnit = 0;
	tarTerritory = nullptr;
}

bool Deploy::validate() {
	//done except for designating which player's territory to look
	cout << "Validate for deploy order" << endl;
	//check if deploy has already been executed
	if (executed == false) {
		//check if target territory belongs to the player
		if (tarTerritory->getOwner() == player) {
			validated = true;
			cout << "\tTarget territory belongs to the player\n\tOrder is valid" << endl;
		}
		else {
			cout << "\tTarget territory does not belong to the player\n\tOrder is not valid" << endl;
		}
	}
	else {
		cout << "\tDeploy Order has already been executed\n\tDeploy order cannot be validated" << endl;
		validated = false;
	}
	return validated;
}

bool Deploy::execute() {
	cout << "\nExecute for deploy order" << endl;
	//check if validated it true
	if (validate() == true) {
		int i = tarTerritory->getArmies();
		//execution
		tarTerritory->addArmies(numArmyUnit);
		//end execution
		

		cout << "Deploy order has been executed" << endl;
		//show
		cout << "\n" << player->getName() << " deployed " << numArmyUnit << " units to " << tarTerritory->getName() << "\n"
			<< tarTerritory->getName() << "| Owner: " << player->getName() << " | Army count: " << i << " -> " << tarTerritory->getArmies() << endl;
    notify(this);
		executed = true;
	}
	else {
		cout << "Deploy order cannot be executed" << endl;
	}
	return executed;
}

ostream& operator << (ostream& os, const Deploy& d){
	if (d.executed == true) {
		return (os << "\nDisplaying order: " <<d.name << "| Army count: " << d.numArmyUnit << "| Target Location: " << d.tarTerritory->getName() << "| Order has already been executed");
	}
	return (os << "\nDisplaying order: " << d.name << "| Army count: " << d.numArmyUnit << "| Target Location: " << d.tarTerritory->getName());
}

string Deploy::toString() const{
	stringstream ss;
	ss << (*this);
	return ss.str();
}


string Deploy::getName() {
	return name;
}

/*----------------------------------------------------------------------advance class---------------------------------------------------------------------*/
Advance::Advance() {
	new LogObserver(this);
}

Advance::Advance(Player* p, int naw, Territory* st, Territory* tt) {
	player = p;
	numArmyUnit = naw;
	souTerritory = st;
	tarTerritory = tt;
	new LogObserver(this);
}

Advance::Advance(Advance& advance) {
	numArmyUnit = advance.numArmyUnit;
	souTerritory = &(*advance.souTerritory);
	tarTerritory = &(*advance.tarTerritory);
	new LogObserver(this);
}

Advance::~Advance() {
	player = nullptr;
	numArmyUnit = 0;
	souTerritory = nullptr;
	tarTerritory = nullptr;
}

bool Advance::validate() {
	cout << "Validate for advance order\n";
	bool ownSource = false, adjacent = false;

	//check if validated it true
	if (executed != true) {
		//check if source territory belongs to the player
		if (player->getTruce() == tarTerritory->getOwner()->getName() || tarTerritory->getOwner()->getTruce() == player->getName()) {
			cout << "\t" << player->getName() << " is in truce with " << tarTerritory->getOwner()->getName() << endl;
			
		}
		else {
			if (souTerritory->getOwner() == player) {
				ownSource = true;
				cout << "\tSource territory belongs to the player" << endl;
			}
			else {
				cout << "\tSource territory does not belong to the player" << endl;
			}
			//check if target territory is adjacent to the source territory
			for (int i = 0; i < souTerritory->getAdjacencyList().size(); i++) {
				if (souTerritory->getAdjacencyList().at(i) == tarTerritory) {
					adjacent = true;
					cout << "\tTarget territory is adjacent to the source territory" << endl;
				}
				else if (i+1 == souTerritory->getAdjacencyList().size()) {
					cout << "\tTarget territory is not adjacent to the source territory" << endl;
				}
			}
			//check if advance order is valid
			if (ownSource == true && adjacent == true) {
				validated = true;
				cout << "Advance order is valid" << endl;
			}
			else {
				cout << "Advance order is invalid" << endl;
			}
		}
	}
	else {
		validated = false;
		cout << "\tAdvance Order has already been executed\n\tAdvance order cannot be validated" << endl;
	}
	return validated;
}

bool Advance::execute() {
	cout << "\nExecute for advance order called\n";
	if (validate() == true) {
		//execution

		int is = souTerritory->getArmies(), ia = numArmyUnit, it = tarTerritory->getArmies();
		//if both territories belong to player (incorporated in other conditions)
		if (souTerritory->getOwner() == player && tarTerritory->getOwner() == player) {
			souTerritory->addArmies(-numArmyUnit);
			tarTerritory->addArmies(numArmyUnit);
			player->setConquered(true);
			//show
			cout << "\n" << player->getName() << " moved " << numArmyUnit << " units to " << tarTerritory->getName() << "\n"
				<< souTerritory->getName() << "| Owner: " << souTerritory->getOwner()->getName() << " | Army count: " << is << " -> " << souTerritory->getArmies() << "\n"
				<< tarTerritory->getName() << "| Owner: " << tarTerritory->getOwner()->getName() << " | Army count: " << it << " -> " << tarTerritory->getArmies() << endl;

		}
		//target territory belongs to an ennemy or is neutral
		if (tarTerritory->getOwner() != player) {
			//check if has enemy armies
			souTerritory->addArmies(-numArmyUnit);
			while (numArmyUnit > 0 && tarTerritory->getArmies() > 0) {
				//fight
				int s = numArmyUnit, t = tarTerritory->getArmies();
				for (int i = 0; i < s; i++) {
					//rand doesn't seem to generate random set every program execution
					int r = (rand()%10);
					if (r < 6 && tarTerritory->getArmies() > 0) {
						tarTerritory->setArmies(tarTerritory->getArmies() - 1);
					}
				}
				for (int i = 0; i < t; i++) {
					int r = rand() % 10;
					if (r < 7 && numArmyUnit > 0) {
						numArmyUnit--;
					}
				}
				cout << "_" << endl;
			}
			if (tarTerritory->getArmies() == 0) {
				tarTerritory->setOwner(player);
				tarTerritory->addArmies(numArmyUnit);
				player->setConquered(true);
				//show
				cout << "\n" << player->getName() << " conquered " << tarTerritory->getName() << ", lost " << ia-numArmyUnit << " units\n"
					<< souTerritory->getName() << "| Owner: " << souTerritory->getOwner()->getName() << " | Army count: " << is << " -> " << souTerritory->getArmies() << "\n"
					<< tarTerritory->getName() << "| Owner: " << tarTerritory->getOwner()->getName() << " | Army count: " << it << " -> " << tarTerritory->getArmies() << endl;
			}
			else {
				//show
				cout << "\n" << player->getName() << " could not conquer " << tarTerritory->getName() << ", lost " << ia - numArmyUnit << " units\n"
					<< souTerritory->getName() << "| Owner: " << souTerritory->getOwner()->getName() << " | Army count: " << is << " -> " << souTerritory->getArmies() << "\n"
					<< tarTerritory->getName() << "| Owner: " << tarTerritory->getOwner()->getName() << " | Army count: " << it << " -> " << tarTerritory->getArmies() << endl;
			}
		}
		//end execution
		notify(this);
		executed = true;
	}
	else {
		cout << "Advance order cannot be executed" << endl;
	}
	return executed;
}

ostream& operator << (ostream& os, const Advance& ad){
	if (ad.executed == true) {
		return (os << "\nDisplaying order: " << ad.name << "| Army count: " << ad.numArmyUnit << "| Source Location " << ad.souTerritory->getName() << "| Target Location: " << ad.tarTerritory->getName() << "| Order has already been executed");
	}
	return (os << "\nDisplaying order: " << ad.name << "| Army count: " << ad.numArmyUnit << "| Source Location " << ad.souTerritory->getName() << "| Target Location: " << ad.tarTerritory->getName());
}

string Advance::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

string Advance::getName() {
	return name;
}
/*----------------------------------------------------------------------bomb class---------------------------------------------------------------------*/
Bomb::Bomb() {
	new LogObserver(this);
}

Bomb::Bomb(Player* p, Territory* tt) {
	player = p;
	tarTerritory = tt;
	new LogObserver(this);
}

Bomb::Bomb(Bomb& bomb) {
	tarTerritory = &(*bomb.tarTerritory);
	new LogObserver(this);
}

Bomb::~Bomb() {
	player = nullptr;
	tarTerritory = nullptr;
}

bool Bomb::validate() {
	cout << "Validate for bomb order\n";
	bool target = false, adjacent = false;

	//check if bomb order has already been executed
	if (executed != true) {
		if (player->getTruce() == tarTerritory->getOwner()->getName() || tarTerritory->getOwner()->getTruce() == player->getName()) {
			cout << "\t" << player->getName() << " is in truce with " << tarTerritory->getOwner()->getName() << endl;
		}
		else {
			//check if target territory does not belong to the player
			if (tarTerritory->getOwner() != player) {
				target = true;
				cout << "\tTarget territory belongs to an opponent" << endl;
				
			}
			else {
				cout << "\tTarget territory belongs to the player" << endl;
			}
			//check if a territory adjacent to the target territory blelong to the owner of the order
			//this ensures that the target territory is adjacent to the player's territory
			for (int i = 0; i < tarTerritory->getAdjacencyList().size(); i++) {
				if ((tarTerritory->getAdjacencyList().at(i)->getOwner() == player) && adjacent == false) {
					adjacent = true;
					cout << "\tTarget territory is adjacent to a player's territory" << endl;
				}
			}
			if (adjacent == false) {
				cout << "\tTarget territory is not adjacent to the source territory" << endl;
			}
			//check if order bomb is valid
			if (target == true && adjacent == true) {
				validated = true;
				cout << "\tBomb order is valid" << endl;
			}
			else {
				cout << "\tBomb order is invalid" << endl;
			}
		}
		
	}
	else {
		validated = false;
		cout << "\tBomb Order has already been executed\n\tBomb order cannot be validated" << endl;
	}
	return validated;
}

bool Bomb::execute() {
	cout << "\nExecute for bomb order\n";
	if (validate() == true) {
		//execution
		int i = tarTerritory->getArmies();
		tarTerritory->setArmies(tarTerritory->getArmies()/2);
		//end execution
		cout << "\n" << player->getName() << " bombed " << tarTerritory->getName() << "\n"
			<< tarTerritory->getName() << "| Owner: " << tarTerritory->getOwner()->getName() << " | Army count: " << i << " -> " << tarTerritory->getArmies() << endl;

    notify(this);
		executed = true;
	}
	else {
		cout << "Bomb order cannot be executed" << endl;
	}
	return executed;
}

ostream& operator << (ostream& os, const Bomb& b){
	if (b.executed == true) {
		return (os << "\nDisplaying order: " << b.name << " | Target Location: " << b.tarTerritory->getName() << "| Order has already been executed");
	}
	return (os << "\nDisplaying order: " << b.name << " | Target Location: " << b.tarTerritory->getName());
}

string Bomb::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

string Bomb::getName() {
	return name;
}
/*----------------------------------------------------------------------blockade class---------------------------------------------------------------------*/
Blockade::Blockade() {
	new LogObserver(this);
}

Blockade::Blockade(Player* p, Territory* tt) {
	player = p;
	tarTerritory = tt;
	new LogObserver(this);
}

Blockade::Blockade(Blockade& blockade) {
	tarTerritory = &(*blockade.tarTerritory);
	new LogObserver(this);
}

Blockade::~Blockade() {
	player = nullptr;
	tarTerritory = nullptr;
}

bool Blockade::validate() {
	cout << "Validate for blockade order\n";
	//check if blockade order has already been executed
	if (executed == false) {
		//check if target territory belongs to the player
		if (tarTerritory->getOwner() == player) {
			validated = true;
			cout << "\tSource territory belongs to the player" << endl;
			cout << "\tBlockade order is valid" << endl;
		}
		else {
			cout << "\tSource territory does not belongs to the player" << endl;

			cout << "\tBlockade order is invalid" << endl;
		}
	}
	else {
		validated = false;
		cout << "\tBlockade Order has already been executed\n\tBlockade order cannot be validated" << endl;
	}
	return validated;
}

bool Blockade::execute() {
	cout << "\nExecute for blockade order called\n";
	if (validate() == true) {
		//execution
		int i = tarTerritory->getArmies();
		Player* n = new Player("NEUTRAL");
		
		//double army count
		tarTerritory->setArmies(tarTerritory->getArmies() * 2);

		//set owner to neutral
		tarTerritory->setOwner(n);
		//end execution
		notify(this);
		executed = true;


		cout << "\n" << player->getName() << " blocked " << tarTerritory->getName() << "\n"
			<< tarTerritory->getName() << "| Owner: " << tarTerritory->getOwner()->getName() << " | Army count: " << i << " -> " << tarTerritory->getArmies() << endl;
	}
	else {
		cout << "Blockade order cannot be executed" << endl;
	}
	return executed;
}

ostream& operator << (ostream& os, const Blockade& bl){
	if (bl.executed == true) {
		return (os << "\nDisplaying order: " << bl.name << " | Target Location: " << bl.tarTerritory->getName() << "| Order has already been executed");
	}
	return (os << "\nDisplaying order: " << bl.name << " | Target Location: " << bl.tarTerritory->getName());
}

string Blockade::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

string Blockade::getName() {
	return name;
}
/*----------------------------------------------------------------------airlift class---------------------------------------------------------------------*/
Airlift::Airlift() {
	new LogObserver(this);
}

Airlift::Airlift(Player* p, int naw, Territory* st, Territory* tt) {
	player = p;
	numArmyUnit = naw;
	souTerritory = st;
	tarTerritory = tt;
	new LogObserver(this);
}

Airlift::Airlift(Airlift& airlift) {
	numArmyUnit = airlift.numArmyUnit;
	souTerritory = &(*airlift.souTerritory);
	tarTerritory = &(*airlift.tarTerritory);
	new LogObserver(this);
}

Airlift::~Airlift() {
	player = nullptr;
	numArmyUnit = 0;
	souTerritory = nullptr;
	tarTerritory = nullptr;
}

bool Airlift::validate() {
	cout << "Validate for airlift order\n";
	//done except for specifying player
	bool source = false;
	bool target = false;

	//check if airlift order has already been executed
	if (executed != true) {
		//check if the source territory belongs to the player
		if (souTerritory->getOwner() == player) {
			source = true;
			cout << "\tSource territory belongs to the player" << endl;
		}
		else {
			cout << "\tSource territory does not belong to the player" << endl;
		}
		//check if the target territory belongs to the player
		if (tarTerritory->getOwner() == player) {
			target = true;
			cout << "\tTarget territory belongs to the player" << endl;
		}
		else {
			cout << "\tTarget territory does not belong to the player" << endl;
		}
		//check if the airlift order is valid
		if (source == true && target == true) {
			validated = true;
			cout << "\tAirlift order is valid" << endl;
		}
		else {
			cout << "\tAirlift order is invalid" << endl;
		}
	}
	else {
		validated = false;
		cout << "tAirlift Order has already been executed\tAirlift order cannot be validated" << endl;

	}
	return validated;
}

bool Airlift::execute() {
	cout << "\nExecute for airlift order\n";
	if (validate() == true) {
		int is = souTerritory->getArmies(), it = tarTerritory->getArmies();
		//execution
		souTerritory->addArmies(-numArmyUnit);
		tarTerritory->addArmies(numArmyUnit);
		//end execution
		notify(this);
		executed = true;
		cout << "\n" << player->getName() << " airlifted " << numArmyUnit << " from " << souTerritory->getName() << " to " << tarTerritory->getName() << "\n"
			<< souTerritory->getName() << "| Owner: " << souTerritory->getOwner()->getName() << " | Army count: " << is << " -> " << souTerritory->getArmies() << "\n"
			<< tarTerritory->getName() << "| Owner: " << tarTerritory->getOwner()->getName() << " | Army count: " << it << " -> " << tarTerritory->getArmies() << endl;
	}
	else {
		cout << "Airlift order cannot be executed" << endl;
	}
	return executed;
}

ostream& operator << (ostream& os, const Airlift& ai) {
	if (ai.executed == true) {
		return (os << "\nDisplaying order: " << ai.name << " | Army count: " << ai.numArmyUnit << "| Source Location " << ai.souTerritory->getName() << "| Target Location: " << ai.tarTerritory->getName() << "| order has already been executed");
	}
	return (os << "\nDisplaying order: " << ai.name << " | Army count: " << ai.numArmyUnit << "| Source Location " << ai.souTerritory->getName() << "| Target Location: " << ai.tarTerritory->getName());
}

string Airlift::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

string Airlift::getName() {
	return name;
}
/*----------------------------------------------------------------------negotiate class---------------------------------------------------------------------*/
Negotiate::Negotiate() {
	new LogObserver(this);
}

Negotiate::Negotiate(Player* p, Player* tp) {
	player = p;
	tarPlayer = tp;
	new LogObserver(this);
	
}

Negotiate::Negotiate(Negotiate& negotiate) {
	tarPlayer = &(*negotiate.tarPlayer);
	new LogObserver(this);
}

Negotiate::~Negotiate() {
	player = nullptr;
	tarPlayer = nullptr;
}

bool Negotiate::validate() {
	cout << "validate for negotiate order\n";

	//check if negotiate order has already been executed
	if (executed != true) {
		//check if target territory does not belong to the player
		if (tarPlayer->getName() != player->getName()) {
			validated = true;
			cout << "\tSource territory does not belong to the player" << endl;
			cout << "\tNegotiate order is valid" << endl;
		}
		else {
			cout << "\tSource territory belongs to the player" << endl;
			cout << "\tNegotiate order is invalid" << endl;

		}
	}
	else {
		validated = false;
		cout << "\tNegotiate Order has already been executed\n\tNegotiate order cannot be validated" << endl;

	}
	return validated;
}

bool Negotiate::execute() {
	cout << "\nExecute for negotiate order called\n";
	if (validate() == true) {
		//execution
		player->setTruce(tarPlayer);
		//end execution
		notify(this);
		executed = true;
		cout << "\n" << player->getName() << " negotiated with " << tarPlayer->getName() << "\n"
			<< "Player " << player->getName() << " and player " << tarPlayer->getName() << " can no longer attack each other" << endl;
	}
	else {
		cout << "Negotiate order cannot be executed" << endl;
	}
	return executed;
}

ostream& operator << (ostream& os, const Negotiate& n) {
	if (n.executed == true) {
		return (os << "\nDisplaying order: " << n.name << " | Target Player: " << n.tarPlayer->getName() << "| Order has already been executed");
	}
	return (os << "\nDisplaying order: " << n.name << " | Target Player: " << n.tarPlayer->getName());
}

string Negotiate::toString() const {
	stringstream ss;
	ss << (*this);
	return ss.str();
}

string Negotiate::getName() {
	return name;
}