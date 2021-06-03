#pragma once

#include "headers/data_loader.h"
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

	int input_layer;		//输入层维数 3
	int hidden_layer;		//隐藏层维数 n
	int output_layer;		//输出层维数 2

	Matrix<double> x;		//输入矩阵 4*1
	Matrix<double> y;		//标签矩阵 3*1

	Matrix<double> w1;		//一二层间权值 n*4
	Matrix<double> b1;		//一二层间偏置 n*1
	Matrix<double> w2;		//二三层间权值 3*n
	Matrix<double> b2;		//二三层间偏置 3*1

	Matrix<double> a1;		//输入矩阵 同x 4*1
	Matrix<double> a2;		//第二层结果 5*1
	Matrix<double> a3;		//第三层结果 即网络输出 3*1

	Matrix<double> delta1;	//前一层敏感度 5*1
	Matrix<double> delta2;	//结果和y的偏差导出的敏感度 3*1

	//设置网络各层维数
	void set_dim(Matrix<double>&, Matrix<double>&);
	//传入输入矩阵和输出矩阵
	void input_x_and_y(Matrix<double>&, Matrix<double>&);
	//网络初始化 初始化各个矩阵大小和随机化
	void init_net();

	//前向传播
	void forward_propagation();
	//误差计算和敏感度回传
	void sensitivity_feedback();	
	//参数修正
	void improve_w_and_b();			
	//loss计算
	double cal_loss();
	//计算准确率 传入验证数据data和评判选择flag 返回准确率
	double cal_acc(data_loader&, int);

	//模型预测 传入输入矩阵 返回类别代号
	int forecast(Matrix<double>&);	

	//保存模型
	void model_save(const string);		

public:
	double* loss;//动态数组，length=迭代数
	double* acc;

	BPnet();
	BPnet(int _iters = 1000, double _lr_w = 0.01, double _lr_b = 0.01,int cell_num=5);
	~BPnet();

	//训练
	void train(data_loader&);			
	
	//检查参数函数 调试用
	void checkparameter();
};