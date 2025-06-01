#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

typedef long long ll;

struct City
{
    int x, y, id;
};

struct Edge
{
    int u, v;
    ll weight;

    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

class DSU
{
private:
    std::vector<int> parent, size;

public:
    DSU(int n) : parent(n), size(n, 1)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        return (parent[x] == x) ? x : (parent[x] = find(parent[x]));
    }

    void unite(int x, int y)
    {
        int rootX = find(x), rootY = find(y);
        if (rootX != rootY)
        {
            if (size[rootX] < size[rootY])
                std::swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

inline ll squaredDistance(const City &a, const City &b)
{
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<City> cities(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> cities[i].x >> cities[i].y;
        cities[i].id = i + 1;
    }

    std::vector<Edge> edges;
    edges.reserve(n * (n - 1) / 2); 

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            edges.emplace_back(Edge{i, j, squaredDistance(cities[i], cities[j])});
        }
    }

    std::sort(edges.begin(), edges.end());

    DSU dsu(n);
    std::vector<std::pair<int, int>> mstEdges;
    double totalWeight = 0.0;

    for (const auto &edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            dsu.unite(edge.u, edge.v);
            mstEdges.emplace_back(edge.u + 1, edge.v + 1);
            totalWeight += std::sqrt(edge.weight);
        }
    }

    std::cout << std::fixed << std::setprecision(6) << totalWeight << "\n"
              << mstEdges.size() << "\n";

    for (const auto &edge : mstEdges)
    {
        int u = edge.first, v = edge.second;
        std::cout << u << " " << v << "\n";
    }

    return 0;
}
