#pragma once

#include "headers/Matrix.hpp"

using namespace std;

class BPnet {
private:
	int iteration_num;//��������
	int lr_w;//wѧϰ��
	int lr_b;//bѧϰ��

	int input_layer;	//�����
	int hidden_layer;	//���ز�
	int output_layer;	//�����

	
	

public:
	BPnet(int _iters = 1000, double _lr_w = 0.01, double _lr_b = 0.01);
	~BPnet();
	void set_dim(Matrix<double>&, Matrix<double>&);	//���ø������
	void checkparameter();
};