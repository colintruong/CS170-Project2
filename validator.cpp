#include "validator.h"

validator::validator(Classifier& classify) : classifier(classify){}
Instance validator::inst(const Instance& instance, const vector<int>& feature) const{
    Instance projInst;
    projInst.classLabel = instance.classLabel;

    projInst.features.reserve(feature.size());
    for(int i : feature){
        int featureInd = i-1;
        if(featureInd >= 0 && featureInd < instance.features.size()){
            projInst.features.push_back(instance.features[featureInd]);
        }
        else{
            cerr << "The feature's index is out of range" << endl;
        }
    }
    return projInst;
}

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
    int correct = 0;
    for(int i = 0; i < n; ++i){
        vector<Instance> train;
        train.reserve(n-1);
        for(int j = 0; j < n; ++j){
            if(j == i){
                continue;
            }
            train.push_back(inst(data[j],feature));
        }
        classifier.train(train);
        vector<double> test = feat(data[i], feature);
        int predict = classifier.test(test);
        int actual = data[i].classLabel;

        if(predict == actual){
            ++correct;
        }
    }
    return (double)(correct)/(n);
}