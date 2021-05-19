#include "headers/BP_net.h"
#include "headers/Matrix.hpp"

BPnet::BPnet()
{
	iteration_num = 1000;
	lr_w = lr_b = 0.01;
	input_layer = 0;
	hidden_layer = 0;
	output_layer = 0;
}

BPnet::BPnet(int _iters, double _lr_w, double _lr_b):iteration_num(_iters),lr_w(_lr_w),lr_b(_lr_b){
	input_layer = 0;
	hidden_layer = 0;
	output_layer = 0;
}

BPnet::~BPnet() {

}

void BPnet::set_dim(Matrix<double>& _x, Matrix<double>& _y) {
	this->x = _x;
	this->y = _y;
	input_layer = (int)x.getRowandCol().get_element(0, 0);
	output_layer = (int)y.getRowandCol().get_element(0, 0);
	hidden_layer = 5;
}

void BPnet::init_net() {
	double (*ptr)(double) = myrand;
	w1(hidden_layer, input_layer);
	w1.self_function(ptr);
	b1(hidden_layer, 1);
	b1.self_function(ptr);
	w2(output_layer, hidden_layer);
	w2.self_function(ptr);
	b2(output_layer, 1);
	b2.self_function(ptr);

	a1 = x;
	a2(hidden_layer, 1);
	a2.self_function(ptr);
	a3(output_layer, 1);
	a3.self_function(ptr);

	delta1(hidden_layer, 1);
	//delta1.self_function(ptr);
	delta2(output_layer, 1);
	//delta2.self_function(ptr);
}

void BPnet::forward_propagation() {
	double (*ptr)(double) = sigmoid;
	Matrix<double> tmp(hidden_layer,1);
	cout<< endl << "tmp" << endl;
	tmp.display();
	tmp = w1 * a1 + b1;
	cout << endl << "tmp" << endl;
	tmp.display();
	tmp.self_function(ptr);
	a2 = tmp;
	//tmp = w2 * a2 + b2;
	a3 = ((w2 * a2) + b2).self_function(ptr);
}

void BPnet::sensitivity_feedback() {
	double (*ptr)(double) = _1subx;
	//Matrix<double> E1(1, output_layer);//1*3
	delta2 = (a3 - y) * ((!a3).self_function(ptr)) * a3;
	//Matrix<double> E2(1, hidden_layer);//1*5
	delta1 = !w2 * delta2 * ((!a2).self_function(ptr)) * a2;//5*1
}

void BPnet::improve_w_and_b() {
	w2 = w2 - lr_w * delta2 * !a2;
	b2 = b2 - lr_b * delta2;

	w1 = w1 - lr_w * delta1 * !a1;//5*4 = 5*1 * 1*4
	b1 = b1 - lr_b * delta1;
}


void BPnet::checkparameter() {
	cout << "dimensions" << endl << "input | hidden | output" << endl;
	cout << input_layer << ' ' << hidden_layer << ' ' << output_layer << endl;
	cout << "matrix check" << endl;
	cout << "x" << endl;
	x.display();
	cout << "y" << endl;
	y.display();

	cout << "w1" << endl;
	w1.display();
	cout << "b1" << endl;
	b1.display();
	cout << "w2" << endl;
	w2.display();
	cout << "b2" << endl;
	b2.display();

	cout << "a1" << endl;
	a1.display();
	cout << "a2" << endl;
	a2.display();
	cout << "a3" << endl;
	a3.display();

	cout << "delta1" << endl;
	delta1.display();
	cout << "delta2" << endl;
	delta2.display();
}

double sigmoid(double x) {
	return 1 / (1 + exp(-x));
}
double _1subx(double x) {
	return 1 - x;
}
double myrand(double x) {
	return (double)(rand() % 1001) / 1000.0;
}