#include <iostream>
#include <vector>

// т.к в задаче не сказано про добавление/удаление/какую-либо
// работу с объектами, то будем считать что в рамках данной задачи
// количество объектов из матрицы извлекается один раз и не меняется
// во время работы программы

using namespace std;
struct Item {
	int subj_i; // можно использовать как имя объекта
	int obj_j;
	string value;
	/*int _subj_name;*/
};

string RW_gen() // рандоматор прав доступа на чтение, запись и отсутствие прав(у меня нет прав)
{
	string M[2] = { "R","W" };
	int w = 2;
	int i, j, n;
	string buff;
	n = pow(2, w);
	vector <string> RWOX;
	for (int i = 0; i < n; i++)
	{
		for (j = 0; j < w; j++)
			if (i & (1 << j))
				buff += M[j];
		RWOX.push_back(buff);
		buff = "";
	}
	int rander = rand() % 3 + 1;
	int rander_empty_or_not = rand() % 2;
	string for_return;
	if (rander_empty_or_not == 1)
		for_return = RWOX[rander];
	else
		for_return = "_";
	return for_return;
}

void output(vector <Item> Items)
{
	cout << "____________________________________" << endl;
	cout << "Вывод сгенерированной разряженной матрицы" << endl;
	cout << "В формате: имя субъекта, имя объекта, права доступа" << endl;
	cout << "" << endl;
	for (int i = 0; i < Items.size(); i++)
	{
		cout << Items[i].subj_i << "| " << Items[i].obj_j << " " << Items[i].value << endl;
		cout << "______" << endl;
	}
	cout << "____________________________________" << endl;
}
void clear(vector <Item>& Items)
{
	for (int d = 0; d < Items.size(); d++)
	{
		if (Items[d].value == "")
		{
			Items.erase(Items.begin() + d);
		}
	}
}
void change_rule(vector <Item>& Items, int act, int i, int j, string rule)
{
	// удаление права - 1, добавление права - 2 отвечает переменная act
	bool standart = false;
	for (int d = 0; d < Items.size(); d++)
	{
		if (Items[d].subj_i == i && Items[d].obj_j)
		{
			standart = true;
		}
		if (Items[d].subj_i == i && Items[d].obj_j == j && act == 1)
		{
			string res = rule;
			for (int inputInd = 0; inputInd < res.size(); inputInd++)
			{
				for (int nowInd = 0; nowInd < Items[d].value.size(); nowInd++)
				{
					if (res[inputInd] == Items[d].value[nowInd])
					{
						Items[d].value = Items[d].value.substr(0, nowInd) + Items[d].value.substr(nowInd + 1, Items[d].value.size() - nowInd - 1);
						break;
					}
				}
			}
		}
		if (Items[d].subj_i == i && Items[d].obj_j == j && act == 2)
		{
			string res = rule;
			for (int inputInd = 0; inputInd < res.size(); inputInd++)
			{
				bool f = true;
				for (int nowInd = 0; nowInd < Items[d].value.size(); nowInd++)
				{
					if (res[inputInd] == Items[d].value[nowInd])
					{
						f = false;
						break;
					}
				}
				if (f)
				{
					/*if (Items[d].value == "R" && )*/
					Items[d].value += res[inputInd];
				}
			}
		}
	}
	if (standart == true && act == 2)
	{
		Item temp;
		temp.subj_i = i;
		temp.obj_j = j;
		temp.value = rule;
		Items.push_back(temp);
	}
	clear(Items);
	output(Items);
}

void insert_new_subj(vector <Item>& Items, int new_subj_i, int obj_count)
{
	Item temp;
	temp.subj_i = new_subj_i;
	temp.value = "R";
	for (int i = 0; i < obj_count; i++)
	{
		temp.obj_j = i;
		Items.push_back(temp);
	}
	clear(Items);
	output(Items);
}

void delete_subj(vector <Item>& Items, int del_subj_i, int obj_count)
{
	bool finded = false;
	for (int i = 0; i < Items.size(); i++)
	{
		if (Items[i].subj_i == del_subj_i)
		{
			finded = true;
			Items.erase(Items.begin() + i);
		}
	}
	if (!finded)
		cout << "Ни одного субъекта с таким именем не найдено, удаления не произошло" << endl;
	if (finded)
	{
		clear(Items);
		output(Items);
	}

}

