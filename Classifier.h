#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

struct Instance {
    int classLabel;
    vector<double> features;
};

class Classifier {
    public:
        Classifier();
        void train(const vector<Instance>& data);
        int test(const vector<double>& id);
        vector<Instance> loadDataset(const string& filename);
        void normalizeData(vector<Instance>& data);
    private:
        vector<Instance> trainingData;
        double euclidean(const vector<double>& a, const vector<double>& b) const;
};
#endif