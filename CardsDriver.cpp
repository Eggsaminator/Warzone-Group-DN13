#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>


using namespace std;

#include"Cards.h"
#include"Player.h"
#include"Orders.h"





void testnonrandow()
{
    Deck d=Deck(23,false);
    d.display();
    d.free_deck();
    
}

void testcopy()
{
    cout<<"test of the copy constructor of card\n";
    Card* c1=new Card("Bomb");
    Card* c2=new Card(*c1);
    cout<<(*c2).card_type<<endl;
    (*c1).card_type="Airlift";
    cout<<"C2 is still "<<(*c2).card_type<<endl;
    cout<<"C1 is now "<<(*c1).card_type<<endl;

    cout<<"test of the copy constructor of hand\n";
    Hand* h1=new Hand();
    (*h1).add_card(c1);
    (*h1).add_card(c2);
    cout<<"h1 is\n";
    (*h1).display();

    Hand* h2=new Hand(*h1);
    cout<<"h2 is \n";
    (*h2).display();

    (*h1).remove_card(c1);
    (*c2).card_type="Blockade";

    cout<<"h1 is now\n";
    (*h1).display();

    cout<<"h2 is still\n";
    (*h2).display();

    // verification that the belong_to_hand is copied in the right way

    assert((*h2).hand_content[0]->belong_to_hand==h2);

    (*h1).free_hand();
    (*h2).free_hand();
    delete c1;









}

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

// Delete

(*d_p).free_deck();
(*h_p).free_hand();
delete d_p;
delete h_p;

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
    delete c2;
    delete c3;
    delete c4;

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

    
    
    
    cout<<"We will create a deck of 15 cards evenly distributed between each type and draw 5 of them to compose the hand of a player:\n";


    cout<<"test of deck\n";

    Deck d=Deck(15,false);
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