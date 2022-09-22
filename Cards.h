
#pragma
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;
class Deck;
class Hand;
class Card
{
    public:
    Card();
    Card(string type, Deck* mydeck=NULL, Hand* myhand=NULL);
    void play();
    void display();

    //attributes 
    

    Deck* belong_to_deck;
    Hand* belong_to_hand;
    bool out;


    string card_type;
    string const cards_list[5]={"Bomb","Reinforcement","Blockade","Airlift","Diplomacy"};
    
    
    

    

};


class Hand
{
    public:
    Hand();
    void draw();
    void display();
    void free_hand();
    void add_card(Card* card_in);
    void remove_card(Card* card_out);

    
    vector<Card*> hand_content;
    // Player * associated player
};


class Deck
{
    public:
    Deck(int size_of_deck);
    void display();
    void draw(Hand* hand_of_player);
    void add_card(Card*card_to_add);
    void free_deck();

    vector<Card*> deck_content;

};

