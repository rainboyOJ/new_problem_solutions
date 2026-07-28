#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        function<void(int,int)> dfs = [&](int i, int j) {
            if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') return;
            grid[i][j] = '0';
            dfs(i-1,j); dfs(i+1,j); dfs(i,j-1); dfs(i,j+1);
        };
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '1') { ans++; dfs(i,j); }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<vector<char>> g(m, vector<char>(n));
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> g[i][j];
    cout << Solution().numIslands(g) << '\n';
    return 0;
}
