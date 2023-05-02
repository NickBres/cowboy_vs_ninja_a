#include "Team.hpp"
#include <iostream>
#include <climits>

using namespace ariel;
using namespace std;

// Constructor
Team::Team(Character *leader) : count(0), leader(0)
{
    add(leader);
    for (int i = 1; i < 10; i++) // initialize all other characters to NULL
    {
        characters[i] = NULL;
    }
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
void Team::add(Character *newCharacter){ 
    if (count == 10)
    {
        throw "Team is full";
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


int Team::stillAlive() const
{
    int alive = 0;
    for (int i = 0; i < count; i++)
    {
        if (characters[i]->isAlive())
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
    cout << "Team: " << endl;
    cout << "Members: " << endl;

    // Cowboys
    for(int i = 0; i < cowboyCount; i++){
        if(i == leader) cout << "LEADER ";
        characters[i]->print();
    }
    // Ninjas
    int ninjaCount = count - cowboyCount;
    for(int i = 9; i > 9 - ninjaCount; i--){
        if(i == leader) cout << "LEADER ";
        characters[i]->print();
    }

};

void Team::findNewLeader()
{
    int newLeader = -1;
    double minDistance = __DBL_MAX__;
    for(int i = 0 ;i < 10; i++){
        if(i != leader && characters[i] && characters[i]->isAlive()){
            double distance = characters[i]->distance(*(characters[leader]));
            if(distance < minDistance){
                minDistance = distance;
                newLeader = i;
            }
        }
    }
    if(newLeader == -1){
        throw "Cant find new leader.No one is alive.";
    }else{
        leader = newLeader;
    }
};

int Team::findTarget(Character leader){
    int target = -1;
    double minDistance = __DBL_MAX__;
    for(int i = 0 ;i < 10; i++){
        if(characters[i] && characters[i]->isAlive()){
            double distance = characters[i]->distance(leader);
            if(distance < minDistance){
                minDistance = distance;
                target = i;
            }
        }
    }
    if(target == -1)  throw "Cant find target.No one is alive.";
    return target;
}

void Team::attack(Team *otherTeam)
{
    if (stillAlive() == 0)
    {
        throw "Team is dead";
        return;
    }
    if (!otherTeam->stillAlive())
    {
        throw "Other team is dead";
        return;
    }
    if(!otherTeam->characters[otherTeam->leader]->isAlive()){
        otherTeam->findNewLeader();
    }
    int target = otherTeam->findTarget(*(characters[leader])); // find target that close to leader
    if(target == -1) return;

    // Cowboys attack first
    for(int i = 0; i < cowboyCount; i++){
        if(characters[i]->isAlive()){
            Cowboy &cowboy = dynamic_cast<Cowboy&>(*(characters[i]));
            if(cowboy.hasBullets()){ 
                cowboy.shoot(*(otherTeam->characters[target]));
                target = checkTarget(target,otherTeam); // check if target is still alive or find new target
            }else{
                cowboy.reload();
            }
        }
    }

    //Ninjas attack
    int ninjaCount = count - cowboyCount;
    for(int i = 9; i > 9 - ninjaCount; i--){
        if(characters[i]->isAlive()){
            Ninja &ninja = dynamic_cast<Ninja&>(*(characters[i]));
            if(ninja.distance(*(otherTeam->characters[target])) <= 1){ // if target is close enough
                ninja.slash(*(otherTeam->characters[target]));
                target = checkTarget(target,otherTeam); // check if target is still alive or find new target
            }else{
                ninja.move(*(otherTeam->characters[target]));
            }
        }
    }
};

int Team::checkTarget(int target, Team *otherTeam){
    if(target == -1) return -1;
    if(!otherTeam->characters[target]->isAlive()){
        target = findTarget(*(characters[leader]));
    }
    return target;
}
