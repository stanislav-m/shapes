#ifndef _vt_shapes_h_
#define _vt_shapes_h_

#include "common.h"
#include <memory>

namespace vt_shapes {

struct vtable {
    void (*destroy_)(void* ptr);
    void* (*clone_)(void* ptr);
    void* (*move_clone_)(void* ptr);
    void (*draw)(void* ptr);
    double (*perimeter)(void* ptr);
    double (*area)(void* ptr);
};

template <typename T>
constexpr vtable vtable_for {
    [](void* ptr) { delete static_cast<T*>(ptr); },
    [](void* ptr) -> void* { return new T(*static_cast<T*>(ptr)); },
    [](void* ptr) -> void* { return new T(std::move(*static_cast<T*>(ptr))); },
    [](void* ptr) { static_cast<T*>(ptr)->draw(); },
    [](void* ptr) { return static_cast<T*>(ptr)->perimeter(); },
    [](void* ptr) { return static_cast<T*>(ptr)->area(); }
};

struct shape {
    void* t_;
    vtable const* vtable_;

    template<typename T>
    shape(T const& t) : t_(new T(t)), vtable_(&vtable_for<T>) {}
    shape(const shape& rhs) : t_(rhs.vtable_->clone_(rhs.t_)), vtable_(rhs.vtable_) {}
    shape(shape&& rhs) : t_(rhs.vtable_->move_clone_(rhs.t_)), vtable_(rhs.vtable_) {}
    ~shape() { vtable_->destroy_(t_); }

    void draw() const        { vtable_->draw(t_); }
    double perimeter() const { return vtable_->perimeter(t_); }
    double area() const      { return vtable_->perimeter(t_); }
};

class circle {
    public:
        circle(double r) : _r(r) {}
        ~circle() = default;
 
        circle(const circle&) = default;
        circle(circle&&) = default;
        circle& operator=(const circle&) = default;
        circle& operator=(circle&&) = default;

        double get_r() const { return _r; }

        void draw() const {}
        double perimeter() const { return 2 * pi * _r;}
        double area() const { return pi * _r * _r;}

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

        void draw() const {}
        double perimeter() const { return 2 * (_a + _b);}
        double area() const { return _a * _b;}

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

        void draw() const {}
        double perimeter() const { return _a + _b + _c;}
        double area() const { return (_a * _h) / 2;}
    private:
        double _a;
        double _b;
        double _c;
        double _h;
};

}
#endif
