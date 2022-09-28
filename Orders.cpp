#include "Orders.h"

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


//order class
Orders::Orders(string user) {
	curUser = user;
}

//deploy class
Deploy::Deploy(string n, int num) {
	name = n;
	numArmyUnit = num;
}

//copy conctructor

//destructor

//validate
bool Deploy::validate() {
	return true;
}

//execute
void Deploy::execute() {
}

//advance class
Advance::Advance(string n, int num) {
	name = n;
	numArmyUnit = num;
}

//copy conctructor

//destructor

//validate
bool Advance::validate() {
	return true;
}

//execute
void Advance::execute() {
}

//bomb class
Bomb::Bomb(string n) {
	name = n;
}

//copy conctructor

//destructor

//validate
bool Bomb::validate() {
	//if user has card "bomb" return true
}

//execute
void Bomb::execute() {
}

//blockade class
Blockade::Blockade(string n) {
	name = n;
}

//copy conctructor

//destructor

//validate
bool Blockade::validate() {
	//if user has card "blockade" return true
}

//execute
void Blockade::execute() {
}

//airlift class
Airlift::Airlift(string n, int num) {
	name = n;
	numArmyUnit = num;
}

//copy conctructor

//destructor

//validate
bool Airlift::validate() {
	//if user has card "airlift" return true
}

//execute
void Airlift::execute() {
}

//negotiate class

//conctructor
Negotiate::Negotiate(string n, string user) {
	name = n;
	tarUser = user;
}

//copy conctructor

//destructor

//validate
bool Negotiate::validate() {
	//if user has card "diplomacy" return true
}

//execute
void Negotiate::execute() {
}