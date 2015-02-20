
#include <string> // Миронов Алексей ПС-21 Задание 1
#include <iostream>
#include <fstream>
#include <locale.h>
#include <string>

using namespace std;


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	if (argc != 5)
	{
		cout << "Количество параметров не равно 4";
		return 1;
	}
	ifstream infile(argv[1]);
	ofstream outfile(argv[2]);
	string searchLine(argv[3]);
	string replaceLine(argv[4]);

	if (searchLine.empty())
	{
		cout << "Искомая строка не должна быть пустой";
		return 2;
	}

	if (!infile)
	{
		return 3;
	}

	string inputLine;
	while (!infile.eof())
	{
		getline(infile, inputLine);
		int it = inputLine.find(searchLine);
		while (it != string::npos)
		{	
			inputLine.replace(it, searchLine.length(), replaceLine);
			it = inputLine.find(searchLine, it);
		}
		outfile << inputLine << endl;
	}
	infile.close();
	outfile.close();
	return 0;
}