/* C++ - Scope and Closures (Lambdas)
Code based on Lei Mao's github [leimao.github.io/blog/CPP-Closure/]
*/

#include <iostream>
#include <functional>

std::function<int(int)>outerFunction(int x){
    //Lambda express with capture.
    return [x](int y) { 
        return x + y;
    };
}

int main() {
    auto closureInstance = outerFunction(5);
    int result = closureInstance(3);
    std::cout << result << std::endl; // Output: 8

    auto createCounter = [](){
        int count = 0;
        //changing count to mutable to allow it to be changed and capture by value.
        return [=]() mutable {
            return ++count;
        };
    };

    auto counter = createCounter();
    std::cout << counter() << std::endl; // First Count: 1
    std::cout << counter() << std::endl; // Second Count: 2
    std::cout << counter() << std::endl; // Third Count: 3

    return 0;
}