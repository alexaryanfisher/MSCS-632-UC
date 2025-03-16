/* C++ - Scope and Closures (Lambdas)
Code based on Lei Mao's GitHub [leimao.github.io/blog/CPP-Closure/]
*/

#include <iostream>
#include <functional>

std::function<int(int)>outerFunction(int x){
    //Lambda expression with capture.
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
        //changing count to mutable, allowing it to be modified and captured by value.
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
