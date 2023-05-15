#include "Team.hpp"
#include <iostream>
#include <climits>
#include <stdexcept>

using namespace ariel;
using namespace std;

// Constructor
Team::Team(Character *leader)
{
    if (leader->isLeader())
    {
        throw runtime_error("Character is already a leader");
        return;
    }
    leader->setLeader();
    this->leader = leader;
    add(leader);
};
// Destructor
Team::~Team()
{
    
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
    {
        delete characters[i];
        characters[i] = NULL;
    }
    leader = NULL;
};
Team2::~Team2()
{
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
    {
        delete characters[i];
        characters[i] = NULL;
    }

    leader = NULL;
};
SmartTeam::~SmartTeam()
{
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
    {
        delete characters[i];
        characters[i] = NULL;
    }

    leader = NULL;
};
// Methods

// All cowboys are added to the beginning of the array, and all ninjas are added to the end of the array
void Team::add(Character *newCharacter)
{
    if (count == TEAM_SIZE)
    {
        throw runtime_error("Team is full");
        return;
    }
    else if (isAlreadyInTeam(newCharacter))
    {
        throw runtime_error("Character already in team");
        return;
    }
    else if (newCharacter->isInTeam())
    {
        throw runtime_error("Character is already in a team");
        return;
    }
    newCharacter->addedToTeam();
    Cowboy *c = dynamic_cast<Cowboy *>(newCharacter);
    Ninja *n = dynamic_cast<Ninja *>(newCharacter);
    if (c != NULL) // newCharacter is a Cowboy
    {
        characters[cowboyCount++] = newCharacter;
    }
    else if (n != NULL) // newCharacter is a Ninja
    {
        characters[TEAM_SIZE - 1 - (count - cowboyCount)] = newCharacter;
    }
    else
    {
        throw runtime_error("Invalid character type (not Cowboy or Ninja))");
        return;
    }

    count++;
};

bool Team::isAlreadyInTeam(Character *character)
{
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
        if (characters[i] == leader)
            cout << "LEADER";
        cout << "   " << characters[i]->print() << endl;
    }
    // Ninjas
    unsigned int ninjaCount = count - cowboyCount;
    for (unsigned int i = 9; i > 9 - ninjaCount; i--)
    {
        if (characters[i] == leader)
            cout << "LEADER";
        cout << "    " << characters[i]->print() << endl;
    }
    cout << " --------------------------------- " << endl;
};

void Team::findNewLeader()
{
    leader = findClosest(leader, this);
    leader->setLeader();
};

void Team::attack(Team *otherTeam)
{
    if (otherTeam == NULL)
    {
        throw invalid_argument("Cant attack NULL team");
        return;
    };
    if (this == otherTeam)
    {
        throw invalid_argument("Cant attack itself");
        return;
    };
    if (stillAlive() == 0)
    {
        throw runtime_error("Dead/empty team cant attack");
        return;
    };
    if (otherTeam->stillAlive() == 0)
    {
        throw runtime_error("Cant attack dead/empty team");
        return;
    };

    if (!leader->isAlive())
    {
        findNewLeader();
    }
    Character *target = findClosest(leader, otherTeam); // find target that close to leader
    if (!target)                                        // no target found
        return;

    // Cowboys attack first
    for (unsigned int i = 0; i < cowboyCount; i++)
    {
        if (characters[i]->isAlive())
        {
            Cowboy &cowboy = dynamic_cast<Cowboy &>(*(characters[i]));
            if (cowboy.hasboolets())
            {
                cowboy.shoot(target);
            }
            else
            {
                cowboy.reload();
            }
            target = checkTarget(target, otherTeam); // check if target is still alive or find a new target
            if (!target)
                return;
        }
    }

    // Ninjas attack
    unsigned int ninjaCount = count - cowboyCount;
    for (unsigned int i = 9; i > 9 - ninjaCount; i--)
    {
        if (characters[i]->isAlive())
        {
            Ninja &ninja = dynamic_cast<Ninja &>(*(characters[i]));
            if (ninja.distance(target) <= 1)
            {
                ninja.slash(target);
            }
            else
            {
                ninja.move(target);
            }
            target = checkTarget(target, otherTeam); // check if target is still alive or find a new target
            if (!target)
                return;
        }
    }
};

Character *Team::checkTarget(Character *target, Team *otherTeam)
{
    if (!target->isAlive())
    {
        target = findClosest(leader, otherTeam);
    }
    return target;
}

// Team2
Team2::Team2(Character *leader)
{
    if (leader->isLeader())
    {
        throw runtime_error("Already a leader");
        return;
    }
    leader->setLeader();
    this->leader = leader;
    this->add(leader);
};

