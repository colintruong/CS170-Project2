#include "backwardElimination.h"
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <climits>
#include <cfloat>

using namespace std;

// double randomGenerator(const vector<int>& features){
//     static mt19937 rng(random_device{}());
//     static uniform_real_distribution<double> dist(0.0, 100.0);
//     return dist(rng);
// }

string stringFormat(const vector<int>& features){
    if (features.empty()){
        return "{}";
    }

    vector<int> sorted = features;
    sort(sorted.begin(), sorted.end());

    string s = "{";
    for (size_t i = 0; i < sorted.size(); ++i){
        if (i > 0){
            s += ",";
        }
        s += to_string(sorted[i]);
    }
    s += "}";
    return s;
}

unordered_set<int> backwardElimination(const vector<Instance>& dataset, validator& val) {
    cout << fixed << setprecision(2);

    int n = dataset[0].features.size();

    vector<int> currSet;
    for (int i = 1; i <= n; ++i) {
        currSet.push_back(i);
    }

    double currAccuracy = val.leaveOneOutValidation(dataset, currSet) * 100.0;
    vector<int> bestSoFar = currSet;
    double bestAccuracy = currAccuracy;

    cout << "Using no features, I get a default accuracy of "
         << val.leaveOneOutValidation(dataset, {}) * 100 << "%\n";
    cout << "Beginning the search.\n";

    while (currSet.size() > 1) {
        double bestAccLevel = -DBL_MAX;
        vector<int> bestCand;

        for (size_t j = 0; j < currSet.size(); ++j) {
            vector<int> candidate;
            candidate.reserve(currSet.size() - 1);

            for (size_t k = 0; k < currSet.size(); ++k) {
                if (k != j) {
                    candidate.push_back(currSet[k]);
                }
            }

            double acc = val.leaveOneOutValidation(dataset, candidate) * 100.0;

            cout << "Feature subset: " << stringFormat(candidate) 
                 << " Accuracy: " << acc << "%\n";

            if (acc > bestAccLevel) {
                bestAccLevel = acc;
                bestCand = candidate;
            }
        }

        currSet = bestCand;

        cout << "\nBest subset at this level: " << stringFormat(currSet) 
             << " Accuracy: " << bestAccLevel << "%\n";

        if (bestAccLevel < bestAccuracy) {
            cout << "(Warning, Accuracy has decreased!)\n";
        }

        if (bestAccLevel > bestAccuracy) {
            bestAccuracy = bestAccLevel;
            bestSoFar = currSet;
        }
    }

    cout << "\nFinished search!! Best feature subset: " << stringFormat(bestSoFar)
         << " Accuracy: " << bestAccuracy << "%\n";

    unordered_set<int> bestSet(bestSoFar.begin(), bestSoFar.end());
    return bestSet;
}

