#include "headers/BP_net.h"
#include "headers/data_loader.h"
#include "headers/Matrix.hpp"
#include<fstream>

using namespace std;

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

void BPnet::input_x_and_y(Matrix<double>& _x, Matrix<double>& _y) {
	this->x = _x;
	this->y = _y;
}

void BPnet::init_net() {
	srand(unsigned(time(0)));
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
	a1 = x;
	double (*ptr)(double) = sigmoid;
	a2 = (w1 * a1 + b1).self_function(ptr);
	a3 = (w2 * a2 + b2).self_function(ptr);
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

int BPnet::forecast(Matrix<double>& _x) {
	x = _x;
	forward_propagation();
	
	double max_elm = a3.find_max();
	int res = -1;
	for (int i = 0; i < 3; i++) {
		if (a3.get_element(i, 0) == max_elm) {
			res = i;
			break;
		}
	}
	return res;	//return 0 1 2 mean different category
}

double BPnet::cal_acc(data_loader& data,int flag) {
	//flag==0表示在训练集上计算准确度
	//flag==1表示在测试集上计算准确度
	int num;
	int tot = 0;
	if (flag == 0) {
		num = data.train_index.getRowandCol().get_element(0, 1);
		for (int i = 0; i < num; i++) {
			int id = data.train_index.get_element(0, i);
			int res = forecast(!data.xtrain[id]);
			if (res == -1) {
				cout << "Forecast Error!" << endl;
				continue;
			}
			else
			{
				if (data.ytrain[id].get_element(0, res) == 1) {
					tot++;
				}
			}
		}
	}
	else
	{
		num = data.test_index.getRowandCol().get_element(0, 1);
		for (int i = 0; i < num; i++) {
			int id = data.test_index.get_element(0, i);
			int res = forecast(!data.xtrain[id]);
			if (res == -1) {
				cout << "Forecast Error!" << endl;
				continue;
			}
			else
			{
				if (data.ytrain[id].get_element(0, res) == 1) {
					tot++;
				}
			}
		}
	}
	return tot / (num * 1.0);
}

void BPnet::train(data_loader& data) {
	set_dim(!data.xtrain[0], !data.ytrain[0]);
	init_net();
	double best_acc = 0;
	int num = data.train_index.getRowandCol().get_element(0, 1);

	for (int iter = 0; iter < iteration_num; iter++) {
		for (int i = 0; i < num; i++) {
			int id = data.train_index.get_element(0, i);
			input_x_and_y(!data.xtrain[id], !data.ytrain[id]);
			forward_propagation();
			sensitivity_feedback();
			improve_w_and_b();
		}

		double tmp = cal_acc(data, 0);

		if (tmp > best_acc) {
			best_acc = tmp;
			//keep the net
		}
		cout << "Iteration: " << iter << " acc:" << tmp << endl;
	}
	cout << "acc on test: " << cal_acc(data, 1) << endl;
	model_save("./data/train_model.pdparams");

	return;
}

void BPnet::checkparameter() {
	cout << "---check parameter---" << endl;
	cout << "iteration nums | lr_w | lr_b" << endl;
	cout << iteration_num << ' ' << lr_w << ' ' << lr_b << endl;
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

void BPnet::model_save(const string s)
{
	ofstream savefile(s);
	savefile.clear();
	streambuf* strmout_buf = cout.rdbuf();
	cout.rdbuf(savefile.rdbuf());
	savefile << "w1" << endl;
	w1.display();
	savefile << "w2" << endl;
	w2.display();
	savefile << "b1" << endl;
	b1.display();
	savefile << "b2" << endl;
	b2.display();
	cout.rdbuf(strmout_buf);
	savefile.close();
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