// Example C++ solution file
// This demonstrates how your source files should be structured

#include <iostream>
#include <vector>
#include <numeric>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }
    
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    double average = static_cast<double>(sum) / n;
    
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;
    // std::cout << "Test change" << std::endl;
    
    return 0;
}
