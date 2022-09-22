#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

#include"Cards.h"

void testCards();
void testDeck();
void testHand();
void testplay();

void testplay()
{cout<<"Test of the play function\n";

Deck* d_p=new Deck(8);
Hand* h_p=new Hand();
cout<<"initial deck is\n";
(*d_p).display();

for(int i=0;i<3;i++)
{//we draw 3 times
    (*d_p).draw(h_p);
}
cout<<"my hand is \n";
(*h_p).display();

(*((*h_p).hand_content[1])).play();

cout<<"my new hand is\n";

(*h_p).display();

cout<<"Final deck is:\n";
(*d_p).display();



}


void testHand()
{
    cout<<"Test of the function of the Hand Class\n";
    Hand* h_p=new Hand();
    Card* c1=new Card("Bomb");
    Card* c2=new Card("Airlift");
    Card* c3=new Card("Reinforcement");
    Card* c4=new Card("Blockade");

    (*h_p).add_card(c1);
    (*h_p).add_card(c2);

    cout<<"initial hand is:\n";


    (*h_p).display();


    (*h_p).remove_card(c2);
    (*h_p).remove_card(c3);

    cout<<"new hand is:\n";

    (*h_p).display();

    (*h_p).free_hand();
    free(c2);
    free(c3);
    free(c4);

}



void testDeck()
{
cout<<"test of the add to deck function\n";
Deck d_test=Deck(5);
Card* card_test=new Card("Bomb");
cout<<"initial deck is:\n";
d_test.display();

d_test.add_card(card_test);

cout<<"new deck is\n";

d_test.display();
d_test.free_deck();
}

void testCards()
{ 

    
    
    
    cout<<"We will create a deck of 10 cards and draw 5 of them to compose the hand of a player:\n";


    cout<<"test of deck\n";

    Deck d=Deck(10);
    Hand* h_p=new Hand();

    cout<<"initial deck is:\n";
    
    d.display();

    for(int i=0;i<5;i++){

    d.draw(h_p);}


    cout<<"the remaining deck is:\n";
    d.display();

    cout<<"the hand now is:\n";

    (*h_p).display();

    (*h_p).free_hand();
    free(h_p);
    d.free_deck();



}

int main()
{
    testplay();
    
    //testHand();
    //testDeck();
    //testCards();
}