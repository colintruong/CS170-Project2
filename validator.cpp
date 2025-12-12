#include "validator.h"

validator::validator(Classifier& classify) : classifier(classify){}

// Porject an Instance onto a subset of features
Instance validator::inst(const Instance& instance, const vector<int>& feature) const{
    Instance projInst;
    projInst.classLabel = instance.classLabel;

    projInst.features.reserve(feature.size());

    // Copy only the requested features
    for(int i : feature){
        int featureInd = i-1;   // Change to 0-based indexing
        if(featureInd >= 0 && featureInd < instance.features.size()){
            projInst.features.push_back(instance.features[featureInd]);
        }
        else{
            cerr << "The feature's index is out of range" << endl;
        }
    }
    return projInst;
}

// Returns feature vector
vector<double> validator::feat(const Instance& instance, const vector<int>& feature) const{
    vector<double> projVec;
    projVec.reserve(feature.size());

    for(int i : feature){
        int featureInd = i-1;
        if(featureInd >= 0 && featureInd < instance.features.size()){
            projVec.push_back(instance.features[featureInd]);
        }
        else{
            cerr << "The feature's index is out of range" << endl;
        }
    }
    return projVec;
}

double validator::leaveOneOutValidation(const vector<Instance>& data, const vector<int>& feature){
    int n = data.size();
    if(n == 0){
        cerr << "Set is empty, so the accuracy is 0" << endl;
        return 0.0;
    }
    int correct = 0;    // count of correct predictions

    // For each instance, leave it out and classify using the rest
    for(int i = 0; i < n; ++i){
        // Build training set excluding i, projected onto selected features
        vector<Instance> train;
        train.reserve(n-1);
        for(int j = 0; j < n; ++j){
            if(j == i){
                continue;
            }
            train.push_back(inst(data[j],feature));
        }
        
        // Train classifier on projected training set
        classifier.train(train);

        // Project test instance onto selected features
        vector<double> test = feat(data[i], feature);

        // Classify test instance
        int predict = classifier.test(test);
        int actual = data[i].classLabel;

        if(predict == actual){
            ++correct;
        }
    }
    return (double)(correct)/(n);
}