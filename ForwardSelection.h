#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <random>

using namespace std;

struct SetHash {
    size_t operator()(const unordered_set<int>& s) const noexcept {
        size_t h = 0;
        for (int x : s)
            h ^= hash<int>{}(x) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
        return h;
    }
};

struct SetEq {
    bool operator()(const unordered_set<int>& a,
                    const unordered_set<int>& b) const noexcept {
        return a == b;
    }
};

unordered_set<int> getMaxKey(const unordered_map<unordered_set<int>, int, SetHash, SetEq>& mp);
int getRandom(int min, int max);
void insertValue(unordered_set<int>& s, vector<int>& v, int x);
void printVector(const vector<int>& v);
unordered_set<int> ForwardSelection(int n);

#endif