#include "vshapes.h"
#include "sshapes.h"
#include "var_shapes.h"
#include "mpark_shapes.h"
#include "vt_shapes.h"

#include <stdlib.h>
#include <benchmark/benchmark.h>

#include <vector>

double get_rand() {
    srand (time(NULL));
    /*
    int cnt = int(rand() % 10 + 1);
    for (int i=0; i<cnt;++i)
        srand (time(NULL));
        */
    return rand() % 10 + 1;
}

static void BM_TypeErasureShapes(benchmark::State& state) {
    std::vector<static_shapes::shape> vec;
    vec.reserve(3*state.range(0));

    for (int i = 0; i < state.range(0); ++i) {
        vec.emplace_back(static_shapes::circle(get_rand()));
        vec.emplace_back(static_shapes::rectangle(get_rand(), get_rand()));
        vec.emplace_back(static_shapes::triangle(get_rand(), get_rand(), get_rand(), get_rand()));
    }  
    for (auto _ : state)
        for (const auto& v : vec) {
            v.do_draw();
            v.do_area();
            v.do_perimeter();
        }
}

static void BM_VirtualShapes(benchmark::State& state) {
    std::vector<std::unique_ptr<virtual_shapes::shape>> vec;
    vec.reserve(3*state.range(0));

    for (int i = 0; i < state.range(0); ++i) {
        vec.emplace_back(std::make_unique<virtual_shapes::circle>(get_rand()));
        vec.emplace_back(std::make_unique<virtual_shapes::rectangle>(get_rand(), get_rand()));
        vec.emplace_back(std::make_unique<virtual_shapes::triangle>(get_rand(), get_rand(), get_rand(), get_rand()));
    }  

    for (auto _ : state)
        for (const auto& v : vec) {
            v->draw();
            v->area();
            v->perimeter();
        }
}

static void BM_VariantShapes(benchmark::State& state) {
    std::vector<var_shapes::shape> vec;
    vec.reserve(3*state.range(0));

    for (int i = 0; i < state.range(0); ++i) {
        vec.emplace_back(var_shapes::circle(get_rand()));
        vec.emplace_back(var_shapes::rectangle(get_rand(), get_rand()));
        vec.emplace_back(var_shapes::triangle(get_rand(), get_rand(), get_rand(), get_rand()));
    }  
    for (auto _ : state)
        for (const auto& v : vec) {
            v.do_draw();
            v.do_area();
            v.do_perimeter();
        }
}

static void BM_MParkShapes(benchmark::State& state) {
    std::vector<mpark_shapes::shape> vec;
    vec.reserve(3*state.range(0));

    for (int i = 0; i < state.range(0); ++i) {
        vec.emplace_back(mpark_shapes::circle(get_rand()));
        vec.emplace_back(mpark_shapes::rectangle(get_rand(), get_rand()));
        vec.emplace_back(mpark_shapes::triangle(get_rand(), get_rand(), get_rand(), get_rand()));
    }  
    for (auto _ : state)
        for (const auto& v : vec) {
            v.do_draw();
            v.do_area();
            v.do_perimeter();
        }
}

static void BM_FullStaticShapes(benchmark::State& state) {
    std::vector<static_shapes::circle> vec_c;
    std::vector<static_shapes::rectangle> vec_r;
    std::vector<static_shapes::triangle> vec_t;
    vec_c.reserve(state.range(0));
    vec_r.reserve(state.range(0));
    vec_t.reserve(state.range(0));

    for (int i = 0; i < state.range(0); ++i) {
        vec_c.emplace_back(static_shapes::circle(get_rand()));
        vec_r.emplace_back(static_shapes::rectangle(get_rand(), get_rand()));
        vec_t.emplace_back(static_shapes::triangle(get_rand(), get_rand(), get_rand(), get_rand()));
    }  
    for (auto _ : state) {
        for (const auto& v : vec_c) {
            draw(v);
            area(v);
            perimeter(v);
        }
        for (const auto& v : vec_r) {
            draw(v);
            area(v);
            perimeter(v);
        }
        for (const auto& v : vec_t) {
            draw(v);
            area(v);
            perimeter(v);
        }
    }
}

static void BM_VTShapes(benchmark::State& state) {
    std::vector<vt_shapes::shape> vec;
    vec.reserve(3*state.range(0));

    for (int i = 0; i < state.range(0); ++i) {
        vec.emplace_back(vt_shapes::circle(get_rand()));
        vec.emplace_back(vt_shapes::rectangle(get_rand(), get_rand()));
        vec.emplace_back(vt_shapes::triangle(get_rand(), get_rand(), get_rand(), get_rand()));
    }  

    for (auto _ : state)
        for (const auto& v : vec) {
            v.draw();
            v.area();
            v.perimeter();
        }
}

// Register the function as a benchmark
BENCHMARK(BM_TypeErasureShapes)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000);
BENCHMARK(BM_VirtualShapes)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000);
BENCHMARK(BM_VariantShapes)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000);
BENCHMARK(BM_MParkShapes)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000);
BENCHMARK(BM_FullStaticShapes)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000);
BENCHMARK(BM_VTShapes)->Arg(1000)->Arg(10000)->Arg(50000)->Arg(100000);

BENCHMARK_MAIN();
