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
	Orders* n = new Negotiate(sampleP, sampleP2);

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

void testOrderExecution() {
	//CREATE SIMPLE MAP
	Continent* continent = new Continent("CONTINENT", 0);
	Territory* t1 = new Territory("TERRITORY #1", continent);
	Territory* t2 = new Territory("TERRITORY #2", continent);
	Territory* t3 = new Territory("TERRITORY #3", continent);
	Territory* t4 = new Territory("TERRITORY #4", continent);
	Territory* t5 = new Territory("TERRITORY #5", continent);
	Territory* t6 = new Territory("TERRITORY #6", continent);
	Territory* t7 = new Territory("TERRITORY #7", continent);
	Territory* t8 = new Territory("TERRITORY #8", continent);
	Territory* t9 = new Territory("TERRITORY #9", continent);

	//CREATE DECK
	Deck d(15, false);
	Hand* hp1 = new Hand();
	
	//CREATE PLAYER
	Player* p1 = new Player("PLAYER_1"); //will have teritory 1,2,3
	Player* p2 = new Player("PLAYER_2"); //will have teritory 4,5,6
	Player* p3 = new Player("PLAYER_3"); //will have teritory 7,8,9

	OrderList* p1o = new OrderList(p1->getName());
	OrderList* p2o = new OrderList(p2->getName());
	OrderList* p3o = new OrderList(p3->getName());

	hp1->setPlayer(p1);

	//ASSIGN TERRITORY
	t1->setOwner(p1); //deploy - advance - aiflift
	t2->setOwner(p1); //blockade
	t3->setOwner(p1); //airlift
	t4->setOwner(p2); //advance
	t5->setOwner(p2); //advance
	t6->setOwner(p2); //advance
	t7->setOwner(p3); //advance
	t8->setOwner(p3); //bomb
	t9->setOwner(p3); //negotiate

	t1->addAdjacency(t5);
	t4->addAdjacency(t6);
	t7->addAdjacency(t4);

	//DEPLOY
	cout << "___________________________________________\n\n\tCHECKING FOR DEPLOY ORDER\n___________________________________________" << endl;
	//p1
	cout << p1o->toString() << "Owner: " << t1->getOwner()->getName() << " | Army count on territory #1: " << t1->getArmies() << endl;
	Orders* dp1 = new Deploy(p1, 10, t1);

	p1o->addOrder(dp1);

	//p1 - deploy
	dp1->execute();

	dp1->execute();

	cout << p1o->toString() << "Owner: " << t1->getOwner()->getName() << " | Army count on territory #1: " << t1->getArmies() << endl;

	//ADVANCE
	cout << "___________________________________________\n\n\tCHECKING FOR ADVANCE ORDER\n___________________________________________" << endl;
	t4->setArmies(5);
	t7->setArmies(15);

	//p1 - to ennemy territory with no units
	Orders* adp1 = new Advance(p1, 1, t1, t5);
	//p2 - to another ally territory
	Orders* adp2 = new Advance(p2, 2, t4, t6);
	//p3 - to ennemy territory with units
	Orders* adp3 = new Advance(p3, 1, t7, t4);

	p1o->addOrder(adp1);
	p2o->addOrder(adp2);
	p3o->addOrder(adp3);

	cout << "\n[PLAYER_1 ADVANCE TO PLAYER_2 TERRITORY WITH NOT ENNEMY UNIT]\nOwner: " << t1->getOwner()->getName() << " | Army in t1: " << t1->getArmies() << "\nOwner: " << t5->getOwner()->getName() << " | Army in t5: " << t5->getArmies() << endl;
	adp1->execute();
	cout << p1o->toString() << "Owner: " << t1->getOwner()->getName() << " | Army in t1: " << t1->getArmies() << "\nOwner: " << t5->getOwner()->getName() << " | Army in t5: " << t5->getArmies() << endl;

	cout << "\n[PLAYER_2 ADVANCE TO PLAYER_2 TERRITORY]\nOwner: " << t4->getOwner()->getName() << " | Army in t4: " << t4->getArmies() << "\nOwner: " << t6->getOwner()->getName() << " | Army in t6: " << t6->getArmies() << endl;
	adp2->execute();
	cout << p2o->toString() << "Owner: " << t4->getOwner()->getName() << " | Army in t4: " << t4->getArmies() << "\nOwner: " << t6->getOwner()->getName() << " | Army in t6: " << t6->getArmies() << endl;

	cout << "\n[PLAYER_3 ADVANCE TO PLAYER_2 TERRITORY WITH ENNEMY UNITS\nOwner: " << t7->getOwner()->getName() << " | Army in t7: " << t7->getArmies() << "\nOwner: " << t4->getOwner()->getName() << " | Army in t4: " << t4->getArmies() << endl;
	adp3->execute();
	cout << p3o->toString() << "Owner: " << t7->getOwner()->getName() << " | Army in t7: " << t7->getArmies() << "\nOwner: " << t4->getOwner()->getName() << " | Army in t4: " << t4->getArmies() << endl;


	//BOMB
	cout << "___________________________________________\n\n\tCHECKING FOR BOMB ORDER\n___________________________________________" << endl;
	t8->setArmies(8);
	t8->addAdjacency(t1);

	//p1 - to ennemy territory with no units
	Orders* bop1 = new Bomb(p1, t8);
	p1o->addOrder(bop1);

	cout << "\n[PLAYER_1 BOMB PLAYER_3 TERRITORY #8]\nOwner: " << t8->getOwner()->getName() << " | Army in t8: " << t8->getArmies() << endl;
	bop1->execute();
	cout << p3o->toString() << "Owner: " << t8->getOwner()->getName() << " | Army in t8: " << t8->getArmies() << endl;

	//BLOCKADE
	cout << "___________________________________________\n\n\tCHECKING FOR BLOCKADE ORDER\n___________________________________________" << endl;
	t2->setArmies(12);

	//p1 - to ennemy territory with no units
	Orders* blp1 = new Blockade(p1, t2);
	p1o->addOrder(blp1);

	cout << "\n[PLAYER_1 BLOCK TERRITORY #2]\nOwner: " << t2->getOwner()->getName() << " | Army in t8: " << t2->getArmies() << endl;
	blp1->execute();
	cout << p1o->toString() << "Owner: " << t2->getOwner()->getName() << " | Army in t2: " << t2->getArmies() << endl;


		//AIRLIFT
	cout << "___________________________________________\n\n\tCHECKING FOR AIRLIFT ORDER\n___________________________________________" << endl;
	t3->setArmies(16);
	//p1 - to ennemy territory with no units
	Orders* aip1 = new Airlift(p1, 10, t3, t1);
	p1o->addOrder(aip1);

	cout << "\n[PLAYER_1 AIRLIFT FROM TERRITORY #3 TO TERRITORY #1]\nOwner: " << t3->getOwner()->getName() << " | Army in t3: " << t3->getArmies() << "\nOwner: " << t1->getOwner()->getName() << " | Army in t1: " << t1->getArmies() << endl;
	aip1->execute();
	cout << p1o->toString() << "Owner: " << t3->getOwner()->getName() << " | Army in t3: " << t3->getArmies() << "\nOwner: " << t1->getOwner()->getName() << " | Army in t1: " << t1->getArmies() << endl;


	//NEGOTIATE
	cout << "___________________________________________\n\n\tCHECKING FOR NEGOTIATE ORDER\n___________________________________________" << endl;
	t1->addAdjacency(t9);
	Orders* np1 = new Negotiate(p1, p3);
	p1o->addOrder(np1); 
	
	cout << "\n[PLAYER_1 NEGOTIATE PLAYER_3]\nPlayer: " << p1->getName() << "\nPlayer: " << p3->getName() << endl;
	np1->execute();
	cout << p1o->toString();

	Orders* ad1Np1 = new Advance(p1, 2, t1, t9);
	p1o->addOrder(ad1Np1);

	ad1Np1->execute();


	Orders* boNp1 = new Bomb(p1, t9);
	p1o->addOrder(boNp1);

	boNp1->execute();

	Orders* ad2Np3 = new Advance(p3, 2, t8, t3);
	p3o->addOrder(ad2Np3);

	ad2Np3->execute();

}