#include "Character.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace ariel;

// Constructors
Character::Character(string name, int health, Point position) : name(name), health(health), position(position){};
Cowboy::Cowboy(string name, Point position) : Character(name, 110, position), bullets(6){};
Ninja::Ninja(string name, int health, Point position, int speed) : Character(name, health, position), speed(speed){};
YoungNinja::YoungNinja(string name, Point position) : Ninja(name, 100, position, 14){};
OldNinja::OldNinja(string name, Point position) : Ninja(name, 150, position, 8){};
TrainedNinja::TrainedNinja(string name, Point position) : Ninja(name, 120, position, 12){};


// Character methods
void Character::addedToTeam(){
    this->inTeam = true;
}

void Character::setLeader(){
    this->leader = true;
}

bool Character::isInTeam() const{
    return this->inTeam;
}

bool Character::isLeader() const{
    return this->leader;
}

int Character::getHealth() const
{
    return health;
}

bool Character::isAlive() const
{
    return health > 0;
}
double Character::distance(Character *character) const
{
    return position.distance(character->getLocation());
}
void Character::hit(int damage)
{
    if(damage < 0)
    {
        throw invalid_argument("Negative damage");
    }
    if (isAlive())
        health -= damage; // deal damage only if alive
    if (health < 0)
        health = 0; // health can't be negative
}
string Character::getName() const
{
    return name;
}
Point Character::getLocation() const
{
    return position;
}
string Character::print() const
{
    string data = "";
    if (isAlive())
        data += name + " HP: " + to_string(health);
    else
        data += "(" + name + ")";
    data += " POS: " + position.print();
    return data;
}
void Character::setLocation(Point point)
{
    position = point;
}

// Cowboy methods
void Cowboy::shoot(Character *enemy)
{
    if (enemy == NULL)
    {
        throw invalid_argument("NULL enemy");
    }
    if (this == enemy)
    {
        throw runtime_error("Cowboys can't shoot themselves");
    }

    if(!isAlive())
    {
        throw runtime_error("Dead cowboys can't shoot");
    }
    if(!enemy->isAlive()){
        throw runtime_error("Cowboys can't shoot dead enemies");
    }
    if (hasboolets())
    {
        bullets--;
        enemy->hit(10);
    }
    // else if (isAlive())
    // { // no bullets
    //    reload();
    // }
}
bool Cowboy::hasboolets() const
{
    return bullets > 0;
}
void Cowboy::reload()
{
    if (!isAlive())
        throw runtime_error("Dead cowboys can't reload");
    bullets = 6;
}
string Cowboy::print() const
{
    string data = "C " + Character::print();
    if (isAlive())
    {
        data += " AMMO: " + to_string(bullets);
    }
    return data;
}

// Ninja methods
void Ninja::move(Character *enemy)
{
    if (enemy == NULL)
    {
        throw invalid_argument("NULL enemy");
    }
    if (isAlive())
    {
        Point enemyPos = enemy->getLocation();
        Point myPos = getLocation();
        setLocation(Point::moveTowards(myPos,enemyPos,speed));                         // set new position
    }
    else
    {
        throw runtime_error("Dead ninjas can't move");
    }
}
void Ninja::slash(Character *enemy)
{
    if (enemy == NULL)
    {
        throw invalid_argument("NULL enemy");
    }
    if (this == enemy)
    {
        throw runtime_error("Ninjas can't slash themselves");
    }

    if(!isAlive())
    {
        throw runtime_error("Dead ninjas can't slash");
    }
    if(!enemy->isAlive()){
        throw runtime_error("Ninjas can't slash dead enemies");
    }
    if (distance(enemy) <= 1)
    {
        enemy->hit(40);
    }
    // else
    // { // too far
    //     move(enemy);
    // }
}

string Ninja::print() const
{
    string data = "N " + Character::print();
    if (isAlive())
    {
        data += " SPEED: " + to_string(speed);
    }
    return data;
}
