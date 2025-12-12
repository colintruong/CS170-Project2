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
    unordered_set<int> result;
    cout << "Welcome to Colin Truong/David Lee/Bavly Shehata's Feature Selection Algorithm." << endl;
    cout << endl;

    // Choosing which dataset to use
    cout << "Pick small (1) or large (2) or titanic (3) dataset: ";
    cin >> option;
    if (option == 1) {
        fileName = "small-test-dataset-2-2.txt";
    } else if (option == 2) {
        fileName = "large-test-dataset-2.txt";
    } else if (option == 3) {
        fileName = "titanic-clean-2.txt";
    }

    Classifier cl;
    vector<Instance> dataset = cl.loadDataset(fileName);
    if (dataset.empty()) {
        cerr << "Failed to load dataset.\n";
        return;
    }

    cl.normalizeData(dataset);
    cout << "Normalizing data...  done." << endl;

    validator val(cl);

    // Choosing which algorithm to use
    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "\n 1. Forward Selection \n 2. Backward Selection \n 3. N/A" << endl;
    cin >> choice;
    cout << endl;

    // Returns a optimal feature subset
    if (choice == 1) {
        cout << "Running Forward Selection..." << endl;
        cout << endl;
        result = ForwardSelection(dataset, val);
    } else if (choice == 2) {
        cout << "Running Backward Elimination..." << endl;
        cout << endl;
        result = backwardElimination(dataset, val);
    } else {
        cout << "Please choose only 1 or 2..." << endl;
    }
}

int main()
{
    menu();
    return 0;
}

/*

Group: Bavly Shehata - bsheh002 - Session 1, Colin Truong - ctruo045 - Session 1, David Lee - dlee486 - Session 1

Small Dataset Results:
    Forward: Feature Subset: {3, 5}, Acc: 0.92
    Backward: Feature Subset: {2, 4, 5, 7, 10}, Acc: 0.82

Large Dataset Results:
    Forward: Feature Subset: {1, 27}, Acc: 0.95
    Backward: Feature Subset: {27}, Acc: 0.85

*/
