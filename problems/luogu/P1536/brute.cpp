// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

vector<int> graph[MAXN];
bool vis[MAXN];

void dfs(int u) {
    vis[u] = true;
    for (int v : graph[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        cin >> m;

        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            vis[i] = false;
        }

        for (int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        int blocks = 0;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                blocks++;
                dfs(i);
            }
        }

        cout << blocks - 1 << '\n';
    }

    return 0;
}
