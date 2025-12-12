#include "ForwardSelection.h"

// Returns the feature set with the highest accuracy in the map
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

unordered_set<int> ForwardSelection(const vector<Instance>& dataset, validator& val) {
    cout << fixed << setprecision(2);

    int n = dataset[0].features.size();

    unordered_set<int> bestSet = {};        // best global subset
    double bestValue = 0;                   // best global accuracy
    unordered_set<int> currentSet = {};     // current subset
    double lastValue = 0;                   // current subset accuracy

    // Default accuracy
    cout << "Using no features, I get a default accuracy of "
         << val.leaveOneOutValidation(dataset, {}) * 100 << "%\n";
         
    cout << "Beginning search.\n";

    // Continuously adding features until we have all features considered
    while (currentSet.size() < n) {
        // Map to store current iteration's subsets and their corresponding accuracies
        unordered_map<unordered_set<int>, double, SetHash, SetEq> map;

        // Go through each feature
        for (int i = 1; i <= n; i++) {
            // If feature i is not in the current set, add. Else, skip
            if (currentSet.count(i) == 0) {
                unordered_set<int> newFeature = currentSet;
                newFeature.insert(i);

                vector<int> feature(newFeature.begin(), newFeature.end());
                double score = val.leaveOneOutValidation(dataset, feature) * 100.0;
                map.insert({ newFeature, score });

                cout << "Using feature(s) ";
                printSet(newFeature);
                cout << " accuracy is " << score << "%\n";
            }
        }

        // Getting the best feature subset in the current iteration
        unordered_set<int> nextSet = getMaxKey(map);
        double nextValue = map[nextSet];

        cout << "Feature set ";
        printSet(nextSet);
        cout << " was best, accuracy is " << nextValue << "%\n";

        if (nextValue < lastValue) {
            cout << "(Warning, Accuracy has decreased!)\n";
        }

        currentSet = nextSet;
        lastValue = nextValue;

        if (nextValue > bestValue) {    // updating the best subset if possible
            bestSet = nextSet;
            bestValue = nextValue;
        }
    }

    cout << "Finished search!! The best feature subset is ";
    printSet(bestSet);
    cout << ", which has an accuracy of " << bestValue << "%\n";

    return bestSet;
}
