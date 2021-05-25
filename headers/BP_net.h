#pragma once

#include "headers/data_loader.h"
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

	//�����������ά��
	void set_dim(Matrix<double>&, Matrix<double>&);
	//�������������������
	void input_x_and_y(Matrix<double>&, Matrix<double>&);
	//�����ʼ�� ��ʼ�����������С�������
	void init_net();

	//ǰ�򴫲�
	void forward_propagation();
	//����������жȻش�
	void sensitivity_feedback();	
	//��������
	void improve_w_and_b();				

	//ģ��Ԥ�� ����������� ����������
	int forecast(Matrix<double>&);	
	//����׼ȷ�� ������֤����data������ѡ��flag ����׼ȷ��
	double cal_acc(data_loader&, int);	

	//����ģ��
	void model_save(const string);		

public:
	BPnet();
	BPnet(int _iters = 1000, double _lr_w = 0.01, double _lr_b = 0.01);
	~BPnet();

	//ѵ��
	void train(data_loader&);			
	
	//���������� ������
	void checkparameter();
};