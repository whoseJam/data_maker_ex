#include <cassert>

#include "tree.h"

namespace graph {

std::vector<std::tuple<int, int>> naiveGraph(int n, int m) {
    assert(m >= n - 1);
    auto answer = tree::naiveTree(n);
    m -= (n - 1);
    for (int i = 1; i <= m; i++) {
        int x = rd::rand(1, n);
        int y = rd::rand(1, n);
        answer.push_back(std::make_tuple(x, y));
    }
    return answer;
}

}