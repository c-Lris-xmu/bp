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

	int input_layer;		//�����ά�� 3
	int hidden_layer;		//���ز�ά�� 5
	int output_layer;		//�����ά�� 2

	Matrix<double> x;		//������� 4*1
	Matrix<double> y;		//��ǩ���� 3*1

	Matrix<double> w1;		//һ�����Ȩֵ 5*4
	Matrix<double> b1;		//һ�����ƫ�� 5*1
	Matrix<double> w2;		//�������Ȩֵ 3*5
	Matrix<double> b2;		//�������ƫ�� 3*1

	Matrix<double> a1;		//������� ͬx 4*1
	Matrix<double> a2;		//�ڶ����� 5*1
	Matrix<double> a3;		//�������� ��������� 3*1

	Matrix<double> delta1;	//ǰһ�����ж� 5*1
	Matrix<double> delta2;	//�����y��ƫ��������ж� 3*1

	//������ʱ������public��
	//������ɺ��ٵ�������

public:
	BPnet();
	BPnet(int _iters = 1000, double _lr_w = 0.01, double _lr_b = 0.01);
	~BPnet();

	//�����������ά��
	void set_dim(Matrix<double>&, Matrix<double>&);
	void input_x_and_y(Matrix<double>&, Matrix<double>&);
	//�����ʼ�� ��ʼ�����������С�������
	void init_net();

	void forward_propagation();	//ǰ�򴫲�
	void sensitivity_feedback();//����������жȻش�
	void improve_w_and_b();		//��������

	int forecast(Matrix<double>&);			//ģ��Ԥ�� ����ѵ������
	double cal_acc(Matrix<double>&, Matrix<double>&);//����׼ȷ�� ������֤����
	void train(Matrix<double>&, Matrix<double>&); //ѵ��
	//���������� ������
	void checkparameter();
};