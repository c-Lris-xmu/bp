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

#### 重载operator()，非初始化阶段也能矩阵赋值

```c++
Matrix<T> m;
m(2,2) //2x2初值为0
m(m2)  //与m2相同
m(vector<vector<int> >)  //同上
```

#### 重载operator[],直接获取某一行,返回值将是一个1xN的Matrix

```c++
m[i] //从第0行开始
```

#### 支持矩阵加减乘，乘包括点乘

###### 现已支持double直接左乘或右乘

```c++
Matrix<int>c = m * m2;
m2 = m - c;
m2 = m + c;
m2 = 1.0*m;
```

#### 重载 operator ！实现自身转置以及赋值给其他类

```c++
m=!c;
```

#### display()函数打印矩阵

```
m.display();
```

#### get_element(int,int) 返回单个元素 超出范围返回矩阵第一个值

```c++
m.get_element(2,2); //index starts from zero
```

#### getRowandCol() 返回一个1*2的Matrix 第一个元素为行，第二个元素为列

```c++
m.getRowandCol();
```

#### self_function(T(*f)(T a)) 传入函数句柄对所有矩阵元素进行操作

```c++
int add(int a)
{
	return a+1;
}
Matrix<int> m;
int (*ptr)(int)=add;
m.self_function(ptr);
```

#### find_max和find_min将返回矩阵的最大值和最小值

```c++
m.find_max();
m.find_min();
```

#### Normalize()将矩阵按列归一化

```c++
m.Normalize();
```

#### shuffle()将矩阵按行乱序

```c++
m.shuffle()  //若要对列乱序，务必转置
```



### 三、data_loader接口

#### read_file(string s) 通过对字符串地址s读取该文件的数据

```c++
read_file("./data/iris.data");
```

####  Matrix类成员xtrain 和 ytrain 存储数据特征和数据结果

```c++
Matrix<double> xtrain,ytrain;
```

#### Matrix类成员train_index和test_index为4:1划分的训练集和测试集索引

```c++
Matrix<int> train_index, test_index;//大小为1xN
```



### 四、BPnet接口

#### 构造函数设置网络训练次数以及w和b的各自学习率

```c++
BPnet net(50, 0.01, 0.01);//训练50次 w和b的学习率都设置为0.01
```

#### 网络训练 传入类型为data_loader的数据data

```c++
net.train(data);
```

