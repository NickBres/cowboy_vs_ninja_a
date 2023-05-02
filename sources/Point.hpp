namespace ariel
{
    class Point
    {
        double x, y;

    public:
        Point(double x = 0, double y = 0);
        double distance(Point p) const;
        void print() const;
        double getX() const;
        double getY() const;
        void setX(double x);
        void setY(double y);
        static void moveTowards(Point &p, Point &q, double dist);
    };
}