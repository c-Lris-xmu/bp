//BP Neural Network
#include<iostream>
#include<fstream>
#include"headers/Matrix.hpp"
#include"headers/BP_net.h"
#include"headers/data_loader.h"

using namespace std;

int main()
{
	cout << "-----START-----" << endl;
	data_loader test;
	test.read_file("./data/iris.data");
	BPnet net(50, 0.01, 0.01);
	net.train(test);
	cout << "-----END-----" << endl;
	
	system("pause");
	return 0;
}