#pragma once
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

template<class T>
class Matrix
{
public:
	Matrix() { Row = 0; Col = 0;}                                        //Ĭ�Ϲ���
	Matrix(int, int);                                                    
	Matrix(const Matrix<T>&);                                            //���ƹ��� 
	Matrix(vector< vector<T> >&);                                        

	template<class T1>
	friend Matrix<T1> operator*(const Matrix<T1>&, const Matrix<T1>&);   //��������Լ�������
	template<class T1>
	friend Matrix<T1> operator*(const Matrix<T1>&, const T1&);           //��������
	template<class T1>
	friend Matrix<T1> operator*(const T1&, const Matrix<T1>&);            
	template<class T1>
	friend Matrix<T1> operator+(const Matrix<T1>&, const Matrix<T1>&);   //�������
	template<class T1>
	friend Matrix<T1> operator-(const Matrix<T1>&, const Matrix<T1>&);   //�������
	template<class T1>
	friend bool judge(const Matrix<T1>&, const Matrix<T1>&);             //�ж��Ƿ��������
 
	Matrix<T> operator!();                                               //����ת��
	Matrix<T> operator()(int,int);                                       //��������
	Matrix<T> operator()(const Matrix&m);
	Matrix<T> operator()(vector< vector<T> >&);
	Matrix<T> operator[](int);                                           //��ȡĳһ��

	T get_element(int, int);                                             //��ȡ����Ԫ��

	void display();                                                      //��ӡ����

	Matrix<T> self_function(T(*f)(T a));                                 //�Զ��庯����������ֵ

	Matrix<T> getRowandCol();                                            //��������

	T find_max();                                                        //�������ֵ
	T find_min();                                                        //������Сֵ


	 
private:
	int Row, Col;
	vector< vector<T> > matrix;

};

template<class T>
Matrix<T>::Matrix(int r, int c)
{
	this->Row = r, this->Col = c;
	this->matrix.assign(r, vector<T>(c, 0));
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& a)
{
	this->Row = a.Row, this->Col = a.Col;
	this->matrix.assign(Row, vector<T>(Col, 0));
	for (int i = 0; i < Row; i++)
		matrix[i].assign(a.matrix[i].begin(), a.matrix[i].end());
}

template<class T>
Matrix<T>::Matrix(vector< vector<T> >& v)
{
	this->Row = v.size(),this->Col=v[0].size();
	this->matrix.assign(Row, vector<T>(Col, 0));
	for (int i = 0; i < (int)v.size(); i++)
		matrix[i].assign(v[i].begin(), v[i].end());
}

template<class T1>
bool judge(const Matrix<T1>& a, const Matrix<T1>& b)
{
	if (a.Col == b.Row || (a.Col == 1 && a.Row == 1))
		return true;
	return false;
}

template<class T>
Matrix<T> Matrix<T>::operator !()
{
	Matrix<T> temp(Col,Row);
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
			temp.matrix[j][i] = matrix[i][j];

	return temp;
}

template<class T>
Matrix<T> Matrix<T>::operator[](int i)
{
	if (i >= Row)
	{
		cout<<"Vector index out of range" << endl;
		return Matrix<T>(1, 0);
	}
	return Matrix<T>(vector< vector<T> >(1, matrix[i]));
}

