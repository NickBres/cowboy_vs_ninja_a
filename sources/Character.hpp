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
        double distance(Character c) const; // distance between two characters
        void hit(int damage); // reduce health by damage
        string getName() const;
        Point getLocation() const;
        virtual void print() const;
        void setLocation(Point p);
    };

    class Cowboy : public Character
    {
        int bullets;

    public:
        Cowboy(string name, Point position);
        void shoot(Character &c); // shoot given character
        bool hasBullets() const;
        void reload(); // reload bullets
        virtual void print() const;
    };

    class Ninja : public Character
    {
        int speed;

    public:
        Ninja(string name, int health, Point position, int speed = 0);
        void move(Character &c); // move towards given character
        void slash(Character &c); // slash given character
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