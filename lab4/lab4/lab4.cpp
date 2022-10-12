#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


//гамильтонов граф - граф,содержащий гамильтонов цикл - цикл,который проходит через все вершины графа,причём один раз
// 
// 
// надо найти кол-во компонент связности, оно будет являться мин количеством сирен в наборе, удовлетворяющее условиям безопасности 


vector<int> g[1000];//списки смежности
bool used[1000]; // исп-е вершины
vector<int> comp;//вектор компонент связности
vector<int> nodes_vector;//вектор вершин
int matr[1000][1000];

//обход в глубину
void dfs(int v)
{
    used[v] = true;
    comp.push_back(v);
    for (size_t i = 0; i < g[v].size(); ++i)
    {
        if (v == i)
            continue;
        int to = g[v][i];
        if (!used[to] && abs(nodes_vector[v] - matr[v][i]) >= 0)
        {
            if (nodes_vector[v] < nodes_vector[i] - nodes_vector[v])
                nodes_vector[v] = nodes_vector[i] - nodes_vector[v];
            dfs(to);
        }
    }
}


int check_components(int n1)
{
    int i, ans = 0;
    for (i = 0; i < n1; ++i)
        used[i] = false;
    for (i = 0; i < n1; ++i)
        if (!used[i])
        {
            comp.clear();
            dfs(i);
        }
    ans = comp.size();
    return ans;
}

int main()
{
    ifstream input;
    ofstream output;
    input.open("alarmin.txt");
    output.open("alarmout.txt");

    int n1, i, a, b, c;
    if (!input.eof())
    {
        input >> n1;
        for (i = 0; i < n1; i++)
        {
            input >> a;
            nodes_vector.push_back(a);
        }
    }
    while (!input.eof())
    {
        input >> a;
        input >> b;
        input >> c;
        g[a].push_back(b);
        matr[a][b] = c;
    }

    input.close();
    int res = check_components(n1);
    output << res;
    cout << "Done! \nComponents = "<< res;
}