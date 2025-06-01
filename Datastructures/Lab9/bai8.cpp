#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int a, b, w;
};

int main()
{
    int N, M;
    cin >> N >> M;

    vector<Edge> edges;

    // Создаем минимальное остовное дерево (MST)
    for (int i = 2; i <= N; i++)
    {
        edges.push_back({i - 1, i, i - 2});
    }

    // Добавляем дополнительные рёбра, чтобы максимизировать количество релаксаций
    for (int i = 1; i <= N && (int)edges.size() < M; i++)
    {
        for (int j = i + 2; j <= N && (int)edges.size() < M; j++)
        {
            edges.push_back({i, j, (i + j) % 5 + 1});
        }
    }

    // Вывод рёбер
    for (const auto &edge : edges)
    {
        cout << edge.a << " " << edge.b << " " << edge.w << "\n";
    }

    return 0;
}