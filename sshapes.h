#ifndef _sshapes_h_
#define _sshapes_h_

#include "common.h"
#include <memory>

namespace static_shapes {

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

class shape {
    public:
        template <typename T>
        shape(T sh) : _pImpl(std::make_unique<ShapeConcept<T>>(std::move(sh))) {}

        shape(const shape& other) {
            _pImpl = other._pImpl->clone();
        }

        shape& operator=(const shape& other) {
            shape tmp(other);
            std::swap(_pImpl, tmp._pImpl);
            return *this;
        }

        shape(shape&&) = default;
        shape& operator=(shape&&) = default;

        void do_draw() const {  _pImpl->draw_concept();  }
        double do_perimeter() const {  return _pImpl->perimeter_concept(); }
        double do_area() const {       return _pImpl->area_concept();      }

    private:
        struct Concept {
            virtual ~Concept() {}

            virtual void draw_concept() const = 0;
            virtual double perimeter_concept() const = 0;
            virtual double area_concept() const = 0;
            virtual std::unique_ptr<Concept> clone() = 0;
        };

        template <typename T>
        struct ShapeConcept : public Concept {
            ShapeConcept(T sh) : _shape(std::move(sh)) {}
            ~ShapeConcept() = default;

            virtual std::unique_ptr<Concept> clone() override {
                return std::make_unique<ShapeConcept<T>>(_shape);
            }
            ShapeConcept(const ShapeConcept&) = default;
            ShapeConcept(ShapeConcept&&) = default;
            ShapeConcept& operator=(const ShapeConcept&) = default;
            ShapeConcept& operator=(ShapeConcept&&) = default;

            virtual void draw_concept() const override { draw(_shape); }
            virtual double perimeter_concept() const override { return perimeter(_shape); }
            virtual double area_concept() const override { return area(_shape); }

            T _shape;
        };
        std::unique_ptr<Concept> _pImpl;
};

}
#endif
