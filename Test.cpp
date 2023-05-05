#include "doctest.h"
#include <iostream>
#include <sstream>

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

    CHECK_THROWS(Point::moveTowards(p1, p2, -1.0)); // distance cannot be negative
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
    
    CHECK_THROWS(c2.shoot(&c1)); // c2 is dead
    CHECK_THROWS(c2.reload()); 

    CHECK_THROWS(c1.shoot(&c1)); // cannot shoot yourself
    CHECK_THROWS(c1.shoot(NULL)); // cannot shoot NULL
}

TEST_CASE("Cowboy/Ninja print test")
{
    Cowboy c1("John", Point(3, 4));
    CHECK(c1.print() == "C John HP: 110 POS: (3.000,4.000) AMMO: 6");
    c1.hit(110);
    CHECK(c1.print() == "C (John) POS: (3.000,4.000)");

    YoungNinja n1("Bruce", Point(1.2312, 2.3412));
    CHECK(n1.print() == "N Bruce HP: 100 POS: (1.231,2.341) SPEED: 14");
    n1.hit(100);
    CHECK(n1.print() == "N (Bruce) POS: (1.231,2.341)");
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

    n1.hit(100);
    CHECK_THROWS(n1.move(&n2)); // n1 is dead
    CHECK_THROWS(n2.move(NULL)); // cannot move to NULL
}

TEST_CASE("Ninja slash test")
{
    Ninja n1("Bruce", 100, Point(1, 2), 3); // 13 damage by default
    Ninja n2("Chuck", 10, Point(3, 4), 2);

    n1.slash(&n2); // will not slash because n2 is too far instead will move towards n2
    CHECK(n1.getLocation().getX() == doctest::Approx(3));
    CHECK(n1.getLocation().getY() == doctest::Approx(4));
    CHECK(n2.isAlive() == true);

    n1.slash(&n2); // will slash because n2 is close enough
    CHECK(n2.isAlive() == false);

    CHECK_THROWS(n2.slash(&n1)); // n2 is dead
    CHECK_THROWS(n1.slash(NULL)); // cannot slash NULL
    CHECK_THROWS(n1.slash(&n1)); // cannot slash yourself

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

TEST_CASE("Ninjas move different by type test")
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

    //cant add same character twice
    CHECK_THROWS(team.add(&cowboy));
    Character c("c", 100, Point(0, 0));
    CHECK_THROWS(team.add(&c)); // c is not a cowboy or ninja

    // add 8 more characters
    Cowboy c1("c1", Point(0, 0));
    Cowboy c2("c2", Point(0, 0));
    Cowboy c3("c3", Point(0, 0));
    Cowboy c4("c4", Point(0, 0));
    Cowboy c5("c5", Point(0, 0));
    Cowboy c6("c6", Point(0, 0));
    Cowboy c7("c7", Point(0, 0));
    Cowboy c8("c8", Point(0, 0));
    Cowboy c9("c9", Point(0, 0));

    team.add(&c1);
    team.add(&c2);
    team.add(&c3);
    team.add(&c4);
    team.add(&c5);
    team.add(&c6);
    team.add(&c7);
    team.add(&c8);

    CHECK_THROWS(team.add(&c9)); // team is full
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

    CHECK_THROWS(team.attack(&team)); // cant attack yourself
    CHECK_THROWS(team.attack(NULL)); // cant attack NULL

    Team team2(&cowboy2); // cowboy2 is the leader
    team2.add(&oldNinja);
    team2.add(&trainedNinja);

    team.attack(&team2);
    CHECK(team2.stillAlive() == 3);

    while (team2.stillAlive() > 0) {
        team.attack(&team2);
    }

    CHECK_THROWS(team.attack(&team2)); // cant attack dead team
    CHECK_THROWS(team2.attack(&team)); // dead team cant attack
}

TEST_CASE("Team and Team2 have different print output")
{
    // Create some characters for team
    Cowboy c1("Cowboy1", Point(0, 0));
    YoungNinja n1("Ninja1", Point(0, 0));
    Cowboy c2("Cowboy2", Point(0, 0));
    TrainedNinja n2("Ninja2", Point(0, 0));

    // Create some characters for team2
    Cowboy c1_team2("Cowboy1", Point(0, 0));
    YoungNinja n1_team2("Ninja1", Point(0, 0));
    Cowboy c2_team2("Cowboy2", Point(0, 0));
    TrainedNinja n2_team2("Ninja2", Point(0, 0));

    // Create teams
    Team team(&c1);
    Team2 team2(&c1_team2);

    // Add characters to the teams
    team.add(&n1);
    team.add(&c2);
    team.add(&n2);

    team2.add(&n1_team2);
    team2.add(&c2_team2);
    team2.add(&n2_team2);

    // Create string streams to capture the print output
    std::stringstream team_output;
    std::stringstream team2_output;

    // Redirect the standard output for each team's print() method
    {
        std::streambuf *old_cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(team_output.rdbuf());
        team.print();
        std::cout.rdbuf(old_cout_buf);
    }

    {
        std::streambuf *old_cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(team2_output.rdbuf());
        team2.print();
        std::cout.rdbuf(old_cout_buf);
    }

    // Compare the print outputs
    CHECK(team_output.str() != team2_output.str());

    //team.print();
    //team2.print();
}


