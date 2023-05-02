#include "Point.hpp"
#include <cmath>
#include <iostream>

using namespace ariel;
using namespace std;

double Point::distance(Point p) const{
    return sqrt(pow(x-p.getX(),2)+pow(y-p.getY(),2));
}

void Point::print() const{
    cout << "(" << x << "," << y << ")";
}

double Point::getX() const{
    return x;
}

double Point::getY() const{
    return y;
}

void Point::setX(double x){
    this->x = x;
}

void Point::setY(double y){
    this->y = y;
}

void Point::moveTowards(Point &p, Point &q, double dist){
    double d = p.distance(q);
    if(d <= dist){
        p = q;
    }
    else{
        double dx = q.getX() - p.getX();
        double dy = q.getY() - p.getY();
        double ratio = dist/d;
        p.setX(p.getX() + dx*ratio);
        p.setY(p.getY() + dy*ratio);
    }
}