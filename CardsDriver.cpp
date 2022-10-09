#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>


using namespace std;

#include"Cards.h"
#include"Player.h"
#include"Orders.h"

void testCards()
{ 
    cout<<"We will create a deck of 15 cards evenly distributed between each type and draw 5 of them to compose the hand of a player:\n";


    cout<<"test of deck\n";

    Deck d(15, false);
    Hand* h_p=new Hand();
    Player* player=new Player("test_player");
    h_p->setPlayer(player);

    cout<<"initial deck is:\n";
    
    d.display();

    for(int i=0;i<5;i++){

    d.draw(h_p);}


    cout<<"the remaining deck is:\n";
    d.display();

    cout<<"the hand now is:\n";

    (*h_p).display();

    cout<<"We will now play the cards of the hand"<<endl;

    (*((*h_p).hand_content[0])).play();
    (*((*h_p).hand_content[0])).play();
    (*((*h_p).hand_content[0])).play();
    (*((*h_p).hand_content[0])).play();
    (*((*h_p).hand_content[0])).play();

    cout<<"After playing my new hand is:"<<endl;

    (*h_p).display();

    cout<<"The orderList of the player that played the cards is:"<<endl;

   (*player).ordersList->toString();

    cout<<"The deck is now"<<endl;
    d.display();

    (*h_p).free_hand();
    delete h_p;
    d.free_deck();
}