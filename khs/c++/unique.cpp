#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 1, 2, 2, 3, 4, 4, 5};

    // 중복 제거
    auto new_end = std::unique(vec.begin(), vec.end());

    // 중복이 제거된 벡터 출력
    for (auto it = vec.begin(); it != new_end; ++it) {
        std::cout << *it << " ";
    }

    return 0;
}