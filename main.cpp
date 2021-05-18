//BP Neural Network
#include<iostream>
#include<fstream>
#include"headers/Matrix.hpp"
#include"headers/BP_net.h"

using namespace std;

int main()
{
	vector< vector<int> >v(4,vector<int>(3,0));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			v[i][j] = i * j;

	vector< vector<int> >v1(3, vector<int>(4, 0));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			v1[i][j] = i * j+j;
	
	Matrix<int> m(v1);
	Matrix<int> m2(v);
	Matrix<int>c = m * m2;
	cout << "矩阵相乘" << endl;
	c.display();
	cout << "矩阵数乘" << endl;
	c = 5 * c;
	c.display();
	cout << "矩阵转置" << endl;
	m=!c;
	m.display();
	c.display();
	cout << "矩阵加减" << endl;
	m2 = m - c;
	m2.display();
	m2 = m + c;
	m2.display();
	cout << "获取单个元素" << endl;
	cout << m2.get_element(4, 4) << endl;
	cout << m2.get_element(2, 2) << endl;

	Matrix<double> mm1(4, 1);
	Matrix<double> mm2(3, 1);
	BPnet net;
	net.set_dim(mm1, mm2);
	net.checkparameter();
	return 0;
}