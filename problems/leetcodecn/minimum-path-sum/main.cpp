#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp = grid[0];
        for (int j = 1; j < n; j++)
            dp[j] += dp[j - 1];
        for (int i = 1; i < m; i++) {
            dp[0] += grid[i][0];
            for (int j = 1; j < n; j++)
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
        }
        return dp[n - 1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> g(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];
    cout << Solution().minPathSum(g) << '\n';
    return 0;
}
