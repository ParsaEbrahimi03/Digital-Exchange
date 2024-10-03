#include "user.h"
#include "transaction.h" 
#include "database.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <Windows.h>
#include <ctime>
#include <chrono>
#define dollar 50000


vector <user>users;
vector<transaction>T_user;

using namespace std;

string date_t()
{
	
	time_t ttime = time(0);

	auto start = chrono::system_clock::now();
	auto legacyStart = chrono::system_clock::to_time_t(start);
	char tmBuff[30];

	ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
	
	return tmBuff;
}

void user::change(user temp)
{
	string npass;
	do
	{
		cout << "Enter password : ";
		getline(cin, npass);

		if (npass.length() < 8)
			cout << "TRY AGAIN!!!";

	} while (npass.length() < 8);
	temp.password = npass;
	cout << "changed successfuly" << endl;
	_getch();
}

void user::calculate(user temp )
{

	transaction temp_t;
	T_user = temp_t.load();
	for (int i = 0; i < T_user.size(); i++)
	{
		if (temp.username == T_user[i].user_T)
		{
			temp_t = T_user[i];
		}
	}

	
	system("cls");
	cout << "ID : " << temp.id << "     Username : " << temp.username << "     Balance RIAL : ";
	printf("%.2lf\n", temp.balance_R);
	cout << "1.Money Exchange (R to D)" << endl;
	cout << "2.Money Exchange (D to R)" << endl;
	cout << "3.Money rising" << endl;
	cout << "4.view Transacation" << endl;
	cout << "5.view Balance" << endl;
	cout << "6.change password" << endl;
	cout << "7.Log out" << endl;

	char cBuf;
	database db;
	
	
	cBuf = _getch();
	switch (cBuf)
	{
	case '1':
		system("cls");
		ExchangeR_D(temp );
		break;
	case '2':
		system("cls");
		ExchangeD_R(temp );
		break;
	case '3':
		rising(temp);
		break;
	case '4':
		system("cls");
		temp_t.print();
		cout << "Press enter to continue ";
		_getch();
		calculate(temp);
		break;
	case '5':
		system("cls");
		cout << "Balance R : " << temp.balance_R << endl;
		cout << "Balance D : " << temp.balance_D << endl;
		cout << "Press enter to continue ";
		_getch();
		calculate(temp);
		break;
	case '6':
		system("cls");
		cin.ignore(254, '\n');
		change(temp);
		system("cls");
		calculate(temp);
		break;
	case '7':
		system("cls");
		cin.ignore(254, '\n');
		push_save(temp);
		db.save(users);
		temp_t.save_T(T_user);
		menu();
		//menu(user );
	default:
		system("cls");
		cout << "try again " << endl;
		cBuf = _getch();
		break;
	}
}

void user::push_save(user temp)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (temp.username == users[i].username) 
		{
			users[i] = temp;
		}
	}
}



void user::menu()
{
	database db;
	transaction tr;
	users = db.load();
	T_user = tr.load();
	user u_temp1;

	cout << "1.LOG IN" << endl;
	cout << "2.SIGN UP" << endl;
	cout << "3.ABOOUT" << endl;
	cout << "9.EXIT" << endl;

	char buf;
	buf = _getch();
	while (buf != '0') {
		switch (buf)
		{
		case '1':
			system("cls");
			Login();
			break;
		case '2':
			system("cls");
			menu_sign();
			buf = '0';
			break;
		case '3':
			break;
		case '9':
			exit(0);
			break;

		default:
			cout << "TRY AGAIN!! " << endl;
			buf = _getch();
		}
	}
}

void user::menu_sign()
{
	user temp;

	cout << "Enter name : ";
	getline(cin, temp.name);
	
	cout << "Enter E_mail : ";
	getline(cin, temp.e_mail);
	
	cout << "Enter username : ";
	getline(cin, temp.username);
	
		do
		{
			cout << "Enter password : ";
			getline(cin, temp.password);
	
			if (temp.password.length() < 8)
				cout << "TRY AGAIN!!!";
	
		} while (temp.password.length() < 8);
	
	
		srand(time(0));
		temp.id = 13456789 + (rand() % 5000);
	
		temp.balance_R = 0;

		cout << "Enter Money RIAL : ";
		cin >> temp.balance_R;
	
		temp.balance_D = 0;
	
		
		cout << "Registration was seccessfully completed ! ";
		system("cls");

		users.push_back(temp);
		database db;
		transaction temp_t;
		transaction1 temp_t1;
		temp_t1.amount = 0;
		temp_t1.balance_d = 0;
		temp_t1.balance_r = temp.balance_R;
		temp_t1.check = 0;
		temp_t1.date = date_t();
		temp_t.user_T = temp.username;
		temp_t.T_temp.push_back(temp_t1);
		
		T_user.push_back(temp_t);
		temp_t.save_T(T_user);
		db.save(users);
		calculate(temp );
}

