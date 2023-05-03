#include "Team.hpp"
#include <iostream>
#include <climits>

using namespace ariel;
using namespace std;

// Constructor
Team::Team(Character *leader) : count(0), cowboyCount(0)
{
    for (int i = 0; i < 10; i++) // initialize all other characters to NULL
    {
        characters[i] = NULL;
    }
    Cowboy *c = dynamic_cast<Cowboy *>(leader);
    if (c != NULL) // leader is a Cowboy
    {
        this->leader = 0;
    }
    else // leader is a Ninja
    {
        this->leader = 9;
    }
    add(leader);
};

// Destructor
Team::~Team()
{
    for (int i = 0; i < count; i++)
    {
        delete characters[i];
    }
};

// Methods
// void Team::add(Character *newCharacter)
// {
//     if (count == 10)
//     {
//         throw "Team is full";
//     }
//     for (int i = 0; i < count; i++)
//     {
//         if (characters[i] == newCharacter)
//         {
//             throw "Character already in team";
//         }
//     }
//     characters[count] = newCharacter;
//     count++;
// };

// All cowboys are added to the beginning of the array, and all ninjas are added to the end of the array
void Team::add(Character *newCharacter)
{
    if (count == 10)
    {
        throw runtime_error("Team is full");
        return;
    }else if (isAlreadyInTeam(newCharacter))
    {
        throw runtime_error("Character already in team");
        return;
    }
    Cowboy *c = dynamic_cast<Cowboy *>(newCharacter);
    if (c != NULL) // newCharacter is a Cowboy
    {
        characters[cowboyCount++] = newCharacter;
    }
    else // newCharacter is a Ninja
    {
        int ninjaCount = count - cowboyCount;
        characters[10 - ninjaCount - 1] = newCharacter;
    }
    count++;
};

bool Team::isAlreadyInTeam(Character *character){
    for (int i = 0; i < count; i++)
    {
        if (characters[i] == character)
        {
            return true;
        }
    }
    return false;
}

int Team::stillAlive() const
{
    int alive = 0;
    for (int i = 0; i < 10; i++)
    {
        if (characters[i] && characters[i]->isAlive())
        {
            alive++;
        }
    }
    return alive;
};

// void Team::print() const
// {
//     cout << "Team: " << endl;
//     cout << "Members: " << endl;
//     for (int i = 0; i < count; i++)
//     {
//         if(i == leader) cout << "LEADER ";
//         characters[i]->print();
//     }
// };

void Team::print() const
{
    cout << " --------------------------------- " << endl;
    cout << "Team: " << endl;
    cout << "Members: " << endl;

    // Cowboys
    for (int i = 0; i < cowboyCount; i++)
    {
        if (i == leader)
            cout << "LEADER ";
        characters[i]->print();
    }
    // Ninjas
    int ninjaCount = count - cowboyCount;
    for (int i = 9; i > 9 - ninjaCount; i--)
    {
        if (i == leader)
            cout << "LEADER ";
        characters[i]->print();
    }
    cout << " --------------------------------- " << endl;
};

void Team::findNewLeader()
{
    int newLeader = -1;
    double minDistance = __DBL_MAX__;
    for (int i = 0; i < 10; i++)
    {
        if (i != leader && characters[i] && characters[i]->isAlive())
        {
            double distance = characters[i]->distance(*(characters[leader]));
            if (distance < minDistance)
            {
                minDistance = distance;
                newLeader = i;
            }
        }
    }
    if (newLeader == -1)
    {
        throw runtime_error("Cant find new leader.No one is alive.");
    }
    else
    {
        leader = newLeader;
    }
};

int Team::findTarget(Character leader)
{
    int target = -1;
    double minDistance = __DBL_MAX__;
    for (int i = 0; i < 10; i++)
    {
        if (characters[i] && characters[i]->isAlive())
        {
            double distance = characters[i]->distance(leader);
            if (distance < minDistance)
            {
                minDistance = distance;
                target = i;
            }
        }
    }
    return target;
}

void Team::attack(Team *otherTeam)
{
    if (stillAlive() == 0 || otherTeam->stillAlive() == 0) return; 
    
    if (!otherTeam->characters[otherTeam->leader]->isAlive())
    {
        otherTeam->findNewLeader();
    }
    int target = otherTeam->findTarget(*(characters[leader])); // find target that close to leader
    if (target == -1)
        return;

    // Cowboys attack first
    for (int i = 0; i < cowboyCount; i++)
    {
        if (characters[i]->isAlive())
        {
            Cowboy &cowboy = dynamic_cast<Cowboy &>(*(characters[i]));
            cowboy.shoot(*(otherTeam->characters[target]));
            target = checkTarget(target, otherTeam); // check if target is still alive or find new target
            if (target == -1) return;
        }
    }

    // Ninjas attack
    int ninjaCount = count - cowboyCount;
    for (int i = 9; i > 9 - ninjaCount; i--)
    {
        if (characters[i]->isAlive())
        {
            Ninja &ninja = dynamic_cast<Ninja &>(*(characters[i]));
            cout << "Ninja " << i << " attacks" << "target " << target << endl;
            ninja.slash(*(otherTeam->characters[target]));
            target = checkTarget(target, otherTeam); // check if target is still alive or find new target
            if (target == -1) return;
        }
    }
};

int Team::checkTarget(int target, Team *otherTeam)
{
    cout << "here" << endl;
    if (!otherTeam->characters[target]->isAlive())
    {
        cout << "here2" << endl;
        target = otherTeam->findTarget(*(characters[leader]));
    }
    return target;
}
