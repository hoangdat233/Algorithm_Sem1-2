#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Point {
    int x, y, z;
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
};

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

bool isSafe(int x, int y, int z, const vector<vector<vector<bool>>>& occupied) {
    return x >= 0 && x < 102 && y >= 0 && y < 102 && z >= 0 && z < 102 && !occupied[x][y][z];
}

int bfs(const Point& start, const Point& end, const vector<vector<vector<bool>>>& occupied) {
    vector<vector<vector<int>>> dist(102, vector<vector<int>>(102, vector<int>(102, INT_MAX)));
    queue<Point> q;
    q.push(start);
    dist[start.x][start.y][start.z] = 0;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y && current.z == end.z) {
            return dist[current.x][current.y][current.z];
        }

        for (int i = 0; i < 6; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            int nz = current.z + dz[i];

            if (isSafe(nx, ny, nz, occupied) && dist[nx][ny][nz] == INT_MAX) {
                dist[nx][ny][nz] = dist[current.x][current.y][current.z] + 1;
                q.push(Point(nx, ny, nz));
            }
        }
    }

    return -1;
}

int main() {
    int K, E;
    cin >> K >> E;

    int xa, ya, za;
    cin >> xa >> ya >> za;

    int xf, yf, zf;
    cin >> xf >> yf >> zf;

    vector<vector<vector<bool>>> occupied(102, vector<vector<bool>>(102, vector<bool>(102, false)));

    for (int i = 0; i < K; ++i) {
        int xi, yi, zi, hi;
        cin >> xi >> yi >> zi >> hi;
        for (int z = zi; z < zi + hi; ++z) {
            occupied[xi][yi][z] = true;
        }
    }

    Point start(xa, ya, za);
    Point end(xf, yf, zf);

    if (start.x == end.x && start.y == end.y && start.z == end.z) {
        cout << 0 << endl;
        return 0;
    }
    int energy = bfs(start, end, occupied);
    if (energy == -1 || energy > E) {
        cout << -1 << endl;
    } else {
        cout << energy << endl;
    }
    return 0;
}