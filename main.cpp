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

	data_loader test;
	test.read_file("./data/iris.data");
	BPnet net(45, 0.01, 0.01);
	net.train(test);
	cout << "----------" << endl;
	test.shuffle_index();
	/*
	int id = test.test_index.get_element(0, 12);
	cout << "id: " << id << endl;
	test.xtrain[id].display();
	test.ytrain[id].display();
	cout << net.forecast(!test.xtrain[id]) << endl;
	*/
	return 0;
}