void usage_prc(vector <Item>& Items, int obj_count)
{
	int max_index_i = -1;
	for (int i = 0; i < Items.size(); i++)
		if (Items[i].subj_i > max_index_i)
			max_index_i = Items[i].subj_i;
	max_index_i++;
	cout << "размер матрицы NxM :" << max_index_i << "x" << obj_count << endl;
	cout << "всего клеток в матрице :" << max_index_i * obj_count << endl;
	cout << "заполненных клеток в матрице :" << Items.size() << endl;
	float all = max_index_i * obj_count;
	float items_size = Items.size();
	cout << "заполненность матрицы :" << float((items_size / all) * 100) << "%" << endl;
}
void list_for_t(vector <Item>& Items, int obj_index, int obj_count)
{
	vector <int> answer = vector <int>();
	for (int i = 0; i < Items.size(); i++)
	{
		if (!(find(answer.begin(), answer.end(), Items[i].subj_i) != answer.end()) && Items[i].obj_j == obj_index)
			answer.push_back(Items[i].subj_i);
	}
	cout << "вывод списка субъектов с доступом к объекту T" << endl;
	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i] << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	int n = rand() % 10 + 2; 
	int m = rand() % 10 + 2; 

	cout << "Количество субъектов(программ обработчиков) " << n << endl;
	cout << "Количество объектов(содержат информацию) " << m << endl;
	cout << "Строки - субъекты, столбцы - объекты" << endl;
	vector <Item> Items = vector <Item>();

	cout << "генерация rw" << endl;
	for (int i = 0; i < n; i++) // строки-субъекты
	{
		for (int j = 0; j < m; j++) // столбцы-объекты
		{
			string temp_RW = RW_gen();
			if (temp_RW != "_")
			{
				Item temp_item;
				temp_item.subj_i = i;
				temp_item.obj_j = j;
				temp_item.value = temp_RW;
				Items.push_back(temp_item);
			}
		}
	}
	output(Items);

	cout << "Вывод списка команд, выбираемых в консоли" << endl;
	cout << "Окончание работы цикла - цифра 0" << endl;
	cout << "1 - редактирование содержимого любой ячейки" << endl;
	cout << "2 - добавление нового субъекта в матрицу с указанием его номера" << endl;
	cout << "3 - удаление Eого субъекта из матрицы" << endl;
	cout << "4 - вычисление процента заполненности матрицы(общее число/хранимое число)" << endl;
	cout << "5 - формирование списка субъектов, имеющих доступ к указанному объекту" << endl;

	int Inp;
	do
	{
		cout << "Введите команду: ";
		cin >> Inp;
		if (Inp == 1)
		{
			cout << "редактирование ячейки" << endl;
			int act, i, j;
			cout << "удаление права - 1, добавление права - 2" << endl;
			cin >> act;
			string rule;
			cout << "введите право, номер субъекта, номер объекта" << endl;
			cin >> rule >> i >> j;
			//i--; j--;
			if (i > n || j > m)
			{
				cout << "не выполнено, такого объекта нет" << endl;
			}
			else
			{
				cout << "выполняется" << endl;
				change_rule(Items, act, i, j, rule);
			}
		}
		if (Inp == 2)
		{
			cout << "добавление субъекта" << endl;
			int new_subj_i;
			cout << "введите числовой индекс(имя) нового субъекта" << endl;
			cin >> new_subj_i;
			cout << "выполняется" << endl;
			insert_new_subj(Items, new_subj_i, m);
		}
		if (Inp == 3)
		{
			cout << "удаление субъекта" << endl;
			int del_subj_i;
			cout << "введите числовой индекс(имя) удаляемого субъекта" << endl;
			cin >> del_subj_i;
			cout << "выполняется" << endl;
			delete_subj(Items, del_subj_i, m);
		}
		if (Inp == 4)
		{
			cout << "вычисление заполненности матрицы" << endl;
			cout << "выполняется" << endl;
			usage_prc(Items, m);
		}
		if (Inp == 5)
		{
			cout << "список субъектов с доступом к объекту T" << endl;
			cout << "введите числовой индекс объекта T" << endl;
			int obj_m;
			cin >> obj_m;
			cout << "выполняется" << endl;
			list_for_t(Items, obj_m, m);
		}
	} while (Inp != 0);
}