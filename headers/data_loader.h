#pragma once
#include<iostream>
#include"Matrix.hpp"

using namespace std;
class data_loader {
public:
	Matrix<double> xtrain,ytrain;
	Matrix<double> xtest, ytest;
	void read_file(string, Matrix<double>&, Matrix<double>&);
	vector<double> label_to_num(const string);
};

