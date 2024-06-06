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

struct tree {
public:
    tree(int root, const std::vector<std::tuple<int, int>> edges) {
        int n = edges.size() + 1;
        fa.resize(n + 1);
        lx.resize(n + 1);
        rx.resize(n + 1);
        dep.resize(n + 1);
        graph.resize(n + 1);
        for (auto& edge : edges) {
            int x = std::get<0>(edge);
            int y = std::get<1>(edge);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        dfs(root, 0);
    }
    std::vector<int> fa;
    std::vector<int> dep;
    std::vector<int> seq;
    std::vector<int> lx;
    std::vector<int> rx;
    std::vector<std::vector<int>> graph;

    /**
     * 从u的子树中，随机抽取n个元素
     * @param u
     * @param n
    */
    std::vector<int> subtree(int u, int n) {
        assert(rx[u] - lx[u] + 1 <= n);
        auto answerIndex = seq::makeUnique(n, lx[u], rx[u]);
        std::vector<int> answer;
        for (auto& index : answerIndex)
            answer.push_back(seq[index]);
        return answer;
    }
private:
    void dfs(int u, int f) {
        fa[u] = f; dep[u] = dep[f] + 1;
        lx[u] = seq.size();
        seq.push_back(u);
        for (auto& v : graph[u]) dfs(v, u);
        rx[u] = seq.size() - 1;
    }
};

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