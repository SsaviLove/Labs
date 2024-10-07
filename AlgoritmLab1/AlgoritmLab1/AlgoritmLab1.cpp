#include <iostream>
//#include <climits>
//#include <cstdlib>
//#include <ctime>

using namespace std;

void RandMatr(int** matr, int m)
{
    srand(time(0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            matr[i][j] = rand() % 20 + 1;
            if (i == j) matr[i][j] = 0;
        }
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

void Swap(int* first, int* second)
{
    int ptr = *first;
    *first = *second;
    *second = ptr;
}

void ShiftLeft(int* mas, int m, int pos)
{
    for (int i = pos; i < m - 1; i++)
        mas[i] = mas[i + 1];
}

int DelCol(int** matr, int m, int k)
{
    int i;
    for (i = 0; i < m; i++)
        ShiftLeft(matr[i], m, k);
    return --m;
}

int DelStr(int** matr, int m, int k)
{
    int i;
    delete[] matr[k];
    for (i = k; i < m - 1; i++)
        matr[i] = matr[i + 1];
    return --m;
}

int RouteCost(int route[], int n, int** matr)
{
    int cost = 0;
    for (int i = 0; i < n-1 ; ++i)
    {
        cost += matr[route[i]][route[i + 1]];
    }
    cost += matr[route[n - 1]][route[0]]; // возвращение в начальный город
    return cost;
}

void OutputMas(int* mas, int m)
{
    for (int* p = mas; p < mas + m; p++) printf("%d ", *p);
}

void permute(int* arr, int start, int end, int** matr, int& min_сost, int *best_route)
{
    if (start == end)
    {
        int currentCost = RouteCost(arr, end + 1, matr);
        if (currentCost < min_сost)
        {
            min_сost = currentCost;
            for (int i = 0; i <= end; i++) best_route[i] = arr[i];
        }
    }
    else
    {
        for (int i = start; i <= end; ++i) {
            Swap(&arr[start], &arr[i]);
            permute(arr, start + 1, end, matr, min_сost,best_route);
            Swap(&arr[start], &arr[i]);
        }
    }
}

void ColZero(int** matr, int m, int index)
{
    for (int i = 0; i < m; i++)
        matr[i][index] = 0;
}

int MaxSumStr(int** matr, int m)
{
    int sum = 0,max_sum=0, index=0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            sum += matr[i][j];
        }
        cout << i + 1 << "строка = " << sum << endl;
        if (sum > max_sum)
        {
            max_sum = sum;
            index = i;
            sum = 0;
        }
    }
    cout << "Макс сумма: " << max_sum << endl;
    return index;
}

int MinDuga(int** matr, int m)
{
    int min_st=1000;
    int index = MaxSumStr(matr, m);
    int index_j = 0;
    for (int j = 0; j < m; j++)
    {
        if (matr[index][j] > 0 && matr[index][j] < min_st)
        {
            min_st = matr[index][j];
            index_j = j;
            ColZero(matr, m, j);
        }
        matr[index][j] = 0;
    }
    return min_st;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int** matr;
    int cnt_city;
    cout << "Введи кол-во городов:" << endl;
    cin >> cnt_city;
    int startCity;
    cout << "Введи старт:" << endl;
    cin >> startCity;
    startCity -= 1;
    matr = new int* [cnt_city];
    for (int i = 0; i < cnt_city; i++)
        matr[i] = new int[cnt_city];
    RandMatr(matr, cnt_city);
    cout << "Матрица стоимости:" << endl;
    OutputMatr(matr, cnt_city);

    // Инициализация массива городов
    int *cities = new int[cnt_city];
    int* best_route = new int[cnt_city];
    for (int i = 0; i < cnt_city; ++i)
    {
        cities[i] = i;
    }

    // Решение задачи коммивояжёра

    Swap(&cities[0], &cities[startCity]);
    int min_сost = 1000;
    permute(cities, 1, cnt_city - 1, matr, min_сost,best_route);
    cout << "Минимальный путь: " << min_сost << endl;
    cout << "Маршрут: ";
    cout <<best_route[0]+1<< "->";
    for (int i=1;i<cnt_city;++i)
        cout<<best_route[i]+1<<"->";
    cout << best_route[0]+1;
    //эвристика
    // 
    //int LenPuti = 0, sum = 0, cnt = 1;
    //while (cnt != cnt_city)
    //{
    //    puts("\nСумма дуг:");
    //    int min_st_puti = MinDuga(matr, cnt_city);
    //    LenPuti += min_st_puti;
    //    cout << "Макс сумма: " << min_st_puti << endl;
    //    //cnt_city = DelCol(matr, cnt_city, indj);
    //    OutputMatr(matr, cnt_city);
    //    cout << endl;
    //    cnt++;
    //}
    //cout << "Длина пути эвристикой: " << LenPuti;
    for (int i = 0; i < cnt_city; i++) delete[]matr[i];
    delete[] matr;
    delete[] cities;
    delete[] best_route;
    return 0;
}