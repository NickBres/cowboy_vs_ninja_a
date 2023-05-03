#include "Character.hpp"

namespace ariel
{
    class Team
    {
        Character *characters[10];
        int count;
        int leader;

        int cowboyCount;

        bool isAlreadyInTeam(Character *character);   // check if the character is already in the team
        void findNewLeader();                         // find the closest alive character to the leader
        int findTarget(Character leader);             // find the closest alive character to the given character
        int checkTarget(int target, Team *otherTeam); // check if the target is alive and find another if not

    public:
        Team(Character *leader);
        void add(Character *c); // add a character to the team
        void attack(Team *t);   // attack the other team
        int stillAlive() const; // return the number of alive characters
        void print() const;     // print the team
        ~Team();
    };
}