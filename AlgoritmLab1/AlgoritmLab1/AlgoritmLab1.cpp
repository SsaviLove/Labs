#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

void RandMatr(int** matr, int m)
{
	srand(time(0));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
		{
			if (i == j) matr[i][j] = 0;
			else
				matr[i][j] = rand() %50 + 1;
		}
}

void OutputMatr(int** matr, int m)
{
	for (int i = 0; i < m; i++)
	{
		printf("\n");
		for (int j = 0; j < m; j++) printf("%d ", matr[i][j]);
		printf("\n");
	}
}

void CopyMatr(int** matr, int** matrCopy, int m)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			matrCopy[i][j] = matr[i][j];
}

void Swap(int* first, int* second) {
	int ptr = *first;
	*first = *second;
	*second = ptr;
}

int CheckInvert(int* massiv, int n)
{
	for (int i = 1; i < n - 1; i++)
		if (massiv[i] < massiv[i + 1])
			return 0;
	return 1;
}


void Sort(int* mas, int left, int right)
{
	while (left <= right)
	{
		for (int i = left; i < right; i++)
			if (mas[i] > mas[i + 1])
				Swap(&mas[i], &mas[i + 1]);
		right--;
		for (int i = right; i > left; i--)
			if (mas[i] < mas[i - 1])
				Swap(&mas[i], &mas[i - 1]);
		left++;
	}
}
void CityWay(int *mas,int m, int begin)
{
	int n = 1;
	mas[0] = begin;
	mas[m] = begin;
	for (int i = 1; n <= m; n++)
	{
		if (begin != n)
		{
			mas[i] = n;
			i++;
		}
	}
}
int RouteCost(int** matr, int* mas, int m)
{
	int sum = 0;
	for (int i = 1; i < m + 1; i++)
	{
		sum = sum + matr[mas[i - 1] - 1][mas[i] - 1];
	}
	return sum;
}
bool Permutation(int** matr, int* mas, int m)
{
	int i_max = 1, j_max = 1;
	for (int i = 2; i < m - 1; i++)
		if (mas[i] > 0 && mas[i] < mas[i + 1])
			i_max = i;
	for (int j = i_max + 1; (j > i_max && j <= m - 1); j++)
	{
		if (mas[i_max] < mas[j])
			j_max = j;
	}
	Swap(&mas[j_max], &mas[i_max]);
	Sort(mas, i_max + 1, m - 1);
	if (CheckInvert(mas, m) == 1)
		return false;
	return true;
}
void Zero(int** matr, int m, int line, int column)
{
	for (int i = 0; i < m; i++)
	{
		matr[line][i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		matr[i][column] = 0;
	}
}
void Max_and_MinCost(int** matr, int sumCities, int* mas, int* masMax, int* masMin, int& priceMin, int& priceMax)
{
	priceMin = RouteCost(matr, mas, sumCities);
	priceMax = RouteCost(matr, mas, sumCities);
	for (int i = 0; i < sumCities + 1; i++)
		masMax[i] = mas[i];
	for (int i = 0; i < sumCities + 1; i++)
		masMin[i] = mas[i];
	do
	{
		int price;
		price = RouteCost(matr, mas, sumCities);
		if (price > priceMax)
		{
			priceMax = price;
			for (int i = 0; i < sumCities + 1; i++)
				masMax[i] = mas[i];
		}
		if (price < priceMin)
		{
			priceMin = price;
			for (int i = 0; i < sumCities + 1; i++)
				masMin[i] = mas[i];
		}
	} while (Permutation(matr, mas, sumCities));
}
void Heuristic(int** matr, int sumCities, int StartCity, int* masHeuristic, int& sumHeuristic)
{
	int sumRouteHeuristic = 1;
	int** matrCopy;
	masHeuristic[0] = StartCity;
	masHeuristic[sumCities] = StartCity;
	matrCopy = new int* [sumCities];
	for (int i = 0; i < sumCities; i++)
		matrCopy[i] = new int[sumCities];
	CopyMatr(matr, matrCopy, sumCities);
	while (sumRouteHeuristic < sumCities)
	{
		int minCol = 0;
		for (int j = 1; j <= sumCities; j++)
		{
			if (matr[StartCity - 1][minCol] == 0)
				minCol++;
			if (matr[StartCity - 1][j] < matr[StartCity - 1][minCol] && matr[StartCity - 1][j] > 0)
				minCol = j;
		}
		masHeuristic[sumRouteHeuristic] = minCol + 1;
		for (int test = 0; test < sumRouteHeuristic; test++)
			if (masHeuristic[test] == minCol + 1)
			{
				matr[StartCity - 1][minCol] = 0;
				minCol = StartCity - 1;
				sumRouteHeuristic--;
			}
		if (minCol + 1 != StartCity)
			Zero(matr, sumCities, StartCity - 1, minCol);
		matr[minCol][StartCity - 1] = 0;
		StartCity = minCol + 1;
		sumRouteHeuristic++;
	}
	sumHeuristic = RouteCost(matrCopy, masHeuristic, sumCities);
}
void Percent(int priceMin, int priceMax, int price)
{
	double percent;
	if (priceMax == priceMin)
		cout <<endl << "Процент выполнения = 100%";
	else
	{
		percent = (1. - (1.0 * (price - priceMin) / (priceMax - priceMin))) * 100;
		cout << endl << "Процент выполнения = " << percent << "%";
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int StartCity, cnt_city;
	cout << "Введите кол-во городов:"<<endl;
	cin >> cnt_city;
	cout << "Введите начальный город:"<<endl;
	cin >> StartCity;
	int** matr; int** matкCopy;
	int* mas; int* masHeuristic; int* masMax; int* masMin;
	int price = 0, priceMax = 0, sumHeuristic = 0, priceMin = 0;
	clock_t start, stop;
	double time1, time2;
	matr = new int* [cnt_city];
	for (int i = 0; i < cnt_city; i++)
		matr[i] = new int[cnt_city];
	mas = new int[cnt_city + 1];
	masMax = new int[cnt_city + 1];
	masMin = new int[cnt_city + 1];
	RandMatr(matr, cnt_city);
	OutputMatr(matr, cnt_city);
	CityWay(mas,cnt_city, StartCity);
	start = clock();
	Max_and_MinCost(matr, cnt_city, mas, masMax, masMin, priceMin, priceMax);
	cout <<endl<< "Стоимость min пути = " << priceMin << endl << "Минимальный путь: ";
	for (int i = 0; i <= cnt_city; i++)
		cout << masMin[i] << " ";
	cout << endl << "Стоимость max пути = " << priceMax << endl << "Максимальный путь: ";
	for (int i = 0; i <= cnt_city; i++)
		cout << masMax[i] << " ";
	stop = clock();
	puts("");
	masHeuristic = new int[cnt_city + 1];
	time1 = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << endl<<"Время выполнения точного алгоритма = " << time1<<endl;
	start = clock();
	Heuristic(matr, cnt_city, StartCity, masHeuristic, sumHeuristic);
	cout << "Путь в эвристике: ";
	for (int i = 0; i <= cnt_city; i++)
		cout << masHeuristic[i] << " ";
	stop = clock();
	time2 = (double)(stop - start) / CLOCKS_PER_SEC;
	puts("");
	cout << endl<<"Стоимость пути в эвристике = " << sumHeuristic<<endl;
	cout << "Время выполнения эвристики = " << time2<<endl;
	Percent(priceMin, priceMax, sumHeuristic);

	delete[] mas;
	delete[] masMax;
	delete[] masMin;
	for (int i = 0; i < cnt_city; i++)
		delete[] matr[i];
	delete[] matr;
	delete[] masHeuristic;
	return 0;
}