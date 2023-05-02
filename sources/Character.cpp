#include "Character.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace ariel;

// Constructors
Character::Character(string name, int health, Point position) : name(name), health(health), position(position){};
Cowboy::Cowboy(string name, Point position) : Character(name, 110, position), bullets(6){};
Ninja::Ninja(string name, int health, Point position, int speed) : Character(name, health, position), speed(speed){};
YoungNinja::YoungNinja(string name, Point position) : Ninja(name, 100, position, 14){};
OldNinja::OldNinja(string name, Point position) : Ninja(name, 150, position, 12){};
TrainedNinja::TrainedNinja(string name, Point position) : Ninja(name, 120, position, 12){};

// Character methods
bool Character::isAlive() const
{
    return health > 0;
}
double Character::distance(Character c) const
{
    return position.distance(c.getLocation());
}
void Character::hit(int damage)
{
    if (isAlive()) health -= damage; // deal damage only if alive
    if (health < 0) health = 0;     // health can't be negative
}
string Character::getName() const
{
    return name;
}
Point Character::getLocation() const
{
    return position;
}
void Character::print() const
{
    cout << name << " HP: " << health << " POS: ";
    position.print();
}
void Character::setLocation(Point p)
{
    position = p;
}

// Cowboy methods
void Cowboy::shoot(Character &enemy)
{
    if(isAlive() && hasBullets()){
        bullets--;
        enemy.hit(10);
    }
}
bool Cowboy::hasBullets() const
{
    return bullets > 0;
}
void Cowboy::reload()
{
    bullets = 6;
}
void Cowboy::print() const
{
    cout << "Cowboy ";
    Character::print();
    cout << " BULLETS: " << bullets << endl;
}

// Ninja methods
void Ninja::move(Character &enemy)
{
    if (isAlive())
    {
        Point enemyPos = enemy.getLocation();
        Point myPos = getLocation();
        Point::moveTowards(myPos, enemyPos, speed); // calculate new position
        setLocation(myPos);                        // set new position
    }
}
void Ninja::slash(Character &enemy)
{
    if (isAlive() && distance(enemy) <= 1)
    {
        enemy.hit(13);
    }
}