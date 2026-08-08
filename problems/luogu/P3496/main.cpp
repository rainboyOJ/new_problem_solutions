#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m;
vector<int> g[MAXN];
int deg_arr[MAXN];
int color_arr[MAXN]; // 0: 未染色, 1: K, 2: S

void bfs_component(int start) {
    queue<int> q;
    color_arr[start] = 1; // 每个连通块根节点固定染成 K
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

    // 只要存在孤立点，就一定无解。
    // 因为这个点无论是否给其中一个行会设办事处，
    // 另一个行会都无法通过相邻城镇来覆盖它。
    for (int i = 1; i <= n; i++) {
        if (deg_arr[i] == 0) {
            cout << "NIE\n";
            return 0;
        }
    }

    // 对每个连通块取一棵生成树，然后二染色。
    // 每个点都会至少有一个生成树中的相邻点颜色与自己相反，
    // 再加上它自己所在的颜色，就能同时被两个行会覆盖。
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
