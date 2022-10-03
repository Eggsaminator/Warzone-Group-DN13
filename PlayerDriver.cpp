#include "Player.h"
#include <iostream>
using namespace std;

int main() {
	Player p1 = Player("jose");
	
	cout << "now entering to defend method.\n";
	p1.toDefend();
	cout << "now exiting to defend method.\n";

}