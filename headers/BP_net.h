#pragma once

#include "headers/Matrix.hpp"

using namespace std;

class BPnet {
private:
	int iteration_num;//迭代次数
	int lr_w;//w学习率
	int lr_b;//b学习率

	int input_layer;	//输入层
	int hidden_layer;	//隐藏层
	int output_layer;	//输出层

	
	

public:
	BPnet(int _iters = 1000, double _lr_w = 0.01, double _lr_b = 0.01);
	~BPnet();
	void set_dim(Matrix<double>&, Matrix<double>&);	//设置各层参数
	void checkparameter();
};