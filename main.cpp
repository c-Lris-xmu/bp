//BP Neural Network
#include<iostream>
#include<fstream>
#include"headers/Matrix.hpp"
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
	cout << "¾ØÕóÏà³Ë" << endl;
	c.display();
	cout << "¾ØÕó×ªÖÃ" << endl;
	m=!c;
	m.display();
	c.display();
	cout << "¾ØÕó¼Ó¼õ" << endl;
	m2 = m - c;
	m2.display();
	m2 = m + c;
	m2.display();

	return 0;
}