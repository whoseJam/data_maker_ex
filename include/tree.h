#ifndef TREE_H
#define TREE_H

#include <vector>
#include <tuple>

#include "rand.h"

namespace tree {

std::vector<int> shuffledNodeId(int n) {
    std::vector<int> nodeId{n};
    for (int i = 1; i <= n; i++)
        nodeId[i - 1] = i;
    for (int i = 0; i < n; i++) {
        int last = rd::rand(0, i);
        std::swap(nodeId[last], nodeId[i]);
    }
    return nodeId;
}

/**
 * 生成一个简单树，简单树的平均高度为O(logn)
 * @param n 树的大小
*/
std::vector<std::tuple<int, int>> naiveTree(int n) {
    std::vector<std::tuple<int, int>> answer;
    auto nodeId = shuffledNodeId(n);
    for (int i = 1; i < n; i++) {
        int cur = nodeId[i];
        int last = nodeId[rd::rand(0, i - 1)];
        if (rd::rand(0, 1) & 1) answer.push_back(std::make_tuple(cur, last));
        else answer.push_back(std::make_tuple(last, cur));
    }
    return answer;
}

/**
 * 生成一条链
 * @param n 树的大小
*/
std::vector<std::tuple<int, int>> chainTree(int n) {
    std::vector<std::tuple<int, int>> answer;
    auto nodeId = shuffledNodeId(n);
    for (int i = 1; i < n; i++) {
        int cur = nodeId[i];
        int last = nodeId[i - 1];
        if (rd::rand(0, 1) & 1) answer.push_back(std::make_tuple(last, cur));
        else answer.push_back(std::make_tuple(last, cur));
    }
    return answer;
}

/**
 * 生成一棵菊花树
 * @param n 树的大小
*/
std::vector<std::tuple<int, int>> flowerTree(int n) {
    std::vector<std::tuple<int, int>> answer;
    auto nodeId = shuffledNodeId(n);
    for (int i = 1; i < n; i++) {
        int cur = nodeId[0];
        int last = nodeId[i - 1];
        if (rd::rand(0, 1) & 1) answer.push_back(std::make_tuple(last, cur));
        else answer.push_back(std::make_tuple(last, cur));
    }
    return answer;
}

/**
 * 生成一棵长树
 * @param n 树的大小
 * @param len 单位长链长度
*/
std::vector<std::tuple<int, int>> longTree(int n, int len) {
    std::vector<std::tuple<int, int>> answer;
    auto nodeId = shuffledNodeId(n);
    int currentLength = 1, last = 0;
    for (int i = 1, fa; i < n; i++) {
        currentLength++; fa = last;
        if (currentLength > len) {
            currentLength = 1;
            fa = rd::rand(0, i - 1);
        }
        // if (rd::rand(0, 1) & 1) 
        answer.push_back(std::make_tuple(nodeId[fa], nodeId[i]));
        // else answer.push_back(std::make_tuple(nodeId[i], nodeId[fa]));
        last = i;
    }
    return answer;
}


}

#endif