#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

int VectorSum(const std::vector<int>& v1, const std::vector<int>& v2){
    return std::accumulate(v1.begin(), v1.end(), 0) + 
        std::accumulate(v2.begin(), v2.end(), 0);
}

int VectorSumAsync(const std::vector<int>& v1, const std::vector<int>& v2){
    std::future<int> sum1 = std::async( [&v1] {
        return std::accumulate(v1.begin(), v1.end(), 0);
    });
    return std::accumulate(v2.begin(), v2.end(), 0) + sum1.get();
}

int main(){
    std::cout << "VectorSum: " << VectorSum({1, 1, 1, 1}, {3, 3, 3}) << std::endl;
    std::cout << "VectorSumAsync: " << VectorSumAsync({1, 1, 1, 1}, {3, 3, 3}) << std::endl;
    return 0;
}