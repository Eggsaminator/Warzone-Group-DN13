#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

#include"Cards.h"

Card::Card()
{
int num =rand() % 5;
card_type=cards_list[num];
}

Card::Card(string type){
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
}


void Card::display()
{
    cout<<card_type<<"\n";
}

void play()
{

}


/*
Deck Class

*/

Deck::Deck(int s)
{
    for(int i=0;i<s;i++)
    {
     deck_content.push_back(new Card());   
    }
}

void Deck::display()
{
    for(int i=0;i<size(deck_content);i++)
    {
        (*deck_content[i]).display();
    }

}

Card* Deck::draw()
{
    int card_i =rand() % size(deck_content);
    Card* selected_card=deck_content[card_i];
    deck_content.erase(deck_content.begin()+card_i);
    return(selected_card);

}

Hand::Hand()
{

}




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

    cout<<"initial deck is:\n";
    
    d.display();

    cout<<"we draw a card wich is:\n";
    (*d.draw()).display();

    cout<<"the remaining deck is:\n";
    d.display();


}