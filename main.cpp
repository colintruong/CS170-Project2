#include <iostream>
#include <chrono>
#include <iomanip>
#include "ForwardSelection.h"
#include "backwardElimination.h"
#include "Classifier.h"
#include "validator.h"

using namespace std;

void menu() {
    int option, choice;
    string fileName;
    cout << "Welcome to Colin Truong/David Lee/Bavly Shehata's Feature Selection Algorithm." << endl;
    cout << endl;

    Classifier cl;
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

        unordered_set<int> result = ForwardSelection(dataset, val);
    }
    if (choice == 2) {
        cout << "Running Backward Elimination..." << endl;
        cout << endl;
        backwardElimination(dataset, _Valid_);
    }
    else {
        cout << "Please choose only 1 or 2..." << endl;
    }
}

int evaluation() {
    Classifier cl;
    int option;

    cout << "Pick small (1) or large (2) dataset: ";
    cin >> option;

    if (option == 1) {

        string filename = "small-test-dataset-2-2.txt";
        vector<Instance> dataset = cl.loadDataset(filename);

        if (dataset.empty()) {
            cerr << "Dataset empty or failed to load.\n";
            return 0;
        }

        cl.normalizeData(dataset);

        validator val(cl);
        vector<int> featureSubset = {3, 5, 7};

        cout << "\n===== SMALL DATASET TRACE =====" << endl;
        cout << "Feature subset: {3, 5, 7}\n" << endl;

        auto start = chrono::high_resolution_clock::now();

        int n = dataset.size();
        int correct = 0;

        for (int i = 0; i < n; i++) {

            vector<Instance> train;
            train.reserve(n - 1);

            for (int j = 0; j < n; j++)
                if (j != i)
                    train.push_back(val.inst(dataset[j], featureSubset));

            cl.train(train);

            vector<double> testFeatures = val.feat(dataset[i], featureSubset);
            int predicted = cl.test(testFeatures);
            int actual = dataset[i].classLabel;

            cout << "Instance " << i
                 << " | Predicted = " << predicted
                 << " | Actual = " << actual
                 << " | " << (predicted == actual ? "Correct" : "Wrong")
                 << endl;

            if (predicted == actual)
                correct++;
        }

        double accuracy = (double)correct / n;

        auto end = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(end - start).count();

        cout << "\nCorrect Predictions: " << correct << " / " << n << endl;
        cout << fixed << setprecision(6);
        cout << "Final accuracy = " << accuracy << endl;
        cout << "Time elapsed = " << elapsed << " seconds\n";
        cout << "===== END SMALL DATASET TRACE =====\n";
    }

    else if (option == 2) {

        string filename = "large-test-dataset-2.txt";
        vector<Instance> dataset = cl.loadDataset(filename);

        if (dataset.empty()) {
            cerr << "Dataset empty or failed to load.\n";
            return 1;
        }

        cl.normalizeData(dataset);

        validator val(cl);
        vector<int> featureSubset = {1, 15, 27};

        cout << "\n===== LARGE DATASET TRACE =====" << endl;
        cout << "Feature subset: {1, 15, 27}\n" << endl;

        auto start = chrono::high_resolution_clock::now();

        int n = dataset.size();
        int correct = 0;

        for (int i = 0; i < n; i++) {

            vector<Instance> train;
            train.reserve(n - 1);

            for (int j = 0; j < n; j++)
                if (j != i)
                    train.push_back(val.inst(dataset[j], featureSubset));

            cl.train(train);

            vector<double> testFeatures = val.feat(dataset[i], featureSubset);
            int predicted = cl.test(testFeatures);
            int actual = dataset[i].classLabel;

            cout << "Instance " << i
                 << " | Predicted = " << predicted
                 << " | Actual = " << actual
                 << " | " << (predicted == actual ? "Correct" : "Wrong")
                 << endl;

            if (predicted == actual)
                correct++;
        }

        double accuracy = (double)correct / n;

        auto end = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(end - start).count();

        cout << "\nCorrect Predictions: " << correct << " / " << n << endl;

        cout << fixed << setprecision(2);
        cout << "Final accuracy = " << accuracy << endl;

        cout << fixed << setprecision(6);
        cout << "Time elapsed = " << elapsed << " seconds\n";

        cout << "===== END LARGE DATASET TRACE =====\n";
    }

    else {
        cout << "Invalid option." << endl;
        return -1;
    }
    return 0;
}

int main()
{
    menu();
    evaluation();
    return 0;
}
