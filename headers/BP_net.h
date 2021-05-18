#pragma once

#include "headers/Matrix.hpp"

using namespace std;
double sigmoid(double);
double _1subx(double);
double myrand(double);
class BPnet {
private:
	int iteration_num;		//��������
	double lr_w;			//wѧϰ��
	double lr_b;			//bѧϰ��

	int input_layer;		//�����
	int hidden_layer;		//���ز�
	int output_layer;		//�����

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

	//������ʱ������public��
	//������ɺ��ٵ�������
	
public:
	BPnet();
	BPnet(int _iters = 1000, double _lr_w = 0.01, double _lr_b = 0.01);
	~BPnet();
	void set_dim(Matrix<double>&, Matrix<double>&);	//���ø������
	
	void init_net();//�����ʼ��
	void forward_propagation();//ǰ�򴫲�
	void sensitivity_feedback();//���жȻش�
	void improve_w_and_b();//��������
	
	void checkparameter();
};