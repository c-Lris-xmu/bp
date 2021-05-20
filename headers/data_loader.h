#pragma once
#include"Matrix.hpp"

using namespace std;
class data_loader {
public:
	Matrix<double> xtrain,ytrain;
	Matrix<int> train_index, test_index;
 	void read_file(const string);
	vector<double> label_to_num(const string);
	void shuffle_index();
};

