#include <iostream>
#include <iomanip>
#include <locale.h>
#include <sstream>
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");

	if (argc != 4)
	{
		cout << "Количество параметров не равно 4";
		return 1;
	}

	double x1 = 0, x2 = 0, a = 0, b = 0, c = 0;
	string A(argv[1]), B(argv[2]), C(argv[3]);

	stringstream aa(A);
	aa >> a;
	stringstream bb(B);
	bb >> b;
	stringstream cc(C);
	cc >> c;

	if (a == 0)
	{
		cout << "Это уравнение не является квадратным";
		return 0;
	}

	double discriminant = b*b - 4 * a*c;
	if (discriminant < 0)
	{
		cout << "Нет действительных корней уравнения";
		return 0;
	}

	if (discriminant == 0)
	{
		cout << "Это уравнение имеет единственный корень:" << endl;
		x1 = -b / (2 * a);
		cout << fixed << setprecision(4) << "x = " << x1;
		return 0;
	}

	if (discriminant > 0)
	{
		cout << "Корни уравнения:\n";
		discriminant = sqrt(discriminant);
		x1 = (-b + discriminant) / (2 * a);
		x2 = (-b - discriminant) / (2 * a);
		cout << fixed << setprecision(4) << "x1 = " << x1 << "\n" << "x2 = " << x2;
		return 0;
	}
}