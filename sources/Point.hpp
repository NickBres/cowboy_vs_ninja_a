#include <string>

namespace ariel
{
    class Point
    {
        double cor_x, cor_y;

    public:
        Point(double cor_x = 0, double cor_y = 0);
        double distance(Point point) const; // distance between two points
        std::string print() const;
        double getX() const;
        double getY() const;
        void setX(double cor_x);
        void setY(double cor_y);
        static void moveTowards(Point &point1, Point &point2, double dist); // move p towards q by dist
    };
}