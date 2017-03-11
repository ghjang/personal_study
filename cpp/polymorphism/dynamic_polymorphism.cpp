#include "dynamic_polymorphism.h"

#include <cstddef>
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>


namespace
{
   struct Point
   {
       Point(int x, int y)
           : x_(x), y_(y)
       { }

       Point()
           : Point(0, 0)
       { }

       double x_;
       double y_;
   };

   struct Shape
   {
       virtual double area() const = 0;
       virtual double perimeter() const = 0;
   };

    class Circle: public Shape
    {
    private:
        Point centerPoint_;
        double radius_;

    public:
        Circle(Point pt, double r)
            : centerPoint_(pt), radius_(r)
        { }

        Circle()
            : Circle(Point(), 0)
        { }

    public:
        double area() const override
        {
            return M_PI * radius_ * radius_;
        }

        double perimeter() const override
        {
            return 2 * M_PI * radius_;
        }
    };

    class Square: public Shape
    {
    private:
        Point leftTop_;
        double sideLength_;

    public:
        Square(Point lt, double len)
            : leftTop_(lt), sideLength_(len)
        { }

        Square()
            : Square(Point(), 0)
        { }

    public:
        double area() const override
        {
            return sideLength_ * sideLength_;
        }

        double perimeter() const override
        {
            return 4 * sideLength_;
        }
    };
} // un-named namespace


void runDynamicPolymorphismTest()
{
    // heterogeneous object creation
    using ShapePtr = std::shared_ptr<Shape>;
    using std::make_shared;
    std::vector<ShapePtr> sv = {
            make_shared<Circle>(Point(), 5),
            make_shared<Square>(Point(), 5),
            make_shared<Circle>(Point(), 10)
    };

    // virtual function call
    for (auto s : sv) {
        std::cout << "area: " << s->area() << '\n'
                  << "perimeter: " << s->perimeter()
                  << std::endl;
    }
}

