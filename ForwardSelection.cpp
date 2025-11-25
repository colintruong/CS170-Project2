#include "ForwardSelection.h"
#include <climits>
#include <iomanip>

double getRandomAcc() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<double> dist(20.0, 80.0);
    return dist(gen);
}

unordered_set<int> getMaxKey(const unordered_map<unordered_set<int>, double, SetHash, SetEq>& mp) {
    auto it = max_element(
        mp.begin(), mp.end(),
        [](const auto& p1, const auto& p2) { return p1.second < p2.second; }
    );
    return it->first;
}

void printSet(const unordered_set<int>& s) {
    vector<int> v(s.begin(), s.end());
    sort(v.begin(), v.end());
    cout << "{";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ",";
    }
    cout << "}";
}

unordered_set<int> ForwardSelection(int n) {
    cout << fixed << setprecision(1);

    cout << "Using no features and \"random\" evaluation, I get an accuracy of "
         << getRandomAcc() << "%\n";
    cout << "Beginning search.\n";

    unordered_set<int> bestSet = {};
    double bestValue = -DBL_MAX;
    unordered_set<int> currentSet = {};
    double lastValue = -DBL_MAX;

    while (currentSet.size() < n) {
        unordered_map<unordered_set<int>, double, SetHash, SetEq> map;

        for (int i = 1; i <= n; i++) {
            if (currentSet.count(i) == 0) {
                unordered_set<int> newFeature = currentSet;
                newFeature.insert(i);

                double score = getRandomAcc();
                map.insert({ newFeature, score });

                cout << "Using feature(s) ";
                printSet(newFeature);
                cout << " accuracy is " << score << "%\n";
            }
        }

        unordered_set<int> nextSet = getMaxKey(map);
        double nextValue = map[nextSet];

        cout << "Feature set ";
        printSet(nextSet);
        cout << " was best, accuracy is " << nextValue << "%\n";

        if (lastValue > 0 && nextValue < lastValue) {
            cout << "(Warning, Accuracy has decreased!)\n";
        }

        currentSet = nextSet;
        lastValue = nextValue;

        if (nextValue > bestValue) {
            bestSet = nextSet;
            bestValue = nextValue;
        }
    }

    cout << "Finished search!! The best feature subset is ";
    printSet(bestSet);
    cout << ", which has an accuracy of " << bestValue << "%\n";

    return bestSet;
}
