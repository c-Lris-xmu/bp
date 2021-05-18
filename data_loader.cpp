#include "headers/data_loader.h"
#include<fstream>
#include<string>
#include<ctype.h>

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

void data_loader::read_file(string str,Matrix<double> &X,Matrix<double> &Y)
{
	
	ifstream openfile(str);
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
	X(all_train_data);
	Y(all_ans_data);
	X.display();
	Y.display();
}