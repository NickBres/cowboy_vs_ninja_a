#include "Point.hpp"
#include <string>

using namespace std;

namespace ariel
{

    class Character
    {
        Point position;
        int health;
        string name;

    public:
        Character(string name = "", int health = 0, Point position = Point(0, 0));
        bool isAlive() const;
        double distance(Character c) const;
        void hit(int damage);
        string getName() const;
        Point getLocation() const;
        virtual void print() const;
    };

    class Cowboy : public Character
    {
        int bullets;

    public:
        Cowboy(string name, Point position);
        void shoot(Character &c);
        bool hasBullets() const;
        void reload();
        virtual void print() const;
    };

    class Ninja : public Character
    {
        int speed;

    public:
        Ninja(string name, int health, Point position, int speed = 0);
        void move(Character &c);
        void slash(Character &c);
        virtual void print() const;
    };

    class YoungNinja : public Ninja
    {
    public:
        YoungNinja(string name, Point position);
        virtual void print() const;
    };

    class OldNinja : public Ninja
    {
    public:
        OldNinja(string name, Point position);
        virtual void print() const;
    };

    class TrainedNinja : public Ninja
    {
    public:
        TrainedNinja(string name, Point position);
        virtual void print() const;
    };

} // namespace ariel