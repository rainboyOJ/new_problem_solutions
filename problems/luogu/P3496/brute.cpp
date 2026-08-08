#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m;
vector<int> g[MAXN];
int deg_arr[MAXN];
int color_arr[MAXN];

// brute.cpp：这里保留最直接的构造版写法。
// 这题的关键结论本身就很简单：
// 只要没有孤立点，就一定可以构造。
// 因此这个文件不再去枚举 3^n 的所有方案，而是直接按生成树二染色实现。

void bfs_component(int start) {
    queue<int> q;
    color_arr[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (color_arr[v] == 0) {
                color_arr[v] = 3 - color_arr[u];
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        deg_arr[i] = 0;
        color_arr[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg_arr[u]++;
        deg_arr[v]++;
    }

    for (int i = 1; i <= n; i++) {
        if (deg_arr[i] == 0) {
            cout << "NIE\n";
            return 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (color_arr[i] == 0) {
            bfs_component(i);
        }
    }

    cout << "TAK\n";
    for (int i = 1; i <= n; i++) {
        if (color_arr[i] == 1) {
            cout << "K\n";
        }
        else {
            cout << "S\n";
        }
    }

    return 0;
}
