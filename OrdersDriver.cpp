#include <iostream>
#include "Orders.h"
#include "Player.h"
#include "Map.h"

void testOrdersList() {
	vector<string> mapList;
	// Map Canada.map is valid
	mapList.push_back("Canada.map");
	Player* sampleP = new Player("player");
	Player* sampleP2 = new Player("not player");
	Continent* continent = new Continent("test",0);
	Territory* sampleTarget = new Territory("territory #1", continent);
	Territory* sampleTarget1 = new Territory("territory #3", continent);
	Territory* sampleSource = new Territory("territory #2", continent);
	Orders* d = new Deploy(sampleP, 1000, sampleTarget);
	Orders* ad = new Advance(sampleP, 2000, sampleSource, sampleTarget);
	Orders* bo = new Bomb(sampleP, sampleTarget);
	Orders* bl = new Blockade(sampleP, sampleTarget);
	Orders* ai = new Airlift(sampleP, 1000, sampleSource, sampleTarget);
	Orders* n = new Negotiate(sampleP, sampleTarget);

	//creating list
	OrderList* tODep = new OrderList(sampleP->getName());
	tODep->addOrder(d);
	tODep->addOrder(ad);
	tODep->addOrder(bo);
	tODep->addOrder(bl);
	tODep->addOrder(ai);
	tODep->addOrder(n);

	//show current list
	cout << tODep->toString();

	sampleSource->setOwner(sampleP);
	sampleTarget->setOwner(sampleP2);
	//test valid method of subclasses
	d->validate();
	ad->validate();
	bo->validate();
	bl->validate();
	ai->validate();
	n->validate();

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

	tODep->~OrderList();
}

