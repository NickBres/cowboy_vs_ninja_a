#include "Point.hpp"
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>

using namespace ariel;
using namespace std;

Point::Point(double cor_x, double cor_y) : cor_x(cor_x), cor_y(cor_y){};

double Point::distance(Point p) const{
    return sqrt(pow(cor_x-p.getX(),2)+pow(cor_y-p.getY(),2));
}

string Point::print() const{
    ostringstream out;
    out << fixed << setprecision(3) << "(" << cor_x << "," << cor_y << ")";
    return out.str();
}


double Point::getX() const{
    return cor_x;
}

double Point::getY() const{
    return cor_y;
}

void Point::setX(double cor_x){
    this->cor_x = cor_x;
}

void Point::setY(double cor_y){
    this->cor_y = cor_y;
}

void Point::moveTowards(Point &point1, Point &point2, double dist){
    if(dist < 0){
        throw runtime_error( "distance cannot be negative");
    }
    double d = point1.distance(point2);
    if(d <= dist){
        point1 = point2;
    }
    else{
        double dx = point2.getX() - point1.getX();
        double dy = point2.getY() - point1.getY();
        double ratio = dist/d;
        point1.setX(point1.getX() + dx*ratio);
        point1.setY(point1.getY() + dy*ratio);
    }
}