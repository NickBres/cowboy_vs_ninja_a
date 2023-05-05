#include "doctest.h"

#include "sources/Team.hpp"

using namespace ariel;

TEST_CASE("Point distance test")
{
    Point p1(0, 0);
    Point p2(3, 4);
    CHECK(p1.distance(p2) == 5.0);
    CHECK(p2.distance(p1) == 5.0);
}

TEST_CASE("Point moveTowards test")
{
    Point p1(0, 0);
    Point p2(3, 4);
    Point::moveTowards(p1, p2, 2.0);
    CHECK(p1.getX() == doctest::Approx(1.2));
    CHECK(p1.getY() == doctest::Approx(1.6));
    Point::moveTowards(p1, p2, 10.0);
    CHECK(p1.getX() == doctest::Approx(3.0));
    CHECK(p1.getY() == doctest::Approx(4.0));
}

TEST_CASE("Character constructor test")
{
    Character c1("Alice", 100, Point(1, 2));
    CHECK(c1.getName() == "Alice");
    CHECK(c1.isAlive() == true);
    CHECK(c1.getLocation().getX() == 1);
    CHECK(c1.getLocation().getY() == 2);

    Character c2;
    CHECK(c2.getName() == "");
    CHECK(c2.isAlive() == false);
    CHECK(c2.getLocation().getX() == 0);
    CHECK(c2.getLocation().getY() == 0);
}

TEST_CASE("Character hit test")
{
    Character c1("Alice", 100, Point(1, 2));
    c1.hit(50);
    CHECK(c1.isAlive() == true);

    c1.hit(60);
    CHECK(c1.isAlive() == false);
}

TEST_CASE("Character distance test")
{
    Character c1("Alice", 100, Point(1, 2));
    Character c2("Bob", 100, Point(4, 6));
    CHECK(c1.distance(&c2) == doctest::Approx(5.0));
    CHECK(c2.distance(&c1) == doctest::Approx(5.0));
}

TEST_CASE("Cowboy constructor test")
{
    Cowboy c1("John", Point(3, 4));
    CHECK(c1.getName() == "John");
    CHECK(c1.isAlive() == true);
    CHECK(c1.getLocation().getX() == 3);
    CHECK(c1.getLocation().getY() == 4);
    CHECK(c1.hasBullets() == true);
}

TEST_CASE("Cowboy shoot test")
{
    Cowboy c1("John", Point(0, 0)); // 6 bullets by default
    Cowboy c2("Mary", Point(3, 4)); // 120 hp by default
    for (int i = 0; i < 6; i++)
    { // shoot all bullets
        c1.shoot(&c2);
    }
    CHECK(c1.hasBullets() == false);
    CHECK(c2.isAlive() == true);
    for(int i = 0; i < 5; i++)  // try to shoot 5 times
    {
        c1.shoot(&c2);
    }
    CHECK(c1.hasBullets() == true); // because c1 had no bullets one shot will reload instead of shoot
    CHECK(c2.isAlive() == true);
    CHECK(c1.hasBullets() == true);
    c1.shoot(&c2); // final shot
    CHECK(c2.isAlive() == false);
}

TEST_CASE("Ninja constructor test")
{
    Ninja n1("Bruce", 100, Point(1, 2), 3);
    CHECK(n1.getName() == "Bruce");
    CHECK(n1.isAlive() == true);
    CHECK(n1.getLocation().getX() == 1);
    CHECK(n1.getLocation().getY() == 2);
}

TEST_CASE("Ninja move test")
{
    Ninja n1("Bruce", 100, Point(1, 2), 3);
    Ninja n2("Chuck", 100, Point(5, 6), 2);
    n1.move(&n2);
    CHECK(n1.getLocation().getX() == doctest::Approx(3.1213));
    CHECK(n1.getLocation().getY() == doctest::Approx(4.1213));
}

TEST_CASE("YoungNinja constructor test")
{
    YoungNinja n1("Billy", Point(1, 2));
    CHECK(n1.getName() == "Billy");
    CHECK(n1.isAlive() == true);
    CHECK(n1.getLocation().getX() == 1);
    CHECK(n1.getLocation().getY() == 2);
}

TEST_CASE("OldNinja constructor test")
{
    OldNinja n1("Bobby", Point(1, 2));
    CHECK(n1.getName() == "Bobby");
    CHECK(n1.isAlive() == true);
    CHECK(n1.getLocation().getX() == 1);
    CHECK(n1.getLocation().getY() == 2);
}

TEST_CASE("TrainedNinja constructor test")
{
    TrainedNinja n1("Bruce Wayne", Point(1, 2));
    CHECK(n1.getName() == "Bruce Wayne");
    CHECK(n1.isAlive() == true);
    CHECK(n1.getLocation().getX() == 1);
    CHECK(n1.getLocation().getY() == 2);
}

TEST_CASE("Ninjas move test")
{
    YoungNinja n1("Billy", Point(1, 2)); // move speed 14 by default
    OldNinja n2("Bobby", Point(1, 2)); // move speed 12 by default
    TrainedNinja n3("Bruce Wayne", Point(1, 2));  // move speed 12 by default

    Character c("Alice", 100, Point(100, 100));

    n1.move(&c);
    CHECK(n1.getLocation().getX() == doctest::Approx(10.9496));
    CHECK(n1.getLocation().getY() == doctest::Approx(11.8491));

    n2.move(&c);
    CHECK(n2.getLocation().getX() == doctest::Approx(9.5282));
    CHECK(n2.getLocation().getY() == doctest::Approx(10.442));

    n3.move(&c);
    CHECK(n3.getLocation().getX() == n2.getLocation().getX());
    CHECK(n3.getLocation().getY() == n2.getLocation().getY());    
}

TEST_CASE("add character to team") {
    // add cowboy to team
    Cowboy cowboy("cowboy", Point(0, 0));
    Team team(&cowboy);
    CHECK(team.stillAlive() == 1);

    // add ninja to team
    YoungNinja ninja("ninja", Point(0, 0));
    team.add(&ninja);
    CHECK(team.stillAlive() == 2);

    // add ninja with same name as cowboy to team
    CHECK_THROWS(team.add(&cowboy));
}

TEST_CASE("attack other team") {
    //Setup team
    Cowboy cowboy("Barak", Point(0, 0));
    YoungNinja ninja("Naruto", Point(0, 0));
    OldNinja oldNinja("Sasuke", Point(0, 0));
    TrainedNinja trainedNinja("Kakashi", Point(0, 0));
    Cowboy cowboy2("Donald", Point(0, 0));

    Team team(&cowboy); // cowboy is the leader
    team.add(&ninja);

    Team team2(&cowboy2); // cowboy2 is the leader
    team2.add(&oldNinja);
    team2.add(&trainedNinja);

    team.attack(&team2);
    CHECK(team2.stillAlive() == 3);
}