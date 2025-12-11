#include <iostream>
#include <chrono>
#include <iomanip>
#include "ForwardSelection.h"
#include "backwardElimination.h"
#include "Classifier.h"
#include "validator.h"

using namespace std;

int evaluation(const unordered_set<int>& featureSubset, 
               const string& fileName, 
               const vector<Instance>& dataset, 
               validator& val) 
{
    if (dataset.empty()) {
        cerr << "Dataset is empty. Cannot evaluate.\n";
        return 0;
    }

    Classifier cl;
    cl.normalizeData(const_cast<vector<Instance>&>(dataset)); // normalize in-place if needed

    // Convert unordered_set<int> to vector<int> for validator
    vector<int> features(featureSubset.begin(), featureSubset.end());

    cout << "\n===== FEATURE SUBSET EVALUATION =====" << endl;
    cout << "Feature subset: ";
    for (size_t i = 0; i < features.size(); ++i) {
        cout << features[i];
        if (i + 1 < features.size()) cout << ", ";
    }
    cout << "\n" << endl;

    auto start = chrono::high_resolution_clock::now();

    int n = dataset.size();
    int correct = 0;

    for (int i = 0; i < n; i++) {
        vector<Instance> train;
        train.reserve(n - 1);
        for (int j = 0; j < n; j++) {
            if (j != i) {
                train.push_back(val.inst(dataset[j], features));
            }
        }

        cl.train(train);

        vector<double> testFeatures = val.feat(dataset[i], features);
        int predicted = cl.test(testFeatures);
        int actual = dataset[i].classLabel;

        cout << "Instance " << i
             << " | Predicted = " << predicted
             << " | Actual = " << actual
             << " | " << (predicted == actual ? "Correct" : "Wrong")
             << endl;

        if (predicted == actual) correct++;
    }

    double accuracy = (double)correct / n;

    auto end = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration<double>(end - start).count();

    cout << "\nCorrect Predictions: " << correct << " / " << n << endl;
    cout << fixed << setprecision(6);
    cout << "Final accuracy = " << accuracy << endl;
    cout << "Time elapsed = " << elapsed << " seconds\n";
    cout << "===== END FEATURE SUBSET EVALUATION =====\n";

    return 0;
}

void menu() {
    int option, choice;
    string fileName;
    unordered_set<int> result;
    cout << "Welcome to Colin Truong/David Lee/Bavly Shehata's Feature Selection Algorithm." << endl;
    cout << endl;

    cout << "Pick small (1) or large (2) or titanic (3) dataset: ";
    cin >> option;
    if (option == 1) {
        fileName = "small-test-dataset-2-2.txt";
    } else if (option == 2) {
        fileName = "large-test-dataset-2.txt";
    } else if (option == 3) {
        fileName = "titanic clean-2.txt";
    }

    Classifier cl;
    vector<Instance> dataset = cl.loadDataset(fileName);
    if (dataset.empty()) {
        cerr << "Failed to load dataset.\n";
        return;
    }

    cl.normalizeData(dataset);

    validator val(cl);


    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "\n 1. Forward Selection \n 2. Backward Selection \n 3. N/A" << endl;
    cin >> choice;
    cout << endl;

    if (choice == 1) {
        cout << "Running Forward Selection..." << endl;
        cout << endl;
        result = ForwardSelection(dataset, val);
    }
    if (choice == 2) {
        cout << "Running Backward Elimination..." << endl;
        cout << endl;
        result = backwardElimination(dataset, val);
    }
    else {
        cout << "Please choose only 1 or 2..." << endl;
    }
    evaluation(result, fileName, dataset, val);
}

int main()
{
    menu();
    return 0;
}
