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
OrderList* Player::issueOrder() {
	return strategy->issueOrder();
}

//method that prints out teritories to defend, would return them in future
vector<Territory*> Player::toDefend() {
	return strategy->toDefend();
}

//method that prints out teritories to attack, would return them in future
vector<Territory*> Player::toAttack() {
	return strategy->toAttack();
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
