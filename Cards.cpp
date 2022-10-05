#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
using namespace std;

#include"Cards.h"
#include"Player.h"

//Initialization of the cards type

vector<string> all_my_cards={"Bomb","Reinforcement","Blockade","Airlift","Diplomacy"};
vector<string> Card::cards_list=all_my_cards;
vector<string> Deck::cards_list=all_my_cards;

Card::Card()
{ // Random constructor. Create a card of a random type
int num =rand() % 5;
card_type=cards_list[num];
}

Card::Card(Card &card)
{ // Copy Constructor of the Card Class
    card_type=card.card_type;
    belong_to_deck=&(*card.belong_to_deck);
    belong_to_hand=&(*card.belong_to_hand);
    
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

void Card::setType(string type)
{
    card_type=type;
}

void Card::setDeck(Deck* deck)
{
    belong_to_deck=deck;
}

void Card::setHand(Hand* hand)
{
    belong_to_hand=hand;
}


void Card::display()
{
    cout<<card_type;
}


void Card::play()
{   //Assert that thecard belong to a deck and a hand and that the hand is indeed asigned to a player
    assert(belong_to_deck!=NULL);
    assert(belong_to_hand!=NULL);
    assert(belong_to_hand->my_player!=NULL);



    
    if(card_type=="Bomb")
    {
        //belong_to_hand->my_player->ordersList->add_orders(new Bomb());
        //belong_to_hand->my_player->ordersList->add_orders();
        belong_to_hand->my_player->issueOrder("Bomb");

    }
    if(card_type=="Reinforcement")
    {
        belong_to_hand->my_player->issueOrder("Reinforcement");

    }
    if(card_type=="Airlift")
    {
        //belong_to_hand->my_player->ordersList->add_orders(new Airlift());
        //belong_to_hand->my_player->ordersList->add_orders();
        belong_to_hand->my_player->issueOrder("Airlift");

    }
    if(card_type=="Diplomacy")
    {
        //belong_to_hand->my_player->ordersList->add_orders(new Negociate());
        //belong_to_hand->my_player->ordersList->add_orders();
        belong_to_hand->my_player->issueOrder("Diplomacy");
        

    }   
    if(card_type=="Blockade")
    {
        //belong_to_hand->my_player->ordersList->add_orders();
        //belong_to_hand->my_player->ordersList->add_orders(new Blockade());
        belong_to_hand->my_player->issueOrder("Blockade");
        

    }


    //insert code to deal with the order
    

    // remove from hand
    (*belong_to_hand).remove_card(this);

    // place back in deck

    (*belong_to_deck).add_card(this); 


}


/*
Deck Class

*/

Deck::Deck()
{

}

Deck::Deck(int s,bool is_random)
{if(is_random){
    for(int i=0;i<s;i++)
    {
     deck_content.push_back(new Card());
     (*deck_content[i]).belong_to_deck=this; 
    }
}
else
{
    int current_size=0;
    while(current_size<s)
    {deck_content.push_back(new Card(cards_list[current_size%5]));
     (*deck_content[current_size]).setDeck(this); 
     current_size++;
        

    }
}
    
}

Deck::Deck(Deck &deck)
{//Copy constructor of the Deck class



for(int i=0;i<size(deck.deck_content);i++)
    {
        // for each card present in the hand we want to copy we will create a copy of this card and place it within the new hand
        Card* card_p=new Card(*deck.deck_content[i]);
        (*card_p).belong_to_deck=this;
        deck_content.push_back(card_p);
        
    }

}

void Deck::display()
{cout<<"[";
    for(int i=0;i<size(deck_content);i++)
    {
        (*deck_content[i]).display();
        cout<<" ,";
    }
    cout<<"]"<<endl;

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
        delete deck_content[i];
    }
}


/**
Class Hand
*/

Hand::Hand()
{

}

Hand::Hand(Hand &hand)
{
    // Copy Constructor of the hand class

    for(int i=0;i<size(hand.hand_content);i++)
    {
        // for each card present in the hand we want to copy we will create a copy of this card and place it within the new hand
        Card* card_p=new Card(*hand.hand_content[i]);
        (*card_p).belong_to_hand=this;
        hand_content.push_back(card_p);
        
    }
}

void Hand::display()
{cout<<"{";
    for(int i=0;i<size(hand_content);i++)
    {
        (*hand_content[i]).display();
        cout<<", ";
    }
cout<<"}"<<endl;
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

void Hand::setPlayer(Player* player)
{
    my_player=player;
}


void Hand::free_hand()
{
    for(int i=0;i<size(hand_content);i++)
    {
        delete hand_content[i];
    }
}
