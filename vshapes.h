#ifndef _vshapes_h_
#define _vshapes_h_

#include "common.h"

namespace virtual_shapes {

class shape {
    public:
       virtual ~shape() {}

       virtual void draw() = 0;
       virtual void rotate(double) = 0;

       virtual double perimeter() = 0;
       virtual double area() = 0; 
};

class circle: public shape {
    public:
        circle(double r) : _r(r) {}
        ~circle() = default;

        circle(const circle&) = default;
        circle(circle&&) = default;
        circle& operator=(const circle&) = default;
        circle& operator=(circle&&) = default;

        virtual void draw(){}
        virtual void rotate(double){}

        virtual double perimeter() { return 2 * pi * _r;}
        virtual double area()  { return pi * _r * _r;}
    private:
        double _r;
};

class rectangle: public shape {
    public:
        rectangle(double a, double b) : _a(a), _b(b) {}
        ~rectangle() = default;

        rectangle(const rectangle&) = default;
        rectangle(rectangle&&) = default;
        rectangle& operator=(const rectangle&) =  default;
        rectangle& operator=(rectangle&&) = default;

        virtual void draw(){}
        virtual void rotate(double){}

        virtual double perimeter() { return 2 * (_a + _b);}
        virtual double area()  { return _a * _b;}
    private:
        double _a;
        double _b;
};

class triangle: public shape {
    public:
        triangle(double a, double b, double c, double h) : _a(a), _b(b), _c(c), _h(h) {}
        ~triangle() = default;

        triangle(const triangle&) = default;
        triangle(triangle&&) = default;
        triangle& operator=(const triangle&) =  default;
        triangle& operator=(triangle&&) = default;

        virtual void draw(){}
        virtual void rotate(double){}

        virtual double perimeter() { return _a + _b + _c;}
        virtual double area()  { return (_a * _h) / 2;}
    private:
        double _a;
        double _b;
        double _c;
        double _h;
};

}
#endif