#ifndef BACKWARD_H
#define BACKWARD_H

#include "Classifier.h"
#include "validator.h"
#include <vector>
#include <unordered_set>
#include <climits>
#include <iomanip>
#include <string>

using namespace std;

double randomGenerator(const vector<int>& features);
string stringFormat(const vector<int>& features);
unordered_set<int> backwardElimination(const vector<Instance>& dataset, validator& val);

#endif