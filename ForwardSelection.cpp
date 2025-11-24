#include "ForwardSelection.h"

unordered_set<int> getMaxKey(const unordered_map<unordered_set<int>, int, SetHash, SetEq>& mp) {
    if (mp.empty())
        return {};

    auto it = max_element(
        mp.begin(), mp.end(),
        [](const auto& p1, const auto& p2) { return p1.second < p2.second; }
    );

    return it->first;
}

int getRandom(int min, int max) {
    static random_device rd; 
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

unordered_set<int> ForwardSelection(int n) {
    unordered_set<int> bestSet = {};
    int bestValue = INT_MIN;
    unordered_set<int> currentSet = {};
    while (currentSet.size() < n) {
        unordered_map<unordered_set<int>, int, SetHash, SetEq> map;
        for (int i = 1; i <= n; i++) {
            unordered_set<int> newFeature = currentSet;
            if (currentSet.count(i) == 0) {
                newFeature.insert(i);
                int score = getRandom(1, 100);
                cout << "New set: { ";
                printSet(newFeature);
                cout << "}, " << score << endl;
                map.insert({newFeature, score});
            }
        }
        currentSet = getMaxKey(map);
        int currentValue = map[currentSet];
        cout << "Current set: { ";
        printSet(currentSet);
        cout << "}, " << map[currentSet] << endl;
        if (bestValue < currentValue) {
            bestSet = currentSet;
            bestValue = currentValue;
        }
        cout << "Best set: { ";
        printSet(bestSet);
        cout << "}, " << bestValue << endl;
        cout << "-------------------------" << endl;
    }
    return bestSet;
}

void printSet(unordered_set<int> s) {
    for (int num : s) {
        cout << num << " ";
    }
}

int main() {
    cout << "Testing features 1...3" << endl;
    ForwardSelection(5);
    cout << "Finished!" << endl;
    return 0;
}