template<class T>
Matrix<T> Matrix<T>::operator()(const Matrix<T>&m)
{
	this->Row = m.Row, this->Col = m.Col;
	this->matrix.assign(Row, vector<T>(Col, 0));
	for (int i = 0; i < Row; i++)
		matrix[i].assign(m.matrix[i].begin(), m.matrix[i].end());

	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator()(int r, int c)
{
	this->Row = r, this->Col = c;
	this->matrix.assign(r, vector<T>(c, 0));
	return *this;
}
template<class T>
Matrix<T> Matrix<T>::operator()(vector< vector<T> >&v)
{
	this->Row = v.size(), this->Col = v[0].size();
	this->matrix.assign(Row, vector<T>(Col, 0));
	for (int i = 0; i < (int)v.size(); i++)
		matrix[i].assign(v[i].begin(), v[i].end());
	return *this;
}
template<class T1>
Matrix<T1> operator *(const Matrix<T1>&a, const Matrix<T1>&b) 
{
	if (!judge(a, b))
	{
		cout << "Wrong Dimension when matrix multiplication" << endl;
	}
	else if (a.Row == 1 && a.Col == 1)
	{
		Matrix<T1> c(b.Row,b.Col);
		for(int i=0;i<b.Row;i++)
			for (int j = 0; j < b.Col; j++)
			{
				c.matrix[i][j] = b.matrix[i][j] * a.matrix[0][0];
			}
		return c;
	}
	else {
		Matrix<T1> c(a.Row, b.Col);
		for (int i = 0; i < a.Row; i++)
			for (int j = 0; j < b.Col; j++)
				for (int k = 0; k < a.Col; k++)
					c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
		return c;
	}
	return Matrix<T1>(0, 0);
}

template<class T1>
Matrix<T1> operator*(const T1&a, const Matrix<T1>&b)
{
	Matrix<T1> temp(b);
	for (int i = 0; i < b.Row; i++)
		for (int j = 0; j < b.Col; j++)
			temp.matrix[i][j] *= a;
	return temp;
}

template<class T1>
Matrix<T1> operator*(const Matrix<T1>& a, const T1& b)
{
	Matrix<T1> temp(a);
	for (int i = 0; i < a.Row; i++)
		for (int j = 0; j < a.Col; j++)
			temp.matrix[i][j] *= b;
	return temp;
}

template<class T1>
Matrix<T1> operator+(const Matrix<T1>&a, const Matrix<T1>&b)
{
	if(a.Row!=b.Row||a.Col!=b.Col)
		cout << "Wrong Dimension when matrix addition" << endl;
	else {
		Matrix<T1> c(a.Row, a.Col);
		for (int i = 0; i < a.Row; i++)
			for (int j = 0; j < b.Col; j++)
				c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
		return c;
	}
	return Matrix<T1>(0, 0);
}

template<class T1>
Matrix<T1> operator-(const Matrix<T1>&a, const Matrix<T1>&b)
{
	if (a.Row != b.Row || a.Col != b.Col)
		cout << "Wrong Dimension when matrix addition" << endl;
	else {
		Matrix<T1> c(a.Row, a.Col);
		for (int i = 0; i < a.Row; i++)
			for (int j = 0; j < b.Col; j++)
				c.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
		return c;
	}
	return Matrix<T1>(0, 0);
}
template<class T>
T Matrix<T>::get_element(int x, int y)
{
	if (x >= Row || y >= Col)
	{
		cout << "Vector index out of range" << endl;
		return matrix[0][0];
	}
	return matrix[x][y];
}

template<class T>
void Matrix<T>::display()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}


template<class T>
Matrix<T> Matrix<T>::self_function(T  (*f)(T a))
{
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
			matrix[i][j] = f(matrix[i][j]);
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::getRowandCol()
{
	Matrix<T> temp(1, 2);
	temp.matrix[0][0] = this->Row;
	temp.matrix[0][1] = this->Col;
	return temp;
}

template<class T>
T Matrix<T>::find_max()
{
	vector<T>::iterator big_ele = max_element(matrix[0].begin(), matrix[0].end());
	for (int i = 1; i < Row; i++)
	{
		vector<T>::iterator tmp = max_element(matrix[i].begin(), matrix[i].end());
		big_ele = *tmp > *big_ele ? tmp : big_ele;
	}
	return *big_ele;
}

template<class T>
T Matrix<T>::find_min()
{
	vector<T>::iterator small_ele = min_element(matrix[0].begin(), matrix[0].end());
	for (int i = 1; i < Row; i++)
	{
		vector<T>::iterator tmp = min_element(matrix[i].begin(), matrix[i].end());
		small_ele = *tmp < *small_ele ? tmp : small_ele;
	}
	return *small_ele;
}