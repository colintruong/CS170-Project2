#include <iostream>
#include <chrono>
#include "ForwardSelection.h"
#include "backwardElimination.h"
#include "Classifier.h"
#include "validator.h"

using namespace std;

void menu() {

    int numberOfFeatures, choice;
    cout << "Welcome to Colin Truong/David Lee/Bavly Shehata's Feature Selection Algorithm." << endl;
    cout << endl;
    cout << "Please enter total number of features: ";
    cin >> numberOfFeatures;
    cout << endl;

    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "\n 1. Forward Selection \n 2. Backward Selection \n 3. N/A" << endl;
    cin >> choice;
    cout << endl;

    if (choice == 1) {
        cout << "Running Forward Selection..." << endl;
        cout << endl;

        unordered_set<int> result = ForwardSelection(numberOfFeatures);
    }
    if (choice == 2) {
        cout << "Running Backward Elimination..." << endl;
        cout << endl;
        backwardElimination(numberOfFeatures);
    }
    else {
        cout << "Please choose only 1 or 2..." << endl;
    }
}

int main()
{
    //menu();
    Classifier cl;
    string filename = "small-test-dataset.txt";
    vector<Instance> dataset = cl.loadDataset(filename);

    if (dataset.empty()) {
        cerr << "Dataset empty or failed to load.\n";
        return 1;
    }

    cl.normalizeData(dataset);



    return 0;
}
