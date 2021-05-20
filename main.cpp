//BP Neural Network
#include<iostream>
#include<fstream>
#include"headers/Matrix.hpp"
#include"headers/BP_net.h"
#include"headers/data_loader.h"

using namespace std;

int add(int a)
{
	return a + 1;
}
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

	c(m2);
	c.display();
	c(2, 2);
	c.display();

	c = m * m2;
	c.display();
	cout << "-------------" << endl;
	c[1].display();
	cout << "-------------" << endl;
	cout<<c.find_max()<<endl;
	cout<<c.find_min()<<endl;


	Matrix<double> m1_test;
	Matrix<double> m2_test;
	data_loader test;
	test.read_file("./data/iris.data", m1_test, m2_test);

	
	cout << "-----bp net test-----" << endl;
	BPnet net(100, 0.01, 0.01);
	cout << "---before---" << endl;
	
	net.set_dim(!m1_test[0], !m2_test[0]);
	net.init_net();
	Matrix<double>xx = !m1_test[0];
	Matrix<double>yy = !m2_test[0];
	for (int i = 0; i < 1000; i++) {
		net.forward_propagation();
		net.sensitivity_feedback();
		net.improve_w_and_b();
	}
	net.checkparameter();
	cout << "------acc check------" << endl;
	int res = net.forecast(!m1_test[20]);
	cout << res << endl;
	/*
	net.train(m1_test, m2_test);
	*/
	cout << "---after---" << endl;
	net.checkparameter();
	
	return 0;
}