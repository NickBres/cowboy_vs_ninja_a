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
        double distance(Character *character) const; // distance between two characters
        void hit(int damage);                        // reduce health by damage
        string getName() const;
        Point getLocation() const;
        virtual string print() const;
        void setLocation(Point point);

        Character(const Character &) = default;
        Character &operator=(const Character &) = default;
        Character(Character &&) noexcept = default;
        Character &operator=(Character &&) noexcept = default;
        virtual ~Character() = default;
    };

    class Cowboy : public Character
    {
        int bullets = 0;

    public:
        Cowboy(string name, Point position);
        void shoot(Character *enemy); // shoot given character
        bool hasBullets() const;
        void reload(); // reload bullets
        string print() const override;
        
        Cowboy() = default;
        Cowboy(const Cowboy &) = default;
        Cowboy &operator=(const Cowboy &) = default;
        Cowboy(Cowboy &&) noexcept = default;
        Cowboy &operator=(Cowboy &&) noexcept = default;
        ~Cowboy() override = default;
    };

    class Ninja : public Character
    {
        int speed = 0;

    public:
        Ninja(string name, int health, Point position, int speed = 0);
        void move(Character *enemy);  // move towards given character
        void slash(Character *enemy); // slash given character
        string print() const override;
        
        Ninja() = default;
        Ninja(const Ninja &) = default;
        Ninja &operator=(const Ninja &) = default;
        Ninja(Ninja &&) noexcept = default;
        Ninja &operator=(Ninja &&) noexcept = default;
        ~Ninja() override = default;
    };

    class YoungNinja : public Ninja
    {
    public:
        YoungNinja(string name, Point position);
        
        YoungNinja() = default;
        YoungNinja(const YoungNinja &) = default;
        YoungNinja &operator=(const YoungNinja &) = default;
        YoungNinja(YoungNinja &&) noexcept = default;
        YoungNinja &operator=(YoungNinja &&) noexcept = default;
        ~YoungNinja() override = default;
    };

    class OldNinja : public Ninja
    {
    public:
        OldNinja(string name, Point position);
        
        OldNinja() = default;
        OldNinja(const OldNinja &) = default;
        OldNinja &operator=(const OldNinja &) = default;
        OldNinja(OldNinja &&) noexcept = default;
        OldNinja &operator=(OldNinja &&) noexcept = default;
        ~OldNinja() override = default;
    };

    class TrainedNinja : public Ninja
    {
    public:
        TrainedNinja(string name, Point position);
        
        TrainedNinja() = default;
        TrainedNinja(const TrainedNinja &) = default;
        TrainedNinja &operator=(const TrainedNinja &) = default;
        TrainedNinja(TrainedNinja &&) noexcept = default;
        TrainedNinja &operator=(TrainedNinja &&) noexcept = default;
        ~TrainedNinja() override = default;
    };

} // namespace ariel