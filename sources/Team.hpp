#include "Character.hpp"

class Team
{
    Character characters[10];
    int count;
    int leader;
public:
    Team(Character *leader);
    void add(Character *c);
    void attack(Team *t);
    bool stillAlive() const;
    void print() const;
    ~Team();

};