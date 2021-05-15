# BP For Iris

## 一、公式

#### Step1.整体网络结构

$$
a^0=p
\\
a^{m+1}=f^{m+1}\left( W^{m+1}a^m+b^{m+1} \right) ,m=0,1,...,M-1
\\
a=a^M
$$

其中，$a$为每层神经网络输出，共$M$层，$a^0$为初始输入

​           $W$为权重矩阵，$b$为偏置矩阵，$f$为输出函数

#### Step2.敏感度回传

$$
s^M=-2\dot{F}^M\left( n^M \right) \left( t-a \right) 
\\
s^m=\dot{F}^m\left( n^m \right) \left( W^{m+1} \right) ^Ts^{m-1},m=M-1,...,2,1
$$

其中，$s$为回传敏感度，$s^M$为迭代起点，$t$为正确结果

​           $\dot{F}^m$为每层神经网络输出对净输出$n$的偏导，最终层为均方误差函数

#### Step3.最速下降更新参数

$$
W^m\left( k+1 \right) =W^m\left( k \right) -l_rs^m\left( a^{m-1} \right) ^T
\\
b^m\left( k+1 \right) =b^m\left( k \right) -l_rs^m
$$

其中，$l_r$为学习率

