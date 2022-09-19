#pragma
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;
class Card
{
    public:
    Card();
    Card(string type);
    void play();
    void display();


    string card_type;
    string const cards_list[5]={"Bomb","Reinforcement","Blockade","Airlift","Diplomacy"}; 

};
class Deck
{
    public:
    Deck(int size_of_deck);
    void display();
    Card* draw();

    vector<Card*> deck_content;

};

class Hand
{
    public:
    Hand();
    void draw();

    private:
    vector<Card*> hand_content;
    Deck* associated_deck;
    // Player * associated player
};
