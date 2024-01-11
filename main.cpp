#include <iostream>

namespace profiler {
    class BaseBlockDescriptor {
        BaseBlockDescriptor(){};
        ~BaseBlockDescriptor(){};
    };
}

int main()
{
    int BaseBlockDescriptor = 42;
    profiler::BaseBlockDescriptor descriptor();
    std::cout << "test\n";
    BaseBlockDescriptor = 43;

    return 0;
}