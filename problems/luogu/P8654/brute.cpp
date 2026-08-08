// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int row_cnt, col_cnt;
int k;
vector<int> g[MAXN];
bool vis[MAXN];

void dfs(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> row_cnt >> col_cnt;
    int tot = row_cnt * col_cnt;

    for (int i = 1; i <= tot; i++) {
        g[i].clear();
        vis[i] = false;
    }

    cin >> k;
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int blocks = 0;
    for (int i = 1; i <= tot; i++) {
        if (!vis[i]) {
            blocks++;
            dfs(i);
        }
    }

    cout << blocks << '\n';
    return 0;
}
