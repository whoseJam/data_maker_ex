#ifndef RAND_H
#define RAND_H

#include <cassert>
#include <random>

namespace rd {

std::mt19937 gen;

/**
 * 初始化随机机器
 * @param seed 随机种子
*/
void init(int seed) {
    gen.seed(seed);
}

/**
 * 生成一个[l, r]范围内的32位整数
 * @param l
 * @param r
*/
int randInt(int l, int r) {
    assert(l <= r);
    return gen() % (r - l + 1) + l;
}

/**
 * 生成一个[l, r]范围内的32位整数
 * @param l
 * @param r
*/
int rand(int l, int r) {
    return randInt(l, r);
}

/**
 * 生成一个[l, r]范围内的8位字符
 * @param l
 * @param r
*/
char randChar(char l, char r) {
    assert(l <= r);
    return gen() % (r - l + 1) + l;
}

}

#endif