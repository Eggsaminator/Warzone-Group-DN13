#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;

//dont know if we will need/keep this
Player::Player() {
	name = "nameless player";
}

//player constructor
Player::Player(string username) {
	name = username;
	ordersList = new OrderList(name);
	hand = new Hand();
}

void Player::addTerritory(Territory* newTerritory){
	territories.push_back(newTerritory);
}

//method for a player to issue an order, takes the order's name
bool Player::issueOrder(vector<Player*> allPlayers) {
	return strategy->issueOrder(allPlayers);

	//if (name == "Bomb") {
	//	if (toAttack().size() > 0) {
	//		int randomToAttackIndex = rand() % toAttack().size();
	//		Territory* destinationTerritory = toAttack().at(randomToAttackIndex);

	//		Orders* orderToAdd = new Bomb(nameP, destinationTerritory);
	//		(*ordersList).addOrder(orderToAdd);
	//	}
	//}
	//else if (name == "Reinforcement") {
	//	//WHAT DO WE DO WITH REINFORCEMENT CARDS?
	//}
	//else if (name == "Airlift") {
	//	int randomSourceIndex = rand() % territories.size();
	//	Territory* sourceTerritory = territories.at(randomSourceIndex);

	//	int randomNbArmyUnits = rand() % (sourceTerritory->getArmies() + 1);

	//	if (toDefend().size() > 0) {
	//		int randomToDefendIndex = rand() % toDefend().size();
	//		Territory* destinationTerritory = toDefend().at(randomToDefendIndex);

	//		Orders* orderToAdd = new Airlift(nameP, randomNbArmyUnits, sourceTerritory, destinationTerritory);
	//		(*ordersList).addOrder(orderToAdd);
	//	}
	//}
	//else if (name == "Negotiate") {
	//	bool randomPlayerPicked = false;
	//	Player* randomPlayer = nullptr;

	//	while (!randomPlayerPicked) {
	//		int randomPlayerIndex = rand() % allPlayers.size();
	//		if (allPlayers[randomPlayerIndex] != nameP) {
	//			randomPlayerPicked = true;
	//			randomPlayer = allPlayers[randomPlayerIndex];
	//		}
	//	}

	//	Orders* orderToAdd = new Negotiate(nameP, randomPlayer);
	//	(*ordersList).addOrder(orderToAdd);
	//}
	//else if (name == "Blockade") {
	//	if (territories.size() > 0) {
	//		int randomTargetIndex = rand() % territories.size();
	//		Territory* targetTerritory = territories.at(randomTargetIndex);

	//		Orders* orderToAdd = new Blockade(nameP, targetTerritory);
	//	}
	//}
}

//method that prints out teritories to defend, would return them in future
vector<Territory*> Player::toDefend() {
	return strategy->toDefend();
	//return territoriesToDefend;
}

//method that prints out teritories to attack, would return them in future
vector<Territory*> Player::toAttack() {
	return strategy->toAttack();
	//return territoriesToAttack;
}

void Player::setHand(Hand* newHand){
	hand = newHand;
}
Hand* Player::getHand(){
	return hand;
}

void Player::setName(string newName){
	name = newName;
}
string Player::getName(){
	return name;
}

void Player::setTerritories(vector<Territory*> newTerritories){
	territories = newTerritories;
}
vector<Territory*> Player::getTerritories(){
	return territories;
}

void Player::setOrdersList(OrderList* newOrdersList){
	ordersList = newOrdersList;
}

void Player::setTerritoriesToAttack(vector<Territory*> territoriesList) {
	territoriesToAttack = territoriesList;
}

void Player::setTerritoriesToDefend(vector<Territory*> territoriesList) {
	territoriesToDefend = territoriesList;
}

OrderList* Player::getOrdersList(){
	return ordersList;
}

int Player::getReinforcementPool() {
	return reinforcementPool;
}

void Player::setReinforcementPool(int armyUnits) {
	reinforcementPool = armyUnits;
}

int Player::getReinforcementPoolLeftToDeploy() {
	return reinforcementPoolLeftToDeploy;
}

void Player::setReinforcementPoolLeftToDeploy(int armyUnits) {
	reinforcementPoolLeftToDeploy = armyUnits;
}

//part 4
void Player::setTruce(Player* tp) {
	nameT = tp->getName();
}

string Player::getTruce() {
	return nameT;
}

void Player::addOrder(Orders* order) {
	
}

void Player::setConquered(bool tf) {
	territoryConquered = tf;
}

bool Player::getConquered() {
	return territoryConquered;
}

void Player::addArmy(int army)
{
	reinforcementPool+=army;
}

void Player::removeArmy(int army)
{
	if(army>reinforcementPool)
	{
		cout<<"invalid operation: not enough army in pool";
	}
	else{
	reinforcementPool-=army;}
}
