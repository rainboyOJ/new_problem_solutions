// brute.cpp：小数据暴力解，DFS 搜索路径，进入格子后标记、递归、恢复现场必须成对。
#include <bits/stdc++.h>
using namespace std;

int m, n;
char grid[10][10];
string word;
bool vis[10][10];

bool dfs(int i, int j, int idx) {
    if (idx == (int)word.size())
        return true;
    if (i < 0 || i >= m || j < 0 || j >= n || vis[i][j] || grid[i][j] != word[idx])
        return false;
    vis[i][j] = true;
    bool ok = dfs(i - 1, j, idx + 1) || dfs(i + 1, j, idx + 1) || dfs(i, j - 1, idx + 1) ||
              dfs(i, j + 1, idx + 1);
    vis[i][j] = false;
    return ok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];
    cin >> word;
    bool found = false;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (dfs(i, j, 0)) {
                found = true;
                break;
            }
    cout << (found ? 1 : 0) << '\n';
    return 0;
}
