#include "Team.hpp"
#include <iostream>
#include <climits>
#include <stdexcept>


using namespace ariel;
using namespace std;

// Constructor
Team::Team(Character *leader) : count(0), cowboyCount(0)
{
    for (unsigned int i = 0; i < TEAM_SIZE; i++) // initialize all other characters to NULL
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


// Methods

// All cowboys are added to the beginning of the array, and all ninjas are added to the end of the array
void Team::add(Character *newCharacter)
{
    if (count == TEAM_SIZE)
    {
        throw runtime_error("Team is full");
        return;
    }else if (isAlreadyInTeam(newCharacter))
    {
        throw runtime_error("Character already in team");
        return;
    }
    Cowboy *c = dynamic_cast<Cowboy *>(newCharacter);
    Ninja *n = dynamic_cast<Ninja *>(newCharacter);
    if (c != NULL) // newCharacter is a Cowboy
    {
        characters[cowboyCount++] = newCharacter;
    }
    else if (n != NULL) // newCharacter is a Ninja
    {
        characters[TEAM_SIZE - 1 - (count - cowboyCount)] = newCharacter;
    }else{
        throw runtime_error("Invalid character type (not Cowboy or Ninja))");
        return;
    }

    count++;
};

bool Team::isAlreadyInTeam(Character *character){
    for (unsigned int i = 0; i < count; i++)
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
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
    {
        if (characters[i] && characters[i]->isAlive())
        {
            alive++;
        }
    }
    return alive;
};

void Team::print() const
{
    cout << " --------------------------------- " << endl;
    cout << "Team: " << endl;
    cout << "   Members: " << endl;

    // Cowboys
    for (unsigned int i = 0; i < cowboyCount; i++)
    {
        if (i == leader)
            cout << "LEADER";
        cout << "   " << characters[i]->print() << endl;
    }
    // Ninjas
    unsigned int ninjaCount = count - cowboyCount;
    for (unsigned int i = 9; i > 9 - ninjaCount; i--)
    {
        if (i == leader)
            cout << "LEADER";
        cout << "    " << characters[i]->print() << endl;
    }
    cout << " --------------------------------- " << endl;
};

void Team::findNewLeader()
{
    unsigned int newLeader = TEAM_SIZE;
    double minDistance = __DBL_MAX__;
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
    {
        if (i != leader && characters[i] && characters[i]->isAlive())
        {
            double distance = characters[i]->distance(characters[leader]);
            if (distance < minDistance)
            {
                minDistance = distance;
                newLeader = i;
            }
        }
    }
    if (newLeader == TEAM_SIZE)
    {
        throw runtime_error("Cant find new leader.No one is alive.");
    }
    else
    {
        leader = newLeader;
    }
};

unsigned int Team::findTarget(Character *leader)
{
    unsigned int target = TEAM_SIZE;
    double minDistance = __DBL_MAX__;
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
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
    if(otherTeam == NULL){
        throw runtime_error("Cant attack NULL team");
        return;
    };
    if(this == otherTeam){
        throw runtime_error("Cant attack itself");
        return;
    };
    if (stillAlive() == 0){
        throw runtime_error("Dead/empty team cant attack");
        return;
    }; 
    if(otherTeam->stillAlive() == 0){
        throw runtime_error("Cant attack dead/empty team");
        return;
    };
    
    if (!otherTeam->characters[otherTeam->leader]->isAlive())
    {
        otherTeam->findNewLeader();
    }
    unsigned int target = otherTeam->findTarget(characters[leader]); // find target that close to leader
    if (target == TEAM_SIZE) // no target found
        return;

    // Cowboys attack first
    for (unsigned int i = 0; i < cowboyCount; i++)
    {
        if (characters[i]->isAlive())
        {
            Cowboy &cowboy = dynamic_cast<Cowboy &>(*(characters[i]));
            cowboy.shoot(otherTeam->characters[target]);
            target = checkTarget(target, otherTeam); // check if target is still alive or find a new target
            if (target == TEAM_SIZE) return;
        }
    }

    // Ninjas attack
    unsigned int ninjaCount = count - cowboyCount;
    for (unsigned int i = 9; i > 9 - ninjaCount; i--)
    {
        if (characters[i]->isAlive())
        {
            Ninja &ninja = dynamic_cast<Ninja &>(*(characters[i]));
            ninja.slash(otherTeam->characters[target]);
            target = checkTarget(target, otherTeam); // check if target is still alive or find a new target
            if (target == TEAM_SIZE) return;
        }
    }
};

unsigned int Team::checkTarget(unsigned int target, Team *otherTeam)
{
    if (!otherTeam->characters[target]->isAlive())
    {
        target = otherTeam->findTarget(characters[leader]);
    }
    return target;
}
