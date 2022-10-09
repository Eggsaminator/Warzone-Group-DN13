#include <iostream>
#include "Orders.h"
#include "Player.h"
#include "Map.h"


//testOrdersList() method to be implemented
//main driver
int main() {
	cout << "hello world!";

	Player* sampleP = new Player();
	Territory* sampleTarget = new Territory();
	Territory* sampleSource = new Territory();


	Deploy* d = new Deploy();
	cout << d->toString();
	Advance* ad = new Advance();
	Bomb* bo = new Bomb();
	Blockade* bl = new Blockade();
	Airlift* ai = new Airlift();
	Negotiate* n = new Negotiate();

	vector<int> i = {11,21,31,41,51};
	cout << i.at(1);

	OrderList* tODep = new OrderList;
	tODep->addOrder(d);
	tODep->addOrder(ad);
	tODep->addOrder(bo);
	tODep->addOrder(bl);
	tODep->addOrder(ai);
	tODep->addOrder(n);
	cout << tODep->toString();
	//cout << tODep->orders.at(0)->toString();

}