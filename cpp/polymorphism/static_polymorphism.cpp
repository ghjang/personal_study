#include "static_polymorphism.h"

#include <cstddef>
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>

#include "boost/variant.hpp"


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

    class Circle
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
        double area() const
        {
            return M_PI * radius_ * radius_;
        }

        double perimeter() const
        {
            return 2 * M_PI * radius_;
        }
    };

    class Square
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
        double area() const
        {
            return sideLength_ * sideLength_;
        }

        double perimeter() const
        {
            return 4 * sideLength_;
        }
    };

    template <typename Shape>
    void runShapeTest()
    {
        // homogeneous object creation
        using ShapePtr = std::shared_ptr<Shape>;
        using std::make_shared;
        std::vector<ShapePtr> sv = {
                make_shared<Shape>(Point(), 5),
                make_shared<Shape>(Point(), 10)
        };

        // normal function call
        for (auto s : sv) {
            std::cout << "area: " << s->area() << '\n'
                      << "perimeter: " << s->perimeter()
                      << std::endl;
        }
    }

    struct CallArea: public boost::static_visitor<double>
    {
        template <typename T>
        double operator () (T s) const
        {
            return s->area();
        }
    };

    struct CallPerimeter: public boost::static_visitor<double>
    {
        template <typename T>
        double operator () (T s) const
        {
            return s->perimeter();
        }
    };

    void runShapeTestByUsingVariant()
    {
        // heterogeneous object creation
        using CirclePtr = std::shared_ptr<Circle>;
        using SquarePtr = std::shared_ptr<Square>;
        using Shape = boost::variant<CirclePtr, SquarePtr>;
        using std::make_shared;
        std::vector<Shape> sv = {
                make_shared<Circle>(Point(), 5),
                make_shared<Square>(Point(), 5),
                make_shared<Circle>(Point(), 10)
        };

        // Boost.Variant visitor call
        for (auto s : sv) {
            std::cout << "area: " << boost::apply_visitor(CallArea(), s) << '\n'
                      << "perimeter: " << boost::apply_visitor(CallPerimeter(), s)
                      << std::endl;
        }
    }
} // un-named namespace


void runStaticPolymorphismTest()
{
    //
    runShapeTest<Circle>();
    runShapeTest<Square>();

    // with Boost.Variant
    std::cout << "-- boost::variant --" << std::endl;
    runShapeTestByUsingVariant();
}

