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

// Convert the vector of features into a sorted string
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

    // Number of features for each instance
    int n = dataset[0].features.size();

    // Start with the full feature set
    vector<int> currSet;
    for (int i = 1; i <= n; ++i) {
        currSet.push_back(i);
    }

    // Evaluating accuracy using all features
    double currAccuracy = val.leaveOneOutValidation(dataset, currSet) * 100.0;
    vector<int> bestSoFar = currSet;
    double bestAccuracy = currAccuracy;

    // Evaluating accuracy with no features
    cout << "Using no features, I get a default accuracy of "
         << val.leaveOneOutValidation(dataset, {}) * 100 << "%\n";
    cout << "Beginning the search.\n";

    // Removing one feature every iteration
    while (currSet.size() > 1) {
        double bestAccLevel = -DBL_MAX;     // best accuracy at this level
        vector<int> bestCand;               // best feature subset at this level

        for (size_t j = 0; j < currSet.size(); ++j) {
            // Creating a new candidate subset with currSet[j] removed
            vector<int> candidate;
            candidate.reserve(currSet.size() - 1);

            for (size_t k = 0; k < currSet.size(); ++k) {
                if (k != j) {
                    candidate.push_back(currSet[k]);
                }
            }

            // Evaluate the candidate's accuracy
            double acc = val.leaveOneOutValidation(dataset, candidate) * 100.0;

            cout << "Feature subset: " << stringFormat(candidate) 
                 << " Accuracy: " << acc << "%\n";

            // Keep track of the best subset at this level
            if (acc > bestAccLevel) {
                bestAccLevel = acc;
                bestCand = candidate;
            }
        }

        // Update current set to the best subset found in this iteration
        currSet = bestCand;

        cout << "\nBest subset at this level: " << stringFormat(currSet) 
             << " Accuracy: " << bestAccLevel << "%\n";

        if (bestAccLevel < bestAccuracy) {
            cout << "(Warning, Accuracy has decreased!)\n";
        }

        // Update the global best if there's improvement
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

