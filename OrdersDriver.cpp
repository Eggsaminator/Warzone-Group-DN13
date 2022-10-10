#include <iostream>
#include "Orders.h"
#include "Player.h"
#include "Map.h"

void testOrdersList() {
	Player* sampleP = new Player("thomas");
	Continent* continent = new Continent("test",0);
	Territory* sampleTarget = new Territory("territory #1", continent);
	Territory* sampleSource = new Territory("territory #2", continent);
	Orders* d = new Deploy(1000, sampleTarget);
	Orders* ad = new Advance(2000, sampleSource, sampleTarget);
	Orders* bo = new Bomb(sampleTarget);
	Orders* bl = new Blockade(sampleTarget);
	Orders* ai = new Airlift(1000, sampleSource, sampleTarget);
	Orders* n = new Negotiate(sampleTarget);

	//creating list
	OrderList* tODep = new OrderList("welp");
	tODep->addOrder(d);
	tODep->addOrder(ad);
	tODep->addOrder(bo);
	tODep->addOrder(bl);
	tODep->addOrder(ai);
	tODep->addOrder(n);

	//show current list
	cout << "\n----\nDisplaying order list for player " << tODep->toString();

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

