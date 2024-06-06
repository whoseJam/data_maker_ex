#ifndef SEQ_H
#define SEQ_H
#include <algorithm>
#include <iostream>
#include <cassert>
#include <clocale>
#include <random>
#include <string>
#include <cwchar>
#include <vector>
#include <string>
#include <set>

#include "rand.h"

namespace seq {

/**
 * 构造一个长度为n的，元素范围[min, max]的数组
 * @param n
 * @param min
 * @param max
*/
std::vector<int> make(int n, int min, int max) {
    assert(min < max);
    std::vector<int> answer;
    for (int i = 0; i < n; i++)
        answer.push_back(rd::rand(min, max));
    return answer;
}

/**
 * 构造一个长度为n的，元素范围[min, max]且任意相邻两项不同的数组
 * @param n
 * @param min
 * @param max
*/
std::vector<int> makeAdjacentDiff(int n, int min, int max) {
    assert(min < max);
    std::vector<int> answer;
    for (int i = 0; i < n; i++) {
        if (i == 0) answer.push_back(rd::rand(min, max));
        else if (min + 5 > max) {
            int cur = rd::rand(min, max);
            if (cur == answer[i - 1]) {
                if (rd::rand(0, 1) & 1) {
                    if (cur - 1 >= min) cur--;
                    else cur++;
                } else {
                    if (cur + 1 <= max) cur++;
                    else cur--;
                }
            }
            answer.push_back(cur);
        } else {
            int cur = rd::rand(min, max);
            while (cur == answer[i - 1])
                cur = rd::rand(min, max);
            answer.push_back(cur);
        }
    }
    return answer;
}

/**
 * 构造一个元素范围为[min, max]的长度为n的元素互不相同的数组
 * @param n 数组长度
 * @param min 最小元素值
 * @param max 最大元素值
*/
std::vector<int> makeUnique(int n, int min, int max) {
    assert(max - min + 1 >= n);
    if (max - min + 1 <= n * 5) {
        std::vector<int> memory(max - min + 1);
        for (int i = min; i <= max; i++)
            memory[i - min] = i;
        std::shuffle(memory.begin(), memory.end(), rd::gen);
        std::vector<int> answer;
        for (int i = 0; i < n; i++)
            answer.push_back(memory[i]);
        return answer;
    } else {
        std::set<int> memory;
        std::vector<int> answer;
        for (int i = 1; i <= n; i++) {
            int x = rd::rand(min, max);
            while (memory.find(x) != memory.end())
                x = rd::rand(min, max);
            answer.push_back(x);
        }
        return answer;
    }
}

/**
 * 构造一个长度为n的字符集范围[min, max]的字符串
 * @param n
 * @param min
 * @param max
*/
std::string makeString(int n, char min, char max) {
    std::string answer;
    for (int i = 0; i < n; i++)
        answer.push_back(rd::rand(min, max));
    return answer;
}

/**
 * 构造一个n的排列
 * @param n 数组长度
*/
std::vector<int> makePermutation(int n) {
    std::vector<int> answer;
    for (int i = 1; i <= n; i++) {
        answer.push_back(i);
        int cur = i - 1;
        if (0 < cur) {
            int last = rd::rand(0, cur);
            std::swap(answer[last], answer[cur]);
        }
    }
    return answer;
}

}

#endif