#pragma once
#include "user.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct transaction1 
{
	int check = 0;
	string date = "0";
	float amount = 0;
	float balance_d = 0;
	float balance_r = 0;
};

class transaction 
{
	string filename = "save_T.txt";

public:
	vector <transaction1>T_temp;
	string user_T;

	void print();
	void input();
	string to_text();
	transaction from_text(string data);
	void save_T(vector<transaction>);
	vector<transaction> load();
};

