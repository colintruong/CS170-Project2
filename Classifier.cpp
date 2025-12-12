#include "Classifier.h"

Classifier::Classifier() {
    // Placeholder
}

// stores data for NN lookup
void Classifier::train(const vector<Instance>& data) {
    trainingData = data;
}

int Classifier::test(const vector<double>& id) {
    double bestDist = INFINITY;     // initialized as a super large value
    int bestClass = 0;
    
    for (const Instance& instance : trainingData) {     // going through each instance in the training data and calculating distance from our input data point
        double distance = euclidean(id, instance.features);
        if (distance < bestDist) {  // update if there's a closer instance
            bestDist = distance;
            bestClass = instance.classLabel;
        }
    }
    return bestClass;   // returns closest instance's class (1-NN)
}

// Euclidean distance between two Instances
double Classifier::euclidean(const vector<double>& a, const vector<double>& b) const {
    double sum = 0.0;
    for (int i = 0; i < a.size(); i++) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

vector<Instance> Classifier::loadDataset(const string& filename) {
    vector<Instance> dataset;
    ifstream fin(filename);
    if (!fin) { 
        cerr << "Cannot open file: " << filename << endl;
        return dataset;
    }

    string line;
    int expected = -1;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        double val;
        Instance inst;

        ss >> val;
        inst.classLabel = static_cast<int>(val);

        while (ss >> val)
            inst.features.push_back(val);

        // Determine expected feature count from first row
        if (expected == -1) {
            expected = inst.features.size();
        }

        // Skip malformed rows
        if (inst.features.size() != expected) {
            cout << "Skipping row (feature count mismatch): has "
                 << inst.features.size() << " expected " << expected << endl;
            continue;
        }

        dataset.push_back(inst);
    }

    return dataset;
}

// Normalizing data with z-score function
void Classifier::normalizeData(vector<Instance>& data) {
    if (data.empty()) return;

    int numFeatures = data[0].features.size();
    int n = data.size();

    vector<double> mean(numFeatures, 0.0);
    vector<double> stddev(numFeatures, 0.0);

    for (const auto& inst : data)
        for (int i = 0; i < numFeatures; i++)
            mean[i] += inst.features[i];

    for (int i = 0; i < numFeatures; i++)
        mean[i] /= n;

    for (const auto& inst : data)
        for (int i = 0; i < numFeatures; i++)
            stddev[i] += pow(inst.features[i] - mean[i], 2);

    for (int i = 0; i < numFeatures; i++)
        stddev[i] = sqrt(stddev[i] / n);

    for (auto& inst : data)
        for (int i = 0; i < numFeatures; i++)
            inst.features[i] = (inst.features[i] - mean[i]) /
                               (stddev[i] == 0 ? 1 : stddev[i]);
}