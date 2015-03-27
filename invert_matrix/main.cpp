#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

const int SIZE = 3;

double FindAlgebraicAdditions(int a, int b, const vector <vector <double>> &matrix)  // Находим алгебраические дополнения элементов матрицы
{	
	double val;
	vector <int> indexX = { 0, 1, 2 };    
	vector <int> indexY = { 0, 1, 2 };
	indexX.erase(indexX.begin() + a);   // убираем (вычеркиваем) из расчета строку
	indexY.erase(indexY.begin() + b);   // и столбец
	val = (matrix[*min_element(indexX.begin(), indexX.end())][*min_element(indexY.begin(), indexY.end())] *  // находим алгебраическое дополнение
		matrix[*max_element(indexX.begin(), indexX.end())][*max_element(indexY.begin(), indexY.end())] -     // как определитель матрицы 2х2
		matrix[*min_element(indexX.begin(), indexX.end())][*max_element(indexY.begin(), indexY.end())] *     // без учета текущего столбца и строки
		matrix[*max_element(indexX.begin(), indexX.end())][*min_element(indexY.begin(), indexY.end())]);
	return val;
}

bool ReadMatrix(const char* fileName, vector <vector <double>> &result)
{
	ifstream inputFile(fileName);
	if (!inputFile)
	{
		return false;
	}

	int i, j;
	for (i = 0; i < SIZE; i++)            //загружаем матрицу из файла
	{
		for (j = 0; j < SIZE; j++)
		{
			inputFile >> result[i][j];
		}
	}

	return true;
}

double FindDeterminant(const vector <vector <double>> &matrix)
{
	double determinant;
	determinant = ((matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) +  //вычисление определелителя
		(matrix[1][0] * matrix[0][2] * matrix[2][1]) - (matrix[2][0] * matrix[1][1] * matrix[0][2]) -             //по формуле треуголников
		(matrix[0][0] * matrix[2][1] * matrix[1][2]) - (matrix[1][0] * matrix[0][1] * matrix[2][2]));
	return determinant;
}

bool InvertMatrix(vector <vector <double>> &result, vector <vector <double>> &matrix)
{
	int i, j;
	double determinant = FindDeterminant(matrix);
	if (determinant == 0)
	{
		return false;
	}
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j<SIZE; j++)
		{
			result[j][i] = pow(-1, i + j) * FindAlgebraicAdditions(i, j, matrix) / determinant;   //находим обратную матрицу по формуле 
		}                                                                                   // A^-1 = 1/|A| * A.т.(транспонированную)
	}
	return true;
}

void PrintResult(vector <vector <double>> &result)
{
	for (int i = 0; i<SIZE; i++) //выводим обратную матрицу
	{
		for (int j = 0; j<SIZE; j++)
		{
			cout << result[i][j] << "\t";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "The number of parameters isn't equal to 2";
		return 1;
	}

	vector <vector <double>> originalMatrix(SIZE, vector<double>(SIZE)), inverseMatrix(SIZE, vector<double>(SIZE));

	if (!ReadMatrix(argv[1], originalMatrix))
	{
		cout << "reading matrix failed!" << endl;
	}

	if (!InvertMatrix(inverseMatrix, originalMatrix))
	{
		cout << "matrix inversion failed!" << endl;
	}
	else
	{
		PrintResult(inverseMatrix);
	}
	system("pause");
}