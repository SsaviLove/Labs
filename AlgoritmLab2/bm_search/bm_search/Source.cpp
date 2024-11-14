#include <iostream>
#include <vector>
#include <string>

using namespace std;

using namespace std;

int find_first_Index(const string& stroka, const string& podstroka, int start = 0)
{
	int Table[256];
	int stroka_len = stroka.size(), podstroka_len = podstroka.size();
	int index = start + podstroka_len - 1, index_podstroka, index_stroka;

	for (int i = 0; i < 256; i++)
		Table[i] = podstroka_len;
	for (int i = 0; i < podstroka_len - 1; i++)
		Table[podstroka[i]] = podstroka_len - 1 - i;

	while (index < stroka_len)
	{
		index_stroka = index;
		index_podstroka = podstroka_len - 1;
		while (index_podstroka >= 0)
		{
			if (stroka[index_stroka] == podstroka[index_podstroka])
			{
				index_stroka--;
				index_podstroka--;
			}
			else
			{
				index += Table[stroka[index]];
				break;
			}
		}
		if (index_podstroka == -1)
			return index - podstroka_len + 1;
	}

	return -1;
}

vector<int> find_all_Index(const string& stroka, const string& podstroka, int leftBorder, int rightBorder)
{
	vector<int> masEntr;
	int start = leftBorder;
	int entr;

	while ((entr = find_first_Index(stroka, podstroka, start)) != -1)
	{
		if (entr >= leftBorder && entr < rightBorder)
			masEntr.push_back(entr);
		start = entr + 1; // сдвиг на следующую позицию после найденной
	}

	return masEntr;
}

int main()
{
	string stroka("std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator");
	cout << stroka << endl;
	string podstroka("tor");
	vector<int> mas_index;
	if (find_first_Index(stroka, podstroka) != -1)
	{
		cout << "First index = " << find_first_Index(stroka, podstroka) << endl;
	}
	else
	{
		cout << "Podstroka is not found" << endl;
	}
	mas_index = find_all_Index(stroka, podstroka, 28, 36);
	cout << "find_all_Index(28б 36) = [";
	for (int i = 0; i < mas_index.size(); i++)
	{
		cout << mas_index[i];
	}
	cout << "]" << endl;

	return 0;
}