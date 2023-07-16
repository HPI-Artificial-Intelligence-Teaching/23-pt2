#include <functional>
#include <iostream>
int main() {
    int factor = 2;  // A variable to capture in the closure
    // Create a closure that multiplies an integer by the captured factor
    auto multiply = [factor](int num) { return num * factor; };
    // Call the closure
    int result = multiply(5);
    std::cout << "Result: " << result << std::endl;
    return 0;
}