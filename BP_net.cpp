#include "headers/BP_net.h"
#include "headers/Matrix.hpp"

BPnet::BPnet(int _iters, double _lr_w, double _lr_b):iteration_num(_iters),lr_w(_lr_w),lr_b(_lr_b){

}
BPnet::~BPnet() {

}
void BPnet::checkparameter() {
	cout << input_layer << ' ' << hidden_layer << ' ' << output_layer << endl;
}
void BPnet::set_dim(Matrix<double>& x, Matrix<double>& y) {
	input_layer = (int)x.getRowandCol().get_element(0, 0);
	output_layer = (int)y.getRowandCol().get_element(0, 0);
	hidden_layer = 5;
}