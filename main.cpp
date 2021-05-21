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

	data_loader test;
	test.read_file("./data/iris.data");
	BPnet net(100, 0.01, 0.01);
	net.train(test);
	cout << "----------" << endl;
	test.xtrain[12].display();
	test.ytrain[12].display();
	cout << net.forecast(!test.xtrain[12]) << endl;



	cout << "----------" << endl;
	test.xtrain[128].display();
	test.ytrain[128].display();
	cout << net.forecast(!test.xtrain[128]) << endl;

	cout << "----------" << endl;
	test.xtrain[92].display();
	test.ytrain[92].display();
	cout << net.forecast(!test.xtrain[92]) << endl;
	return 0;
}