/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
using namespace std;

#include "sources/Team.hpp" //no need for other includes

using namespace ariel;

int main()
{
   Point a(32.3, 44), b(1.3, 3.5);
   assert(a.distance(b) == b.distance(a));
   Cowboy *tom = new Cowboy("Tom", a);
   OldNinja *sushi = new OldNinja("sushi", b);
   tom->shoot(*sushi);
   tom->print();

   sushi->print();
   sushi->move(*tom);
   sushi->print();
   sushi->slash(*tom);
   tom->print();

   Team team1(tom);
   team1.add(new YoungNinja("Yogi", Point(64, 57)));

   //team1.add(tom); //should throw tom is already in team a

   Team team2(sushi);
   team2.add(new TrainedNinja("Hikari", Point(12, 81)));

   team1.print();
   team2.print();

   while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
   {
      team1.attack(&team2);
      team2.attack(&team1);
      cout << "after round:" << endl;
      team1.print();
      team2.print();
   }

   if (team1.stillAlive() > 0)
      cout << "winner is a" << endl;
   else
      cout << "winner is b" << endl;

   return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.
}
