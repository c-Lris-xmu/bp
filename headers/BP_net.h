#pragma once

#include "headers/Matrix.hpp"

using namespace std;
double sigmoid(double);
double _1subx(double);
double myrand(double);
class BPnet {
private:
	int iteration_num;		//迭代次数
	double lr_w;			//w学习率
	double lr_b;			//b学习率

	int input_layer;		//输入层
	int hidden_layer;		//隐藏层
	int output_layer;		//输出层

	Matrix<double> x;		//4*1
	Matrix<double> y;		//3*1

	Matrix<double> w1;		//5*4
	Matrix<double> b1;		//5*1
	Matrix<double> w2;		//3*5
	Matrix<double> b2;		//3*1

	Matrix<double> a1;		//input 4*1
	Matrix<double> a2;		//5*1
	Matrix<double> a3;		//3*1

	Matrix<double> delta1;	//5*1
	Matrix<double> delta2;	//3*1

	//函数暂时都放在public中
	//大体完成后再调整回来
	
public:
	BPnet();
	BPnet(int _iters = 1000, double _lr_w = 0.01, double _lr_b = 0.01);
	~BPnet();
	void set_dim(Matrix<double>&, Matrix<double>&);	//设置各层参数
	
	void init_net();//网络初始化
	void forward_propagation();//前向传播
	void sensitivity_feedback();//敏感度回传
	void improve_w_and_b();//参数修正
	
	void checkparameter();
};