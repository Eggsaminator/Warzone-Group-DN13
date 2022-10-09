
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;
class Deck;
class Hand;
class Player;

//The Class card defines the Card object that can be drawn from a Deck, placed in a Hand and played by the player

class Card
{
    public:
    //default constructor: creates a Card with a random type
    Card();

    //Constructor: creates a card with the given type and optionnal the hand/deck it belongs to
    Card(string type, Deck* mydeck=NULL, Hand* myhand=NULL);

    //Copy Constructor
    Card(Card &card);
    
    //Stream insertion operator
    void display();
    
    //Assignment Operator
    void setType(string type);
    void setHand(Hand* myhand);
    void setDeck(Deck* mydeck);

    //Service method
    void play();

    Deck* belong_to_deck;
    Hand* belong_to_hand;
    
// string defining the type of the card. Should be in the form of one of the card_list members
    string card_type;
    static vector<string> cards_list;
};

// The Hand class defines a collection of Card owned by one player

class Hand
{
    public:

    //Default constructor
    Hand();

    //Copy Constructor
    Hand(Hand &hand);

    //Destructor 
    void free_hand();

    // Stream insertion operator
    void display();
    
    //Assignment operator
    void add_card(Card* card_in);
    void remove_card(Card* card_out);
    void setPlayer(Player* player);

    vector<Card*> hand_content;
    Player* my_player;
};


//The Deck class defines a collection of card from which the player can draw a card

class Deck
{
    public:

    //Default Constructor: creates an empty Deck
    Deck();

    //Constructor of an even Deck

    //Constructor that generates a random deck with the given size
    Deck(int size_of_deck,bool is_random = true);

    //Copy Constructor
    Deck(Deck &deck);

    //Stream insertion operator
    void display();

    //Assignment operator

    void add_card(Card*card_to_add);

    //Destructor
    void free_deck();

    //Service method

    void draw(Hand* hand_of_player);

    vector<Card*> deck_content;
    static vector<string> cards_list;
};
