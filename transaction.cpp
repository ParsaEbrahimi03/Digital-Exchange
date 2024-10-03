#include "transaction.h"
#include "VariadicTable.h"
#include "user.h"
#include <conio.h>

void transaction::print()
{
	cout << "Username : " << user_T << endl << endl;
	VariadicTable<std::string, string, double, double> vt({ "Exchange", "Date", "Rial", "Dollar" },
		10);
	for (int i = 0; i < T_temp.size(); i++)
	{
		string date = T_temp[i].date;
		string date2;
		if (date[date.size() - 1] == '\n')
		{
			for (int i = 0; i < date.size() - 1; i++)
			{
				date2[i] = date[i];
			}
		}
		else
		{
			date2 = T_temp[i].date;
			
		}
		{
		
		string check;
		if (T_temp[i].check == 1)
			check = "D to R";
		else if (T_temp[i].check == 2)
			check = "R to D";
		else
			check = "Open account";
			vt.addRow(check,date , T_temp[i].balance_r, T_temp[i].balance_d);

			
		}
		/*cout << "|   " << T_temp[i].balance_r;
		cout << "       |   " << T_temp[i].balance_d << endl;*/
	}
	vt.print(std::cout);
	_getch();
}


void transaction::input()
{
	transaction temp;
	cout << "Enter user : ";
	cin >> transaction::user_T;
	T_temp[0].date = "1035";
	T_temp[0].balance_d = 0;
	T_temp[0].balance_r = 0;
	T_temp[0].check = 1;
}

string transaction::to_text()
{
	stringstream ss;

	ss << user_T <<"-";
	for (int i = 0; i < T_temp.size(); i++)
	{
		string sa;
		sa = T_temp[i].date;
		if (sa[sa.size()-1] == '\n')
		{
			for (int i = 0; i < sa.size() - 1; i++)
			{
				ss << sa[i];
			}
			ss << "*" << T_temp[i].amount << "*" << T_temp[i].check << "*" << T_temp[i].balance_r << "*" << T_temp[i].balance_d << "+";
		}
		else
			ss << T_temp[i].date << "*" << T_temp[i].amount << "*" << T_temp[i].check << "*" << T_temp[i].balance_r << "*" << T_temp[i].balance_d << "+";
		
		
	}
	ss << endl;
	return ss.str();
}

transaction transaction::from_text(string data)
{
	stringstream ss(data);
	string user_T1;
	vector<transaction1> temp_T;
	transaction1 buf;
	string endl;
	transaction Result;
	T_temp.clear();
	string amount, balance_d, balance_r, date, check;
	
	getline(ss, user_T1, '-');
	user_T = user_T1;
	
	while (ss)
	{
		getline(ss, date, '*');
		getline(ss, amount, '*');
		getline(ss, check, '*');
		getline(ss, balance_r, '*');
		getline(ss, balance_d, '+');
		buf.amount = stof(amount);
		buf.balance_d = stof(balance_d);
		buf.balance_r = stof(balance_r);
		buf.check = stoi(check);
		buf.date = date;
		if (buf.date != "")
			T_temp.push_back(buf);
	}

	/*for (int i = 0; ss;i++)
	{
		
	}*/
	

	Result.T_temp = T_temp;
	return Result;
}

void transaction::save_T(vector<transaction>T_users)
{
	ofstream file(filename);

	for (int i = 0; i < T_users.size(); i++)
	{
		file << T_users[i].to_text();
	}

	file.close();
}

vector<transaction> transaction::load()
{
	vector<transaction>Result;
	transaction obj;

	ifstream file(filename);

	string line;
	while (getline(file, line))
	{
		transaction temp = obj.from_text(line);
		temp.user_T = obj.user_T;
		Result.push_back(temp);
	}

	return Result;
}