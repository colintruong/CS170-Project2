#include "Classifier.h"

Classifier::Classifier() {
}

void Classifier::train(const vector<Instance>& data) {
    trainingData = data;
}

int Classifier::test(const vector<double>& id) {
    float bestDist = INT_MAX;
    int bestClass = -1;
    
    for (const Instance& instance : trainingData) {
        double distance = euclidean(id, instance.features);
        if (distance < bestDist) {
            bestDist = distance;
            bestClass = instance.classLabel;
        }
    }
    return bestClass;
}

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
    if (!fin) { cerr << "Cannot open file\n"; return dataset; }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        double val;
        Instance inst;
        ss >> val;
        inst.classLabel = static_cast<int>(val);

        while (ss >> val)
            inst.features.push_back(val);

        dataset.push_back(inst);
    }
    return dataset;
}

int main() {
    Classifier cl;
    string filename = "small-test-dataset-2-2.txt";
    vector<Instance> dataset = cl.loadDataset(filename);

    if (dataset.empty()) {
        cerr << "Dataset empty!\n";
        return 1;
    }

    // Example: train on all but last instance, test on last
    vector<Instance> trainSet(dataset.begin(), dataset.end() - 1);
    cl.train(trainSet);

    int predicted = cl.test(dataset.back().features);
    cout << "Predicted: " << predicted 
         << ", Actual: " << dataset.back().classLabel << endl;

    return 0;
}


