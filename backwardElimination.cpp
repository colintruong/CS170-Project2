#include "backwardElimination.h"
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

double randomGenerator(const vector<int>& features){
    static mt19937 rng(random_device{}());
    static uniform_real_distribution<double> dist(0.0, 100.0);
    return dist(rng);
}

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

void backwardElimination(int numFeatures){
    vector<int> currSet;
    for (int i = 1; i <= numFeatures; ++i){
        currSet.push_back(i);
    }

    double currAccuracy = randomGenerator(currSet);
    vector<int> bestSoFar = currSet;
    double bestAccuracy = currAccuracy;

    cout << "Features: " << stringFormat(currSet) << " Evaluation: \"random\" Accuracy: " << fixed << setprecision(1) << currAccuracy << "%\n" << endl;
    cout << "Beginning the search.\n" << endl;

    while (currSet.size() > 1){
        double bestAccLevel = -1.0;
        vector<int> bestCand;

        for (size_t j = 0; j < currSet.size(); ++j){
            vector<int> candidate;
            candidate.reserve(currSet.size() - 1);
            for (size_t k = 0; k < currSet.size(); ++k) {
                if (k != j){
                    candidate.push_back(currSet[k]);
                }
            }

            double acc = randomGenerator(candidate);
            cout << "Feature: " << stringFormat(candidate) << " Accuracy: " << fixed << setprecision(1) << acc << "%\n";
            if (acc > bestAccLevel){
                bestAccLevel = acc;
                bestCand = candidate;
            }
        }

        currSet = bestCand;
        cout << endl;
        cout << "Feature: " << stringFormat(currSet) << " was best. Accuracy: " << fixed << setprecision(1) << bestAccLevel << "%\n" << endl;

        if (bestAccLevel < bestAccuracy){
            cout << "(Warning, Accuracy has decreased!)\n";
        }

        if (bestAccLevel > bestAccuracy){
            bestAccuracy = bestAccLevel;
            bestSoFar = currSet;
        }
    }

    cout << "Best feature: " << stringFormat(bestSoFar) << ". Accuracy: " << fixed << setprecision(1) << bestAccuracy << "%\n";
}