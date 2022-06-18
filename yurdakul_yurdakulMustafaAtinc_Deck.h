#ifndef _DECK_H
#define _DECK_H
#include <string>
#include <iostream>
using namespace std;

struct Card
{
    string name;
    int energy;
    Card(string n="",int e=0)
        :name(n),energy(e)
    {}
    bool operator==(const Card & rhs) const
    {
        return (name==rhs.name) && (energy==rhs.energy);
    }
};

class Deck
{
private:
    Card * cards;
    int size;
public:
    Deck();
    Deck(const Deck & rhs);
    ~Deck();
    Card * getCards() const;
    int getSize() const;
    Deck operator+(const Card & rhs);
    Deck operator+(const Deck & rhs);
    Deck & operator+=(const Deck & rhs);
    Deck operator-(int num);
    Deck & operator=(const Deck & rhs);
    bool operator==(const Deck & rhs) const;
    int totalEnergy() const;
    bool operator<(const Deck & rhs) const;
    bool operator>(int rhs) const;
    Card & operator[](int rhs) const;
};
ostream & operator<<(ostream & os, const Deck & rhs);
bool operator<=(const Card & lhs, const Deck & rhs);

#endif