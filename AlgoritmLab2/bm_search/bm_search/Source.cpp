#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int findFirstIndex(string& const stroka, string& const podstroka)
{
	int Table[256];
	int stroka_len = stroka.size(), podstroka_len = podstroka.size();
	int index = podstroka_len - 1, index_podstroka, index_stroka;
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
			cout << stroka[index_stroka] << "---" << podstroka[index_podstroka]<<endl;
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
			break;
	}
	if (index_podstroka == -1)
		return index - podstroka_len + 1;
	else
		return -1;
}

int main()
{
	string stroka("std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator");
	string podstroka("tor");
	vector<int> mas_index;
	if (findFirstIndex(stroka, podstroka) != -1)
	{
		cout << "First index = " << findFirstIndex(stroka, podstroka) << endl;
	}
	else
	{
		cout << "Podstroka is not found" << endl;
	}
	return 0;
}