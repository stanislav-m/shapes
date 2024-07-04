#ifndef _mpark_shapes_h_
#define _mpark_shapes_h_

#include "common.h"
#include <mpark/variant.hpp>

namespace mpark_shapes {

class circle {
    public:
        circle(double r) : _r(r) {}
        ~circle() = default;
 
        circle(const circle&) = default;
        circle(circle&&) = default;
        circle& operator=(const circle&) = default;
        circle& operator=(circle&&) = default;

       double get_r() const { return _r; }
    private:
        double _r;
};

class rectangle {
    public:
        rectangle(double a, double b) : _a(a), _b(b) {}
        ~rectangle() = default;

        rectangle(const rectangle&) = default;
        rectangle(rectangle&&) = default;
        rectangle& operator=(const rectangle&) =  default;
        rectangle& operator=(rectangle&&) = default;

       double get_a() const { return _a; }
       double get_b() const { return _b; }
    private:
        double _a;
        double _b;
};

class triangle {
    public:
        triangle(double a, double b, double c, double h) : _a(a), _b(b), _c(c), _h(h) {}
        ~triangle() = default;

        triangle(const triangle&) = default;
        triangle(triangle&&) = default;
        triangle& operator=(const triangle&) =  default;
        triangle& operator=(triangle&&) = default;

       double get_a() const { return _a; }
       double get_b() const { return _b; }
       double get_c() const { return _c; }
       double get_h() const { return _h; }
    private:
        double _a;
        double _b;
        double _c;
        double _h;
};


////// circle free functions
void draw(const circle& shape) {}
void rotate(const circle& shape, double){}
double perimeter(const circle& shape) {
    auto r = shape.get_r();
    return 2 * pi * r;
}
double area(const circle& shape) {
    auto r = shape.get_r();
    return pi * r * r;
}

////// rectangle free functions
void draw(const rectangle& shape) {}
void rotate(const rectangle& shape, double){}
double perimeter(const rectangle& shape) {
    auto a = shape.get_a();
    auto b = shape.get_b();
    return 2*(a + b);
}
double area(const rectangle& shape) {
    auto a = shape.get_a();
    auto b = shape.get_b();
    return (a * b) / 2;
}

////// triangle free functions
void draw(const triangle& shape) {}
void rotate(const triangle& shape, double){}
double perimeter(const triangle& shape) {
    auto a = shape.get_a();
    auto b = shape.get_b();
    auto c = shape.get_c();
    return a + b + c;
}
double area(const triangle& shape) {
    auto a = shape.get_a();
    auto h = shape.get_h();
    return (a * h) / 2;
}

struct draw_visitor {
    template <typename T>
    void operator()(const T& sh) { draw(sh); }
};

struct perimeter_visitor {
    template <typename T>
    double operator()(const T& sh) { return perimeter(sh); }
};

struct area_visitor {
    template <typename T>
    double operator()(const T& sh) { return area(sh); }
};

class shape {
    public:
        template <typename T>
        shape(T sh) : _data(std::move(sh)) {}

        shape(const shape& other) = default;
        shape& operator=(const shape& other) = default;

        shape(shape&&) = default;
        shape& operator=(shape&&) = default;

        void do_draw() const {  mpark::visit(draw_visitor{}, _data);  }
        double do_perimeter() const {  return mpark::visit(perimeter_visitor{}, _data); }
        double do_area() const { return mpark::visit(area_visitor{}, _data); }

    private:
        mpark::variant<circle, rectangle, triangle> _data;
};

}
#endif
