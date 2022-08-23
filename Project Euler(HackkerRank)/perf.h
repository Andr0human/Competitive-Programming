

#ifndef PERF_H
#define PERF_H

#ifdef OPTIMIZE
#define OPTIMIZE
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#endif

#include <iostream>
#include <chrono>
#include <utility>

#define FAST_IO(); std::ios::sync_with_stdio(0); std::cin.tie(0);
#define RANDOM_TIME srand(std::chrono::steady_clock::now().time_since_epoch().count());
#define perf_clock std::chrono::_V2::high_resolution_clock::time_point
#define perf_time std::chrono::duration<float>

namespace perf {


inline perf_clock now() {
    return std::chrono::high_resolution_clock::now();
}

struct Timer {

    perf_clock _start, _end;
    std::chrono::duration<float> duration;
    std::string func_name;

    Timer() { 
        func_name = "Timer";
        _start = now();
    }

    Timer(std::string function_name) {
        func_name = function_name;
        _start = now();
    }

    ~Timer() {
        _end = now();
        duration = _end - _start;
        std::cout << func_name << " took " << duration.count() << " sec." << std::endl;
    }


};

template <typename _Callable, typename... _Args>
float Time(_Callable &__f, _Args&&... __args) {
    perf_clock start = now();
    __f(std::forward<_Args>(__args)...);
    std::chrono::duration<float> dur = now() - start;
    return dur.count();
}

template <typename _Callable, typename... _Args>
void StopWatch(std::string func_name,  _Callable &__f, _Args&&... __args) {
    perf_clock start = now();
    __f(std::forward<_Args>(__args)...);
    std::chrono::duration<float> dur = now() - start;
    std::cout << func_name << " took " << dur.count() << " sec." << std::endl;
}


}


#endif



