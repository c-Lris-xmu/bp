# BP For Iris

## 一、公式

#### Step1.整体网络结构
![](https://latex.codecogs.com/gif.image?\dpi{110}&space;a^0=p)


![](https://latex.codecogs.com/gif.image?\dpi{110}&space;a^{m&plus;1}=f^{m&plus;1}\left(&space;W^{m&plus;1}a^m&plus;b^{m&plus;1}&space;\right)&space;,m=0,1,...,M-1)


![](https://latex.codecogs.com/gif.image?\dpi{110}&space;a=a^M)


其中，a为每层神经网络输出，共M层，a^0为初始输入

​           W为权重矩阵,b为偏置矩阵，f为输出函数

#### Step2.敏感度回传
![](https://latex.codecogs.com/gif.image?\dpi{110}&space;s^M=-2\dot{F}^M\left(&space;n^M&space;\right)&space;\left(&space;t-a&space;\right))

![](https://latex.codecogs.com/gif.image?\dpi{110}&space;s^m=\dot{F}^m\left(&space;n^m&space;\right)&space;\left(&space;W^{m&plus;1}&space;\right)&space;^Ts^{m+1},m=M-1,...,2,1)

其中,s为回传敏感度，s^M为迭代起点，t为正确结果

​           dot{F}^m为每层神经网络输出对净输出n的偏导，最终层为均方误差函数

#### Step3.最速下降更新参数
![](https://latex.codecogs.com/gif.image?\dpi{110}&space;W^m\left(&space;k&plus;1&space;\right)&space;=W^m\left(&space;k&space;\right)&space;-l_rs^m\left(&space;a^{m-1}&space;\right)&space;^T)

![](https://latex.codecogs.com/gif.image?\dpi{110}&space;b^m\left(&space;k&plus;1&space;\right)&space;=b^m\left(&space;k&space;\right)&space;-l_rs^m)


其中，lr为学习率

## 二、Matrix接口

#### 初始化支持三种形式，接下来视情况扩展int** 

```c++
	Matrix(int, int);                                                    
	Matrix(const Matrix<T>&);                                            
	Matrix(vector< vector<T> >&);                                        
```

#### 目前支持矩阵加减乘，乘包括点乘

```c++
        Matrix<int>c = m * m2;
	m2 = m - c;
	m2 = m + c;
```

#### 重载 operator ！实现自身转置以及赋值给其他类

```c++
	m=!c;
```

#### display()函数打印矩阵