void user::ExchangeR_D(user temp )
{
	transaction temp_t;
	transaction1 temp_t1;

	int tUser = -1;
	for (int i = 0; i < T_user.size(); i++)
	{
		if (temp.username == T_user[i].user_T)
		{
			temp_t = T_user[i];
			tUser = i;
		}
	}
	
	char C_buf;

	do
	{
		long float R_buf;

		printf("Balance R : %.2f     //Blance D : %.2f\n", temp.balance_R,temp.balance_D);

		cout << "Enter the desired amount : ";
		cin >> R_buf;
		if (R_buf > temp.balance_R)
		{
			cout << "Try Again !!" << endl;
			Sleep(100);
			ExchangeR_D(temp);
		}
		else 
		{
			
			temp.balance_R = temp.balance_R - R_buf;
			temp.balance_D = temp.balance_D + (R_buf / dollar);

			temp_t1.check = 2;
			temp_t1.amount = R_buf;
			temp_t1.balance_d = temp.balance_D;
			temp_t1.date = date_t();
			temp_t1.balance_r = temp.balance_R;
			temp_t.T_temp.push_back(temp_t1);


			cout << "Do you want to continue ? Y/N : ";
			C_buf = _getch();

			system("cls");
		}
		

	} while (C_buf =='y' || C_buf == 'Y');

	try {
		if (tUser != -1)
			T_user[tUser] = temp_t;
		else
			throw invalid_argument("out of the range !!");
	}
	catch(invalid_argument &e)
	{
		temp_t.user_T = temp.username;
		T_user.push_back(temp_t);
	}
	
	//T_user[tUser].user_T = temp.username;
	temp_t.save_T(T_user);
	calculate(temp );
}

void user::ExchangeD_R(user temp )
{
	transaction temp_t;
	transaction1 temp_t1;

	int tUser;
	for (int i = 0; i < T_user.size(); i++)
	{
		if (temp.username == T_user[i].user_T)
		{
			temp_t = T_user[i];
			tUser = i;
		}
	}

	char C_buf;
	
	do
	{
		
		long float D_buf;

		printf("Balance D : %.2f     //Blance R : %.2f\n", temp.balance_D, temp.balance_R);

		cout << "Enter the desired amount : ";
		cin >> D_buf;

		if (D_buf > temp.balance_D)
		{
			cout << "Try again !! " << endl;
			Sleep(500);

			ExchangeD_R(temp );
		}
		else
		{
			temp.balance_D = temp.balance_D - D_buf;
			temp.balance_R = temp.balance_R + (D_buf * dollar);

			temp_t1.check = 1;
			temp_t1.amount = D_buf;
			temp_t1.balance_d = temp.balance_D;
			temp_t1.date = date_t();
			temp_t1.balance_r = temp.balance_R;
			temp_t.T_temp.push_back(temp_t1);

			cout << "Do you want to continue ? Y/N : ";
			C_buf = _getch();

			system("cls");
		}

	} while (C_buf == 'y' || C_buf == 'Y');

	try {
		if (tUser != -1)
			T_user[tUser] = temp_t;
		else
			throw invalid_argument("out of the range !!");
	}
	catch (invalid_argument& e)
	{
		temp_t.user_T = temp.username;
		T_user.push_back(temp_t);
	}
	temp_t.save_T(T_user);
	calculate(temp );
}

void user::rising(user temp )
{
	system("cls");

	long float b_buf;

	cout << "Enter the desired amount : ";
	cin >> b_buf;

	temp.balance_R = temp.balance_R + b_buf;

	system("cls");

	calculate(temp );
}

void user::Login()
{
	user temp;

	char check = '1';

	int i_user;
	do
	{
		cout << "Enter username : ";
		cin >> temp.username;
		for ( int i = 0; i < users.size(); i++)
		{
			if (users[i].username == temp.username)
			{
				check = '0';
				i_user = i;
			}
		}
		if (check == '1')
		{
			cout << "Try again !" << endl;
		}
		
	} while (check == '1');

	do
	{
		cout << "Enter password : ";
		cin >> temp.password;

			if (users[i_user].password != temp.password)
			{
				cout << "Try again !" << endl;
			}
	} while (users[i_user].password != temp.password);

	transaction temp_t;

	for (int i = 0; i < T_user.size(); i++)
	{
		if (users[i_user].username == T_user[i].user_T)
			temp_t = T_user[i];
	}

	temp = users[i_user];

	system("cls");

	calculate(temp );
}

string user::to_text()
{
	stringstream ss;

	ss << name << "_" << e_mail << "_" << username << "_" << password << "_" << id << "_" << balance_R << "_" << balance_D << endl;

	return ss.str();
}

user user::from_text(string data)
{
	stringstream ss(data);

	string name, e_mail, username, password, id, balance_d, balance_r;
	int id1;
	float balance_d1, balance_r1;

	getline(ss, name, '_');
	getline(ss, e_mail, '_');
	getline(ss, username, '_');
	getline(ss, password, '_');
	getline(ss, id, '_');
	getline(ss, balance_r, '_');
	getline(ss, balance_d, '\n');

	id1 = stoi(id);
	balance_r1 = stof(balance_r);
	balance_d1 = stof(balance_d);

	return user{ name,e_mail,username,password,id1,balance_r1,balance_d1 };
}