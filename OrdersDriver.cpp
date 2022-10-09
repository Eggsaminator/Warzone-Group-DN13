#include <iostream>
#include "Orders.h"
#include "Player.h"
#include "Map.h"

void testOrdersList() {
	Player* sampleP = new Player("thomas");
	Territory* sampleTarget = new Territory();
	Territory* sampleSource = new Territory();
	Orders* d = new Deploy(1000, nullptr);
	Orders* ad = new Advance(2000, nullptr, nullptr);
	Orders* bo = new Bomb(nullptr);
	Orders* bl = new Blockade(nullptr);
	Orders* ai = new Airlift(1000, nullptr, nullptr);
	Orders* n = new Negotiate(nullptr);

	//creating list
	OrderList* tODep = new OrderList;
	tODep->addOrder(d);
	tODep->addOrder(ad);
	tODep->addOrder(bo);
	tODep->addOrder(bl);
	tODep->addOrder(ai);
	tODep->addOrder(n);

	//show current list
	cout << tODep->toString();

	//test valid method of subclasses
	d->validate();
	bo->validate();
	ai->validate();

	//test execute method of subclasses
	ad->execute();
	bl->execute();
	n->execute();

	//list with executed orders
	cout << tODep->toString();

	//move method of orderlist
	tODep->move(0, 4);
	tODep->move(1, 6);
	tODep->move(3, 2);

	//show modified list
	cout << tODep->toString();

	//remove method of orderlist
	tODep->remove(5);
	tODep->remove(9);
	tODep->remove(0);

	//show updated list
	cout << tODep->toString();
}


int main() {
	cout << "testing order tasks\n----\n";
	testOrdersList();
}