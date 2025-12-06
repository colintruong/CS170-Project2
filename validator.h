#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "Classifier.h"
#include <vector>
#include <climits>

using namespace std;

class validator{
    public:
        validator(Classifier& classify);
        double leaveOneOutValidation(const vector<Instance>& data, const vector<int>& feature);
        Instance inst(const Instance& instance, const vector<int>& feature) const;
        vector<double> feat(const Instance& instance, const vector<int>& feature) const;

    private:
        Classifier& classifier;
};

#endif