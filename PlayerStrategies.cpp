#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy(Player* p) {
	player = p;
}


HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p){}

bool HumanPlayerStrategy::issueOrder(vector<Player*> allPlayers) {

}
vector<Territory*> HumanPlayerStrategy::toDefend() {

}
vector<Territory*> HumanPlayerStrategy::toAttack() {

}


AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool AggressivePlayerStrategy::issueOrder(vector<Player*> allPlayers) {

}
vector<Territory*> AggressivePlayerStrategy::toDefend() {

}
vector<Territory*> AggressivePlayerStrategy::toAttack() {

}


BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool BenevolentPlayerStrategy::issueOrder(vector<Player*> allPlayers) {

}
vector<Territory*> BenevolentPlayerStrategy::toDefend() {

}
vector<Territory*> BenevolentPlayerStrategy::toAttack() {

}


NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool NeutralPlayerStrategy::issueOrder(vector<Player*> allPlayers) {
	return false;
}
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	return vector<Territory*>{};
}
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	return vector<Territory*>{};
}


CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p) {}
bool CheaterPlayerStrategy::issueOrder(vector<Player*> allPlayers) {

}
vector<Territory*> CheaterPlayerStrategy::toDefend() {

}
vector<Territory*> CheaterPlayerStrategy::toAttack() {

}