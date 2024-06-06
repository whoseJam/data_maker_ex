#include <iostream>
#include <vector>

namespace fmt {
/**
 * 输出一个数组
 * @param array 数组
 * @param widthEnter 是否添加换行
*/
void out(const std::vector<int> array, bool withEnter = true) {
    for (auto i : array)
        std::cout << i << ' ';
    if (withEnter) std::cout << '\n';
}

/**
 * 输出边集
 * @param edges 边集
*/
void out(const std::vector<std::tuple<int, int>>& edges) {
    for (auto edge : edges)
        std::cout << std::get<0>(edge) << ' ' << std::get<1>(edge) << '\n';
}

/**
 * 输出一个字符串
 * @param str 字符串
 * @param withEnter 末尾是否换行
*/
void out(const std::string& str, bool withEnter = true) {
    std::cout << str;
    if (withEnter) std::cout << '\n';
}

}