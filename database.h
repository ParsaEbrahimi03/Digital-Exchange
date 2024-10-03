#pragma once
#include "user.h"
class database :user
{
	string filename = "save.txt";
public:
	void save(vector<user>);
	vector<user> load();
};

