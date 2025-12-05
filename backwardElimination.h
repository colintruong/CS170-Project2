#ifndef BACKWARD_H
#define BACKWARD_H

#include <vector>
#include <string>

using namespace std;

double randomGenerator(const vector<int>& features);
string stringFormat(const vector<int>& features);
void backwardElimination(int numFeatures);

#endif