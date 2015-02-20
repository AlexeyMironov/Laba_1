#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
const int SIZE = 3;

int findAlgebraicAdditions(int a, int b, const vector <vector <float>> &Matr)  // Находим алгебраические дополнения элементов матрицы
{	
	int i, j, val;
	vector <int> IndexX = { 0, 1, 2 };    
	vector <int> IndexY = { 0, 1, 2 };
	IndexX.erase(IndexX.begin() + a);   // убираем (вычеркиваем) из расчета строку
	IndexY.erase(IndexY.begin() + b);   // и столбец
	val = (Matr[*min_element(IndexX.begin(), IndexX.end())][*min_element(IndexY.begin(), IndexY.end())] *  // находим алгебраическое дополнение
		Matr[*max_element(IndexX.begin(), IndexX.end())][*max_element(IndexY.begin(), IndexY.end())] -     // как определитель матрицы 2х2
		Matr[*min_element(IndexX.begin(), IndexX.end())][*max_element(IndexY.begin(), IndexY.end())] *     // без учета текущего столбца и строки
		Matr[*max_element(IndexX.begin(), IndexX.end())][*min_element(IndexY.begin(), IndexY.end())]);     
	return val;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "The number of parameters isn't equal to 2";
		return 1;
	}

	ifstream inputFile(argv[1]);
	if (!inputFile)
	{
		return 2;
	}

	vector <vector <float>> Matr(SIZE, vector<float>(SIZE)), inverseMatrix(SIZE, vector<float>(SIZE));
	int i, j;
	for (i = 0; i < SIZE; i++)            //загружаем матрицу из файла
	{
		for (j = 0; j < SIZE; j++)
		{
			inputFile >> Matr[i][j];
		}
	}
	
	float determinant;
	determinant = ((Matr[0][0] * Matr[1][1] * Matr[2][2]) + (Matr[0][1] * Matr[1][2] * Matr[2][0]) +  //вычисление определелителя
		(Matr[1][0] * Matr[0][2] * Matr[2][1]) - (Matr[2][0] * Matr[1][1] * Matr[0][2]) -             //по формуле треуголников
		(Matr[0][0] * Matr[2][1] * Matr[1][2]) - (Matr[1][0] * Matr[0][1] * Matr[2][2]));

	for (i = 0; i < SIZE; i++)    
	{
		for (j = 0; j<SIZE; j++)
		{
			inverseMatrix[j][i] = pow(-1, i+j) * findAlgebraicAdditions(i, j, Matr) / determinant;   //находим обратную матрицу по формуле 
		}                                                                                   // A^-1 = 1/|A| * A.т.(транспонированную)
	}
	
	for (int i = 0; i<SIZE; i++) //выводим обратную матрицу
	{
		for (int j = 0; j<SIZE; j++)
		{
			cout << inverseMatrix[i][j] << "\t";
		}
		cout << endl;
	}
}