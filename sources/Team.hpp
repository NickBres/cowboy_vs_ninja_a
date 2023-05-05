#include "Character.hpp"
#include <array>


namespace ariel
{
    const unsigned int TEAM_SIZE = 10;
    class Team
    {
        array<Character *, TEAM_SIZE> characters;
        unsigned int count;
        unsigned int leader;

        unsigned int cowboyCount;

        bool isAlreadyInTeam(Character *character);   // check if the character is already in the team
        void findNewLeader();                         // find the closest alive character to the leader
        unsigned int findTarget(Character *leader);             // find the closest alive character to the given character
        unsigned int checkTarget(unsigned int target, Team *otherTeam); // check if the target is alive and find another if not

    public:
        Team(Character *leader);
        void add(Character *character); // add a character to the team
        void attack(Team *enemies);   // attack the other team
        int stillAlive() const; // return the number of alive characters
        void print() const;     // print the team
        //~Team();
    };
}