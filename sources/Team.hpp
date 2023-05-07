#include "Character.hpp"
#include <array>


namespace ariel
{
    const unsigned int TEAM_SIZE = 10;
    class Team
    {
    public:
        array<Character *, TEAM_SIZE> characters = {nullptr};
        unsigned int count = 0;
        Character* leader = nullptr;

        unsigned int cowboyCount = 0;

        bool isAlreadyInTeam(Character *character);   // check if the character is already in the team
        void findNewLeader();                         // find the closest alive character to the leader
        Character* checkTarget(Character* target, Team *otherTeam); // check if the target is alive and find another if not
        Character* findClosest(Character *character, Team *team); // find the closest alive character to the given character in given team

        Team(Character *leader);
        virtual void add(Character *character); // add a character to the team
        virtual void attack(Team *enemies);   // attack the other team
        int stillAlive() const; // return the number of alive characters
        virtual void print() const;     // print the team

        Team() = default;
        Team(const Team &) = default;
        Team &operator=(const Team &) = default;
        Team(Team &&) noexcept = default;
        Team &operator=(Team &&) noexcept = default;
        virtual ~Team();
    };

    class Team2: public Team{
        public:
        Team2(Character *leader);
        void add(Character *character) override; // add a character to the team
        void attack(Team *enemies) override;   // attack the other team
        void print() const override;     // print the team

        Team2() = default;
        Team2(const Team2 &) = default;
        Team2 &operator=(const Team2 &) = default;
        Team2(Team2 &&) noexcept = default;
        Team2 &operator=(Team2 &&) noexcept = default;
        ~Team2() override;
    };

    class SmartTeam: public Team{
        public:
        SmartTeam(Character *leader);
        void attack(Team *enemies) override;   // attack the other teamo
        Character* findWeakestEnemy(Team *enemies);

        SmartTeam() = default;
        SmartTeam(const SmartTeam &) = default;
        SmartTeam &operator=(const SmartTeam &) = default;
        SmartTeam(SmartTeam &&) noexcept = default;
        SmartTeam &operator=(SmartTeam &&) noexcept = default;
        ~SmartTeam() override;
    };
    
}