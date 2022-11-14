#include <iostream>
#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include "GameEngine.h"

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

	cout << "__________________________________________\n\n\tTesting Order Execution\n__________________________________________" << endl;
	Engine orderEngine = Engine();

	//CREATE SIMPLE MAP
	Continent* continent = new Continent("CONTINENT", 0);
	Territory* t1 = new Territory("TERRITORY #1", continent); //deploy called
	Territory* t2 = new Territory("TERRITORY #2", continent); //no unit
	Territory* t3 = new Territory("TERRITORY #3", continent); //no unit
	Territory* t4 = new Territory("TERRITORY #4", continent); //unit
	Territory* t5 = new Territory("TERRITORY #5", continent);
	Territory* t6 = new Territory("TERRITORY #6", continent);
	t4->addArmies(10);

	//CREATE DECK
	Deck d(15, false);
	Hand* hp1 = new Hand();
	
	//CREATE PLAYER
	vector<Player*> players;
	Player* p1 = new Player("PLAYER_1"); //will have teritory 1,2,3
	Player* p2 = new Player("PLAYER_2"); //will have teritory 4,5,6
	Player* p3 = new Player("PLAYER_3"); //will have teritory 7,8,9
	players.push_back(p1);
	players.push_back(p2);
	players.push_back(p3);

	hp1->setPlayer(p1);

	//ASSIGN TERRITORY
	t1->setOwner(p1); 
	t2->setOwner(p1); 
	t3->setOwner(p2); 
	t4->setOwner(p2); 
	t5->setOwner(p3); 
	t6->setOwner(p3); 

	//ADD ADJACENCY
	//1 -> 2 & 3 & 4 & 5
	t1->addAdjacency(t2);
	t1->addAdjacency(t3);
	t1->addAdjacency(t5);
	//2 -> 1 & 4 & 5
	t2->addAdjacency(t5);
	//3 -> 1 & 4
	//4 -> 1 & 2 & 3 & 5 & 6
	t4->addAdjacency(t1);
	t4->addAdjacency(t2);
	t4->addAdjacency(t3);
	t4->addAdjacency(t5);
	t4->addAdjacency(t6);
	//5 -> 1 & 2 & 4
	//6 -> 4

	Map gameMap;
	gameMap.addContinent(continent);
		
	orderEngine.setMyMap(&gameMap);
	orderEngine.setMyPlayers(players);
	
	//DEPLOY
	//PLAYER_1 - DEPLOY ON OWN TERRITORY
	Orders* d1 = new Deploy(p1, 50, t1);
	//PLAYER_1 - DEPLOY ON WRONG TERRITORY
	Orders* d2 = new Deploy(p1, 20, t3);

	//ADVANCE
	//PLAYER_1 - ADVANCE TO ALLY TERRITORY
	Orders* ad1 = new Advance(p1, 5, t1, t2);
	//PLAYER_1 - ADVANCE TO ENNEMY TERRITORY WITH NO UNITS
	Orders* ad2 = new Advance(p1, 1, t1, t3);
	//PLAYER_1 - ADVANCE TO ENNEMY TERRITORY WITH UNITS
	Orders* ad3 = new Advance(p1, 3, t1, t4);
	//PLAYER_1- WRONG ADVANCE (ENNEMY TO X)
	Orders* ad4 = new Advance(p1, 1, t3, t1);
	
	//BOMB
	//PLAYER_1 - BOMB ENNEMY TERRITORY
	Orders* bo1 = new Bomb(p1, t4);
	//PLAYER_1 - BOMB NON-ADJACENT ENNEMY TERRITORY
	Orders* bo2 = new Bomb(p1, t6);
	//PLAYER_1 - BOMB OWN TERRITORY
	Orders* bo3 = new Bomb(p1, t1);

	//BLOACKADE
	//PLAYER_1 - BLOCKADE OWN TERRITORY
	Orders* bl1 = new Blockade(p1, t2);
	//PLAYER_1 - BLOCKADE ENNEMY TERRITORY
	Orders* bl2 = new Blockade(p1, t6);

	//AIRLIFT
	//- AIRLIFT ON OWN TERRITORIES
	Orders* ai1 = new Airlift(p1, 10, t1, t2);
	//- AIRLIFT ON ENNEMY TERRITORY
	Orders* ai2 = new Airlift(p1, 10, t1, t3);

	//NEGOTIATE 
	//p1 - NEGOTIATE TO ENNEMY
	Orders* n1 = new Negotiate(p1, p3);
	//p1 - NEGOTIATE TO SELF
	Orders* n2 = new Negotiate(p1, p1);

	//actions demonstrating temporary ceasefire between players
	//PLAYER_1 advancing to PLAYER_3's territory
	Orders* nad = new Advance(p1, 5, t1, t5);
	//PLAYER_1 bombing PLAYER_3's territory
	Orders* nbo1 = new Bomb(p1, t5);
	//PLAYER_3 advancing to PLAYER_1's territory
	Orders* nad1 = new Advance(p3, 2, t5, t1);

	players.at(0)->getOrdersList()->addOrder(d1);
	players.at(0)->getOrdersList()->addOrder(d2);

	players.at(0)->getOrdersList()->addOrder(ad1);
	players.at(0)->getOrdersList()->addOrder(ad2);
	players.at(0)->getOrdersList()->addOrder(ad3);
	players.at(0)->getOrdersList()->addOrder(ad4);

	players.at(0)->getOrdersList()->addOrder(bo1);
	players.at(0)->getOrdersList()->addOrder(bo2);
	players.at(0)->getOrdersList()->addOrder(bo3);

	players.at(0)->getOrdersList()->addOrder(bl1);
	players.at(0)->getOrdersList()->addOrder(bl2);

	players.at(0)->getOrdersList()->addOrder(ai1);
	players.at(0)->getOrdersList()->addOrder(ai2);

	players.at(0)->getOrdersList()->addOrder(n1);
	players.at(0)->getOrdersList()->addOrder(n2);

	players.at(0)->getOrdersList()->addOrder(nad);
	players.at(0)->getOrdersList()->addOrder(nbo1);
	players.at(0)->getOrdersList()->addOrder(nad1);

	orderEngine.executeOrdersPhase();
	






	//to show execute works fine along with validate
	//1. hardcode basic setup
	//2. add them to game engine
	//3. hardcode orders and put them into appropriate orderlist

}