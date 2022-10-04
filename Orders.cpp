#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Player.h"

/*Methods
* move()
* remove()		
* validate()	
* execute()		
*/

/*Create OrdersList class
* this class will have the move() and remove()
* 
*/

/*Other classes
* lists*: deploy, advance, bomb, blockade, airlift, negotiate
* lists* will be classes
*	Each of the classes should at least have validate() and execute()
* variables needed currently: current user (curUser)
*/

/*----------------------------------------------------------------------order class---------------------------------------------------------------------*/
Orders::Orders() {}

/*----------------------------------------------------------------------orderlist class---------------------------------------------------------------------*/
/*OrderList::OrderList(vector<Orders>& o) {
	orders = o;
}*/

/*----------------------------------------------------------------------deploy class---------------------------------------------------------------------*/
Deploy::Deploy(Player* p, int naw, Territory* tt) {
	curUser = p;
	numArmyUnit = naw;
	tarTerritory = tt;
}
//copy constructor
Deploy::Deploy(Deploy& deploy) {
	curUser = &(*deploy.curUser);
	numArmyUnit = deploy.numArmyUnit;
	tarTerritory = &(*deploy.tarTerritory);
}
//destructor

//validate
bool Deploy::validate() {
	cout << "\nvalidate for deploy order";
	return true;
}

//execute
void Deploy::execute() {
	cout << "\nexecute for deploy order";
}


/*----------------------------------------------------------------------advance class---------------------------------------------------------------------*/
Advance::Advance(Player* p, int naw, Territory* st, Territory* tt) {
	curUser = p;
	numArmyUnit = naw;
	souTerritory = st;
	tarTerritory = tt;
}
//copy conctructor
Advance::Advance(Advance& advance) {
	curUser = &(*advance.curUser);
	numArmyUnit = advance.numArmyUnit;
	souTerritory = &(*advance.souTerritory);
	tarTerritory = &(*advance.tarTerritory);
}
//destructor

//validate
bool Advance::validate() {
	cout << "\nvalidate for advance order";
	return true;
}

//execute
void Advance::execute() {
	cout << "\nexecute for advance order";
}

/*----------------------------------------------------------------------bomb class---------------------------------------------------------------------*/
Bomb::Bomb(Player* p, Territory* tt) {
	curUser = p;
	tarTerritory = tt;
}

//copy conctructor
Bomb::Bomb(Bomb& bomb) {
	curUser = &(*bomb.curUser);
	tarTerritory = &(*bomb.tarTerritory);
}

//destructor

//validate
bool Bomb::validate() {
	//if user has card "bomb" return true
	cout << "\nvalidate for bomb order";
	return true;
}

//execute
void Bomb::execute() {
	cout << "\nexecute for bomb order";
}


/*----------------------------------------------------------------------blockade class---------------------------------------------------------------------*/
Blockade::Blockade(Player* p, Territory* tt) {
	curUser = p;
	tarTerritory = tt;
}

//copy conctructor
Blockade::Blockade(Blockade& blockade) {
	curUser = &(*blockade.curUser);
	tarTerritory = &(*blockade.tarTerritory);
}

//destructor

//validate
bool Blockade::validate() {
	//if user has card "blockade" return true
	cout << "\nvalidate for blockade order";
	return true;
}

//execute
void Blockade::execute() {
	cout << "\nexecute for blockade order";
}


/*----------------------------------------------------------------------airlift class---------------------------------------------------------------------*/
Airlift::Airlift(Player* p, int naw, Territory* st, Territory* tt) {
	curUser = p;
	numArmyUnit = naw;
	souTerritory = st;
	tarTerritory = tt;
}

//copy conctructor
Airlift::Airlift(Airlift& airlift) {
	curUser = &(*airlift.curUser);
	numArmyUnit = airlift.numArmyUnit;
	souTerritory = &(*airlift.souTerritory);
	tarTerritory = &(*airlift.tarTerritory);
}

//destructor

//validate
bool Airlift::validate() {
	//if user has card "airlift" return true
	cout << "\nvalidate for airlift order";
	return true;
}

//execute
void Airlift::execute() {
	cout << "\nexecute for airlift order";
}

/*----------------------------------------------------------------------negotiate class---------------------------------------------------------------------*/

//conctructor
Negotiate::Negotiate(Player* p, Territory* tt) {
	curUser = p;
	tarTerritory = tt;
}

//copy conctructor
Negotiate::Negotiate(Negotiate& negotiate) {
	curUser = &(*negotiate.curUser);
	tarTerritory = &(*negotiate.tarTerritory);
}

//destructor

//validate
bool Negotiate::validate() {
	//if user has card "diplomacy" return true
	cout << "\nvalidate for negotiate order";
	return true;
}

//execute
void Negotiate::execute() {
	cout << "\nvalidate for negotiate order";
}


/*----------------------------------------------------------------------main---------------------------------------------------------------------*/
int main() {
	cout << "hello world!";

	Player* sampleP = new Player();
	Territory* sampleTarget = new Territory();
	Territory* sampleSource = new Territory();


	//default test to see if individual classes work (diffent possible action class)
	//deploy
	Deploy* testDeploy = new Deploy(sampleP, 100, sampleTarget);
	testDeploy->validate();
	testDeploy->execute();
	//advance
	Advance* testAdvance = new Advance(sampleP, 100, sampleSource, sampleTarget);
	testAdvance->validate();
	testAdvance->execute();
	//bomb
	Bomb* testBomb = new Bomb(sampleP, sampleTarget);
	testBomb->validate();
	testBomb->execute();
	//blockade
	Blockade* testBlockade = new Blockade(sampleP, sampleTarget);
	testBlockade->validate();
	testBlockade->execute();
	//airlift
	Airlift* testAirlift = new Airlift(sampleP, 100, sampleSource, sampleTarget);
	testAirlift->validate();
	testAirlift->execute();
	//negotiate
	Negotiate* testNegotiate = new Negotiate(sampleP, sampleTarget);
	testNegotiate->validate();
	testNegotiate->execute();

	//test to see if order class can contain the different action classes correctly
	//Orders* tODep = new Orders(testDeploy);
}