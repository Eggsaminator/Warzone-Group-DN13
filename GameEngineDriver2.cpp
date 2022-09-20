#include <iostream>;
	using std::cin;
	using std::cout;
	using std::endl;

void testGameStates() {
	string currentCommand = "";
	while (currentCommand != "exit") {
		cin >> currentCommand;
		cout << "yeah: " + currentCommand;
	}

}

int main()
{
	testGameStates();
}