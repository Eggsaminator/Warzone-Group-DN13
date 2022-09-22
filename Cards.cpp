#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
using namespace std;

#include"Cards.h"

Card::Card()
{
int num =rand() % 5;
card_type=cards_list[num];
}

Card::Card(string type,Deck* mydeck, Hand* myhand){
    bool valid=false;
    for(int i=0;i<size(cards_list);i++)
    {
        if(cards_list[i]==type)
        {card_type=type;
        valid=true;

        }
    }
    if(!valid)
    {
        cout<<"invalid card type\n";
    }
    belong_to_deck=mydeck;
    belong_to_hand=myhand;
}


void Card::display()
{
    cout<<card_type<<"\n";
}


void Card::play()
{
    //insert code to deal with the order
    assert(belong_to_deck!=NULL);
    assert(belong_to_hand!=NULL);

    // remove from hand
    (*belong_to_hand).remove_card(this);

    // place back in deck

    (*belong_to_deck).add_card(this); 


}


/*
Deck Class

*/

Deck::Deck(int s)
{
    for(int i=0;i<s;i++)
    {
     deck_content.push_back(new Card());
     (*deck_content[i]).belong_to_deck=this; 
    }
    
}

void Deck::display()
{
    for(int i=0;i<size(deck_content);i++)
    {
        (*deck_content[i]).display();
    }

}

void Deck::add_card(Card* card_to_add)
{
    deck_content.push_back(card_to_add);

}

void Deck::draw(Hand* hand_of_player)
{
    int card_i =rand() % size(deck_content);
    Card* selected_card=deck_content[card_i];
    (*selected_card).belong_to_hand=hand_of_player;
    deck_content.erase(deck_content.begin()+card_i);
    (*hand_of_player).hand_content.push_back(selected_card);
    

}

void Deck::free_deck()
{
    for(int i=0;i<size(deck_content);i++)
    {
        free(deck_content[i]);
    }
}


/**
Class Hand
*/

Hand::Hand()
{

}

void Hand::display()
{
    for(int i=0;i<size(hand_content);i++)
    {
        (*hand_content[i]).display();
    }
}


void Hand::add_card(Card* card_in)
{
    hand_content.push_back(card_in);
    (*card_in).belong_to_hand=this;
}


void Hand::remove_card(Card* card_out)
{
    bool card_found=false;
    int i=0;
    while(i<size(hand_content)&&!card_found)
    {
        if(hand_content[i]==card_out)
        {// e found the card and we want to erase it
            card_found=true;
            (*card_out).belong_to_hand=NULL;
            hand_content.erase(hand_content.begin()+i);
        }
        else
        {
            // we move on to the next card
            i++;
        }
    }
    if(!card_found)
    {
        cout<<"error card not in the hand\n";
    }
}


void Hand::free_hand()
{
    for(int i=0;i<size(hand_content);i++)
    {
        free(hand_content[i]);
    }
}


/**
int main()
{
    // seed for the random generation of cards !!
    srand((unsigned) time(NULL));


    cout<<"hello world\n";
    Card* card_test=new Card("Bomb");
    Card* card_test2=new Card("blabla");
    (*card_test).display();
    free(card_test);
    free(card_test2);
    
    cout<<"test of deck\n";

    Deck d=Deck(5);
    Hand* h_p=new Hand();

    cout<<"initial deck is:\n";
    
    d.display();

    d.draw(h_p);


    cout<<"the remaining deck is:\n";
    d.display();

    cout<<"the hand now is:\n";

    (*h_p).display();

    (*h_p).free_hand();
    free(h_p);
    d.free_deck();




}*/