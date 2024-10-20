#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void randMatrD(int** matr, int m, int lf, int rt)
{
	srand(time(0));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
		{
			if (i == j)
				matr[i][j] = 0;
			else
				matr[i][j] = rand() % (rt - lf + 1) + lf;
		}
}
void outputMatrD(int** matr, int m)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++) printf(" % 4d", matr[i][j]);
		printf("\n");
	}
}
void swap(int& a, int& b)
{
	int c;
	c = a;
	a = b;
	b = c;
}
int inverСheck(int* massiv, int n)
{
	for (int i = 1; i < n - 1; i++)
		if (massiv[i] < massiv[i + 1])
			return 0;
	return 1;
}
void copyMatrix(int** matrix, int** matrixCopy, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrixCopy[i][j] = matrix[i][j];
}
void sheiker(int* massiv, int L, int R)
{
	while (L <= R)
	{
		for (int i = L; i < R; i++)
			if (massiv[i] > massiv[i + 1])
				swap(massiv[i], massiv[i + 1]);
		R--;
		for (int i = R; i > L; i--)
			if (massiv[i] < massiv[i - 1])
				swap(massiv[i], massiv[i - 1]);
		L++;
	}
}
void createMassivWay(int n, int begin, int* massiv)
{
	int m = 1;
	massiv[0] = begin;
	massiv[n] = begin;
	for (int i = 1; m <= n; m++)
	{
		if (begin != m)
		{
			massiv[i] = m;
			i++;
		}
	}
}
int priceWay(int** matr, int* massiv, int n)
{
	int sum = 0;
	for (int i = 1; i < n + 1; i++)
	{
		sum = sum + matr[massiv[i - 1] - 1][massiv[i] - 1];
	}
	return sum;
}
bool dijkAlg(int** matr, int* massiv, int n)
{
	int i_max = 1, j_max = 1;
	for (int i = 2; i < n - 1; i++)
		if (massiv[i] > 0 && massiv[i] < massiv[i + 1])
			i_max = i;
	for (int j = i_max + 1; (j > i_max && j <= n - 1); j++)
	{
		if (massiv[i_max] < massiv[j])
			j_max = j;
	}
	swap(massiv[j_max], massiv[i_max]);
	sheiker(massiv, i_max + 1, n - 1);
	if (inverСheck(massiv, n) == 1)
		return false;
	return true;
}
void delStrStl(int** matrix, int n, int line, int column)
{
	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		matrix[i][column] = 0;
	}
}
void exactAlg(int** matrix, int sumCities, int* massiv, int* masMax, int* masMin, int& priceMin, int& priceMax)
{
	priceMin = priceWay(matrix, massiv, sumCities);
	priceMax = priceWay(matrix, massiv, sumCities);
	for (int i = 0; i < sumCities + 1; i++)
		masMax[i] = massiv[i];
	for (int i = 0; i < sumCities + 1; i++)
		masMin[i] = massiv[i];
	do
	{
		int price;
		price = priceWay(matrix, massiv, sumCities);
		if (price > priceMax)
		{
			priceMax = price;
			for (int i = 0; i < sumCities + 1; i++)
				masMax[i] = massiv[i];
		}
		if (price < priceMin)
		{
			priceMin = price;
			for (int i = 0; i < sumCities + 1; i++)
				masMin[i] = massiv[i];
		}
	} while (dijkAlg(matrix, massiv, sumCities));
}
void heuristic(int** matrix, int sumCities, int Begin, int* masHeuristic, int& sumHeuristic)
{
	int sumWayHeuristic = 1;
	int** matrixCopy;
	masHeuristic[0] = Begin;
	masHeuristic[sumCities] = Begin;
	matrixCopy = new int* [sumCities];
	for (int i = 0; i < sumCities; i++)
		matrixCopy[i] = new int[sumCities];
	copyMatrix(matrix, matrixCopy, sumCities);
	while (sumWayHeuristic < sumCities)
	{
		int minCol = 0;
		for (int j = 1; j <= sumCities; j++)
		{
			if (matrix[Begin - 1][minCol] == 0)
				minCol++;
			if (matrix[Begin - 1][j] < matrix[Begin - 1][minCol] && matrix[Begin - 1][j] > 0)
				minCol = j;
		}
		masHeuristic[sumWayHeuristic] = minCol + 1;
		for (int test = 0; test < sumWayHeuristic; test++)
			if (masHeuristic[test] == minCol + 1)
			{
				matrix[Begin - 1][minCol] = 0;
				minCol = Begin - 1;
				sumWayHeuristic--;
			}
		if (minCol + 1 != Begin)
			delStrStl(matrix, sumCities, Begin - 1, minCol);
		matrix[minCol][Begin - 1] = 0;
		Begin = minCol + 1;
		sumWayHeuristic++;
	}
	sumHeuristic = priceWay(matrixCopy, masHeuristic, sumCities);
}
void percent(int priceMin, int priceMax, int price)
{
	double percent;
	if (priceMax == priceMin)
		std::cout << "\n" << "accuracy of execution = 100%";
	else
	{
		percent = (1. - (1.0 * (price - priceMin) / (priceMax - priceMin))) * 100;
		std::cout << "\n" << "\n" << "accuracy of execution = " << percent << "%";
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	//for (int j = 0; j < 1; j++)
	//{
		int Begin, sumCities;
		std::cout << "Enter the number of cities - ";
		std::cin >> sumCities;
		puts("");
		std::cout << "Enter your starting city ";
		std::cin >> Begin;
		puts("");
		int** matrix; int** matrixCopy;
		int* massiv; int* masHeuristic; int* masMax; int* masMin;
		int price = 0, priceMax = 0, sumHeuristic = 0, priceMin = 0;
		clock_t start, stop; double time1, time2;
		matrix = new int* [sumCities];
		for (int i = 0; i < sumCities; i++)
			matrix[i] = new int[sumCities];
		massiv = new int[sumCities + 1];
		masMax = new int[sumCities + 1];
		masMin = new int[sumCities + 1];
		randMatrD(matrix, sumCities, 1, 100);
		outputMatrD(matrix, sumCities);
		createMassivWay(sumCities, Begin, massiv);
		start = clock();
		exactAlg(matrix, sumCities, massiv, masMax, masMin, priceMin, priceMax);
		std::cout << "\n" << "The min Way = " << priceMin << "\n" << "Minimum way: ";
		for (int i = 0; i <= sumCities; i++)
			std::cout << masMin[i] << " ";
		std::cout << "\n" << "The max Way = " << priceMax << "\n" << "Maximum way: ";
		for (int i = 0; i <= sumCities; i++)
			std::cout << masMax[i] << " ";
		puts("");
		delete[] massiv;
		delete[] masMax;
		delete[] masMin;
		masHeuristic = new int[sumCities + 1];
		stop = clock();
		time1 = (double)(stop - start) / CLOCKS_PER_SEC;
		std::cout << "the running time of the exact algorithm = " << time1;
		puts("");
		start = clock();
		heuristic(matrix, sumCities, Begin, masHeuristic, sumHeuristic);
		std::cout << "\n" << "Heuristic way massiv: ";
		for (int i = 0; i <= sumCities; i++)
			std::cout << masHeuristic[i] << " ";
		stop = clock();
		time2 = (double)(stop - start) / CLOCKS_PER_SEC;
		std::cout << "\nThe Way in heuristic = " << sumHeuristic;
		std::cout << "\n" << "the running time of the heuristic algorithm = " << time2;
		percent(priceMin, priceMax, sumHeuristic);
		for (int i = 0; i < sumCities; i++)
			delete[] matrix[i];
		delete[] matrix;
		delete[] masHeuristic;
		puts("\n--------------------------------------------------");
	//}
	return 0;
}