void Team2::add(Character *newCharacter)
{
    if (count == TEAM_SIZE)
    {
        throw runtime_error("Team is full");
        return;
    }
    else if (isAlreadyInTeam(newCharacter))
    {
        throw runtime_error("Character already in team");
        return;
    }
    else if (newCharacter->isInTeam())
    {
        throw runtime_error("Character is already in a team");
        return;
    }
    Cowboy *c = dynamic_cast<Cowboy *>(newCharacter);
    Ninja *n = dynamic_cast<Ninja *>(newCharacter);
    if (c != NULL || n != NULL)
    {
        characters[count++] = newCharacter;
    }
    else
    {
        throw runtime_error("Invalid character type (not Cowboy or Ninja))");
        return;
    }
}

void Team2::print() const
{
    cout << " --------------------------------- " << endl;
    cout << "Team: " << endl;
    cout << "   Members: " << endl;

    // Cowboys
    for (unsigned int i = 0; i < count; i++)
    {
        if (characters[i] == leader)
            cout << "LEADER";
        cout << "   " << characters[i]->print() << endl;
    }
    cout << " --------------------------------- " << endl;
}

void Team2::attack(Team *enemies)
{
    if (enemies == NULL)
    {
        throw invalid_argument("Cant attack NULL team");
        return;
    };
    if (this == enemies)
    {
        throw invalid_argument("Cant attack itself");
        return;
    };
    if (stillAlive() == 0)
    {
        throw runtime_error("Dead/empty team cant attack");
        return;
    };
    if (enemies->stillAlive() == 0)
    {
        throw invalid_argument("Cant attack dead/empty team");
        return;
    };

    if (!leader->isAlive())
    {
        findNewLeader();
    }
    Character *target = findClosest(leader, enemies); // find target that close to leader
    if (!target)                                      // no target found
        return;

    for (unsigned int i = 0; i < count; i++)
    {
        if (characters[i]->isAlive())
        {
            Cowboy *c = dynamic_cast<Cowboy *>(characters[i]);
            Ninja *n = dynamic_cast<Ninja *>(characters[i]);
            if (c != NULL) //
            {
                if (c->hasboolets())
                {
                    c->shoot(target);
                }
                else
                {
                    c->reload();
                }
            }
            else if (n != NULL)
            {
                if (n->distance(target) <= 1)
                {
                    n->slash(target);
                }
                else
                {
                    n->move(target);
                }
            }
            target = checkTarget(target, enemies); // check if target is still alive or find a new target
            if (!target)
            {
                return;
            }
        }
    }
}

// Smart Team

SmartTeam::SmartTeam(Character *leader) : Team(leader){};

void SmartTeam::attack(Team *otherTeam)
{

    if (otherTeam == NULL)
    {
        throw invalid_argument("Cant attack NULL team");
        return;
    };
    if (this == otherTeam)
    {
        throw invalid_argument("Cant attack itself");
        return;
    };
    if (stillAlive() == 0)
    {
        throw runtime_error("Dead/empty team cant attack");
        return;
    };
    if (otherTeam->stillAlive() == 0)
    {
        throw invalid_argument("Cant attack dead/empty team");
        return;
    };

    // Ninjas attack first close enemies
    unsigned int ninjaCount = count - cowboyCount;
    for (unsigned int i = 9; i > 9 - ninjaCount; i--)
    {
        if (characters[i]->isAlive())
        {
            Ninja &ninja = dynamic_cast<Ninja &>(*(characters[i]));
            Character *closestEnemy = findClosest(characters[i], otherTeam);
            if (ninja.distance(closestEnemy) <= 1)
            {
                ninja.slash(closestEnemy);
            }
            else
            {
                ninja.move(closestEnemy);
            }
        }
    }

    // Cowboys attack enemies with lowest health
    for (unsigned int i = 0; i < cowboyCount; i++)
    {
        if (characters[i]->isAlive())
        {
            Cowboy &cowboy = dynamic_cast<Cowboy &>(*(characters[i]));
            Character *weakestEnemy = findWeakestEnemy(otherTeam);
            if (cowboy.hasboolets())
            {
                cowboy.shoot(weakestEnemy);
            }
            else
            {
                cowboy.reload();
            }
        }
    }
}

Character *Team::findClosest(Character *character, Team *team)
{
    Character *closest = NULL;
    int minDistance = INT_MAX;
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
    {
        if (team->characters[i] && team->characters[i]->isAlive())
        {
            int distance = character->distance(team->characters[i]);
            if (distance < minDistance)
            {
                minDistance = distance;
                closest = team->characters[i];
            }
        }
    }
    return closest;
}

Character *SmartTeam::findWeakestEnemy(Team *otherTeam)
{
    Character *weakestEnemy = NULL;
    int minHealth = INT_MAX;
    for (unsigned int i = 0; i < TEAM_SIZE; i++)
    {
        if (characters[i] && characters[i]->isAlive())
        {
            int health = otherTeam->characters[i]->getHealth();
            if (health < minHealth)
            {
                minHealth = health;
                weakestEnemy = characters[i];
            }
        }
    }
    return weakestEnemy;
}
