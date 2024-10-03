#include "database.h"
#include <fstream>

void database::save(vector<user>users)
{
	ofstream file(filename);

	for (int i = 0; i < users.size(); i++)
	{
		file << users[i].to_text();
	}

	file.close();
}

vector<user> database::load()
{
	vector<user>result;
	user obj;

	ifstream file(filename);

	string line;
	while (getline(file, line))
	{
		user temp = obj.from_text(line);

		result.push_back(temp);
	}

	return result;
}
