//BP Neural Network
#include<iostream>
#include<fstream>
#include"headers/Matrix.hpp"
#include"headers/BP_net.h"
#include"headers/data_loader.h"
#include<Python.h>
#include<string>
using namespace std;
template<class T>
string creat_arr(T* arr, int n)
{
	//把c++里面是数组转化成python的list
	string str = "[";
	for (int i = 0; i < n; i++)
	{
		str += to_string(arr[i]);
		if (i < n - 1) str += ",";
	}
	str += "]";
	return str;
}
template<class T>
void plot(T* x, int n, string s)
{
	//PyRun_SimpleString("import matplotlib.pyplot as plt");
	string cmd = "plt.plot(";
	string s1 = creat_arr(x, n);
	cmd += (s1 + s+")");
	PyRun_SimpleString(cmd.c_str());
	//PyRun_SimpleString("plt.show()");
}
void draw(int n, double* loss1, double* loss2, double* loss3, double* acc1, double* acc2, double* acc3)
{
	Py_Initialize();
	PyRun_SimpleString("import matplotlib.pyplot as plt");
	PyRun_SimpleString("plt.figure(figsize = (10, 10), dpi = 100)");
	PyRun_SimpleString("plt.figure(1)");
	// draw loss
	PyRun_SimpleString("plt.subplot(2, 1, 1)");
	plot(loss1, n, ",label='loss of four neure'");
	plot(loss2, n, ",label='loss of five neure'");
	plot(loss3, n, ",label='loss of six neure'");
	PyRun_SimpleString("plt.xlabel('epoch')");
	PyRun_SimpleString("plt.ylabel('loss')");
	PyRun_SimpleString("plt.legend()");
	//draw acc
	PyRun_SimpleString("plt.subplot(2, 1, 2)");
	plot(acc1, n, ",label='acc of four neure'");
	plot(acc2, n, ",label='acc of five neure'");
	plot(acc3, n, ",label='acc of six neure'");
	PyRun_SimpleString("plt.xlabel('epoch')");
	PyRun_SimpleString("plt.ylabel('acc')");
	PyRun_SimpleString("plt.legend()");
	//suptitle
	PyRun_SimpleString("plt.suptitle('loss and accuracy of the BPnet')");
	//save pic
	PyRun_SimpleString("plt.savefig('./loss_and_acc.jpg')");
	PyRun_SimpleString("plt.show()");
	Py_Finalize();
}
int main()
{
	cout << "-----START-----" << endl;
	data_loader data;
	data.read_file("./data/iris.data");
	cout << "=============Train 1==============" << endl;
	BPnet net1(100, 0.01, 0.01,4);
	net1.train(data);
	cout << "=============Train 2==============" << endl;
	BPnet net2(100, 0.01, 0.01, 5);
	net2.train(data);
	cout << "=============Train 3==============" << endl;
	BPnet net3(100, 0.01, 0.01, 6);
	net3.train(data);
	cout << "-----END-----" << endl;
	draw(100,net1.loss, net2.loss, net3.loss,net1.acc,net2.acc,net3.acc);
	system("pause");
	return 0;
}
