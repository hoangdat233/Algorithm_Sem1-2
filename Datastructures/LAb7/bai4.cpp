#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> grid(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> grid[i][j];
        }
    }

    std::vector<std::vector<long long>> dpFromStart(n, std::vector<long long>(m));
    dpFromStart[0][0] = grid[0][0];
    for (int i = 1; i < n; ++i) {
        dpFromStart[i][0] = dpFromStart[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < m; ++j) {
        dpFromStart[0][j] = dpFromStart[0][j - 1] + grid[0][j];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dpFromStart[i][j] = std::max(dpFromStart[i - 1][j], dpFromStart[i][j - 1]) + grid[i][j];
        }
    }

    std::vector<std::vector<long long>> dpFromEnd(n, std::vector<long long>(m));
    dpFromEnd[n - 1][m - 1] = grid[n - 1][m - 1];
    for (int i = n - 2; i >= 0; --i) {
        dpFromEnd[i][m - 1] = dpFromEnd[i + 1][m - 1] + grid[i][m - 1];
    }
    for (int j = m - 2; j >= 0; --j) {
        dpFromEnd[n - 1][j] = dpFromEnd[n - 1][j + 1] + grid[n - 1][j];
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = m - 2; j >= 0; --j) {
            dpFromEnd[i][j] = std::max(dpFromEnd[i + 1][j], dpFromEnd[i][j + 1]) + grid[i][j];
        }
    }

    int queries;
    std::cin >> queries;
    while (queries--) {
        int row, col;
        std::cin >> row >> col;
        std::cout << dpFromStart[row][col] + dpFromEnd[row][col] - grid[row][col] << "\n";
    }

    return 0;
}