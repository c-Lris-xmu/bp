#include "headers/data_loader.h"
#include<fstream>
#include<string>
#include<ctype.h>

using namespace std;

double data_loader::label_to_num(const string s)
{
	if (s == "Iris-setosa")
		return 1.0;
	else if (s == "Iris-versicolor")
		return 2.0;
	return 3.0;
}

void data_loader::read_file(string str,Matrix<double> &X,Matrix<double> &Y)
{
	
	ifstream openfile(str);
	vector<vector<double> > all_train_data;
	vector<double> all_ans_data;
	while (!openfile.eof())
	{
		vector<string> string_tmp(5,"");
		vector<double> train_tmp;
		int cnt = 0,flag=1;
		getline(openfile, string_tmp[cnt++], ',');
		for (auto& p : string_tmp)
		{
			for (auto& c : p)
			{
				if (!isdigit(c) && c != '.')
				{
					flag = 0;
					break;
				}
			}
			if (flag)
				train_tmp.push_back(stod(p));
			else all_ans_data.push_back(label_to_num(p));
		}
		all_train_data.push_back(train_tmp);
	}
	X(all_train_data);
	Y(vector<vector<double> >(1, all_ans_data));
	X.display();
	Y.display();
}