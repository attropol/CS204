#include "yurdakul_yurdakulMustafaAtinc_Deck.h"
Deck::Deck()
{
    size = 0;
    cards = nullptr;
}

Deck::Deck(const Deck & rhs)
{
    size = rhs.size;
    cards = new Card[rhs.size];
    for (int i = 0; i < rhs.size; i++)
    {
        cards[i] = rhs.cards[i];
    }
}

Deck::~Deck()
{
    delete[] cards;
}

Card *Deck::getCards() const
{
    return cards;
}
int Deck::getSize() const
{
    return size;
}

ostream & operator<<(ostream & os, const Deck & rhs)
{
    for (int i = 0; i < rhs.getSize(); i++)
    {
        os << i+1  << ": " << rhs.getCards()[i].name << " - " << rhs.getCards()[i].energy << endl;
    }
    return os;
}

Deck Deck::operator+(const Card & rhs)
{
    Deck newdeck;
    newdeck.cards = new Card[size+1];
    newdeck.size = size +1;
    for (int i = 0; i < size; i++)
    {
        newdeck.cards[i] = cards[i];
    }
    newdeck.cards[size] = rhs;
    return newdeck;
}

Deck Deck::operator+(const Deck & rhs)
{
    Deck newdeck;
    newdeck.cards = new Card[size+rhs.size];
    newdeck.size = size + rhs.size;
    for (int i = 0; i < size; i++)
    {
        newdeck.cards[i] = cards[i];
    }
    for (int i = 0; i < rhs.size; i++)
    {
        newdeck.cards[size+i] = rhs.cards[i];
    }
    return newdeck;
}

Deck & Deck::operator+=(const Deck & rhs)
{
    Deck oldobj(*this);
    delete[] cards;
    size = oldobj.size + rhs.size;
    cards = new Card[oldobj.size + rhs.size];
    for (int i = 0; i < oldobj.size; i++)
    {
        cards[i] = oldobj.cards[i];
    }
    for (int i = 0; i < rhs.size; i++)
    {
        cards[oldobj.size+i] = rhs.cards[i];
    }
    return *this;
}

Deck Deck::operator-(int num)
{
    Deck newdeck;
    if(num<size)
    {
        newdeck.size = size-num;
        newdeck.cards = new Card[size-num];
        for (int i = 0; i < size-num; i++)
        {
            newdeck.cards[i]= cards[num+i];
        }
    }
    return newdeck;
}

Deck & Deck::operator=(const Deck & rhs)
{
    if(this!=&rhs)
    {
        delete[] cards;
        size = rhs.size;
        cards = new Card[rhs.size];
        for (int i = 0; i < rhs.size; i++)
        {
            cards[i] = rhs.cards[i];
        }
    }
    return *this;
}

int Deck::totalEnergy() const
{
    int total = 0;
    for (int i = 0; i < size; i++)
    {
        total+=cards[i].energy;
    }
    return total;    
}

bool Deck::operator==(const Deck & rhs) const
{
    return totalEnergy()==rhs.totalEnergy();
}

bool Deck::operator<(const Deck & rhs) const
{
    return totalEnergy()<rhs.totalEnergy();
}

bool Deck::operator>(int rhs) const
{
    return size>rhs;
}

bool operator<=(const Card & lhs, const Deck & rhs)
{
    for (int i = 0; i < rhs.getSize(); i++)
    {
        if(lhs==rhs.getCards()[i])
            return true;
    }
    return false;
}

Card & Deck::operator[](int rhs) const
{
    return cards[rhs];
}