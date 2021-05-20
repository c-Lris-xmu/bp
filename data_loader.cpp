#include "headers/data_loader.h"
#include<fstream>
#include<string>
#include<cctype>
#include<algorithm>
#include<numeric>

using namespace std;

vector<double> data_loader::label_to_num(const string s)
{
	vector<double> v(3, 0);
	if (s == "Iris-setosa")
		v[0] = 1;
	else if (s == "Iris-versicolor")
		 v[1] = 1;
	else v[2] = 1;
	return v;
}

void data_loader::read_file(const string s)
{
	
	ifstream openfile(s);
	string str;
	vector<vector<double> > all_train_data;
	vector<vector<double> > all_ans_data;
	while (!openfile.eof())
	{
		vector<string> string_tmp;
		vector<double> train_tmp;
		int cnt = 0, flag = 1;
		getline(openfile, str);
		string::size_type lastpos = str.find_first_not_of(",", 0);
		string::size_type pos = str.find_first_of(",", lastpos);
		while (string::npos != pos || string::npos != lastpos)
		{
			string_tmp.push_back(str.substr(lastpos, pos - lastpos));
			lastpos= str.find_first_not_of(",", pos);
			pos= str.find_first_of(",", lastpos);
		}
		for (int i=0;i<(int)string_tmp.size();i++)
		{
			for (int j=0;j<(int)string_tmp[i].size();j++)
			{
				if (!isdigit(string_tmp[i][j]) && string_tmp[i][j] != '.')
				{
					flag = 0;
					break;
				}
			}
			if (flag)
				train_tmp.push_back(stod((const string)string_tmp[i]));
			else all_ans_data.push_back(label_to_num(string_tmp[i]));
		}
		all_train_data.push_back(train_tmp);
	}
	xtrain(all_train_data);
	xtrain.Normalize();
	ytrain(all_ans_data);
	ytrain.Normalize();
	shuffle_index();
	//xtrain.display();
	//ytrain.display();
}

void data_loader::shuffle_index()
{
	int data_size = (int)xtrain.getRowandCol().get_element(0, 0);
	vector<int> tmp(data_size);
	vector<int> test;
	vector<int> train;
	iota(tmp.begin(), tmp.end(), 1);
	random_shuffle(tmp.begin(), tmp.end());
	for (int i = 0; i < data_size; i++)
	{
		if (i % 5 == 0)
			test.push_back(tmp[i]);
		else train.push_back(tmp[i]);
	}
	train_index(vector< vector<int> >(1, train));
	test_index(vector< vector<int> >(1, test));
	//train_index.display();
	//test_index.display();
}
