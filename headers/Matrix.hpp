#pragma once
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

template<class T>
class Matrix
{
public:
	Matrix() { Row = 0; Col = 0;}                                        //默认构造
	Matrix(int, int);                                                    
	Matrix(const Matrix<T>&);                                            //复制构造 
	Matrix(vector< vector<T> >&);                                        

	template<class T1>
	friend Matrix<T1> operator*(const Matrix<T1>&, const Matrix<T1>&);   //矩阵相乘以及矩阵点乘
	template<class T1>
	friend Matrix<T1> operator*(const Matrix<T1>&, const T1&);           //矩阵数乘
	template<class T1>
	friend Matrix<T1> operator*(const T1&, const Matrix<T1>&);            
	template<class T1>
	friend Matrix<T1> operator+(const Matrix<T1>&, const Matrix<T1>&);   //矩阵相加
	template<class T1>
	friend Matrix<T1> operator-(const Matrix<T1>&, const Matrix<T1>&);   //矩阵相减
	template<class T1>
	friend bool judge(const Matrix<T1>&, const Matrix<T1>&);             //判断是否满足相乘
 
	Matrix<T> operator!();                                               //矩阵转置
	Matrix<T> operator()(int,int);                                       //拷贝复制
	Matrix<T> operator()(const Matrix&m);
	Matrix<T> operator()(vector< vector<T> >&);
	Matrix<T> operator[](int);                                           //读取某一行

	T get_element(int, int);                                             //读取单个元素

	void display();                                                      //打印矩阵

	Matrix<T> self_function(T(*f)(T a));                                 //自定义函数操作矩阵值

	Matrix<int> getRowandCol();                                          //返回行列

	T find_max();                                                        //返回最大值
	T find_min();                                                        //返回最小值

	void Normalize();                                                    //按列对矩阵元素归一化
	void shuffle();                                                      //矩阵按行乱序

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
Matrix<int> Matrix<T>::getRowandCol()
{
	vector<int> v;
	v.push_back(this->Row);
	v.push_back(this->Col);
	Matrix<int> temp(vector<vector<int>>(1,v));
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

template<class T>
void Matrix<T>::Normalize()
{
	T* Mat_max = new T[Col];
	T* Mat_min = new T[Col];
	memset(Mat_max, -1, sizeof(T) * Col);
	memset(Mat_min, 127, sizeof(T) * Col);
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			Mat_max[j] = Mat_max[j] > matrix[i][j] ? Mat_max[j] : matrix[i][j];
			Mat_min[j] = Mat_min[j] < matrix[i][j] ? Mat_min[j] : matrix[i][j];
		}
	}

	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			matrix[i][j] = 1.0 * (matrix[i][j] - Mat_min[j]) / (Mat_max[j] - Mat_min[j]);
		}
	}
	delete[] Mat_max;
	delete[] Mat_min;
}

template<class T>
void Matrix<T>::shuffle()
{
	for (int i = 0; i < Row; i++)
		random_shuffle(matrix[i].begin(), matrix[i].end());
}