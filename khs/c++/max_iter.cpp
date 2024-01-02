#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    // 최댓값과 최솟값을 찾는다
    auto max_iter = std::max_element(numbers.begin(), numbers.end());
    auto min_iter = std::min_element(numbers.begin(), numbers.end());

    // 결과 출력
    std::cout << "최댓값: " << *max_iter << std::endl;
    std::cout << "최솟값: " << *min_iter << std::endl;

    return 0;
}