#include<vector>
#include<iostream>

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
	friend Matrix<T1> operator+(const Matrix<T1>&, const Matrix<T1>&);   //�������
	template<class T1>
	friend Matrix<T1> operator-(const Matrix<T1>&, const Matrix<T1>&);   //�������
	template<class T1>
	friend bool judge(const Matrix<T1>&, const Matrix<T1>&);             //�ж��Ƿ��������
 

	Matrix<T>& operator!();                                              //����ת��
	void display();

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
	this->Row = a.Row, this->Col = a.Row;
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
Matrix<T>& Matrix<T>::operator !()
{
	Matrix<T> temp(Col,Row);
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
			temp.matrix[j][i] = matrix[i][j];
	this->Row = temp.Row, this->Col = temp.Col;
	this->matrix.assign(Row, vector<T>(Col, 0));
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
			this->matrix[i][j] = temp.matrix[i][j];
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
void Matrix<T>::display()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}




