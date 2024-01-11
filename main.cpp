#include <iostream>
#include <unistd.h>

#include "profiling.hpp"

int main()
{   
    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::duration<double, std::milli> duration;
    int i;
    for (i = 1; i <= 100; i++) {
        // t1 = std::chrono::high_resolution_clock::now();
        // Profiling("A").stop();
        Profiling("A").start();
        // pre_process();
        sleep(0.1);
        Profiling("A").stop();
        // t2 = std::chrono::high_resolution_clock::now();
        duration = t2 - t1;
        // Profiling("A").start();
    }

    // std::cout << ": " <<  duration.count() << std::endl;
    std::cout << "A: " <<  Profiling("A").getCurrentDuration() << std::endl;
    std::cout << "A Average Time: " <<  Profiling("A").getAverageTime() << std::endl;
    std::cout << "Report: \n" << Profiling::report();

    return 0;
}