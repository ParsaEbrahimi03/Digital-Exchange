#pragma once
#include <iostream>
#include "transaction.h"
#include <vector>

using namespace std;

class user 
{
private:
	
public:
	string name;
	string e_mail;
	string username;
	string password;
	int id;
	float balance_R;
	float balance_D;


	void calculate(user );
	void menu();
	void menu_sign();
	void ExchangeR_D(user );
	void ExchangeD_R(user );
	void rising(user );
	void Login();
	void push_save(user);
	void change(user);
	string to_text();
	user from_text(string data);
};

