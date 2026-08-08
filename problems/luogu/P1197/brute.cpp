// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n, m, k;
vector<int> graph_edges[MAXN];
int destroy_order[MAXN];
bool alive[MAXN], vis[MAXN];

int count_components() {
    memset(vis, false, sizeof(vis));
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        if (!alive[i] || vis[i]) {
            continue;
        }
        cnt++;
        queue<int> q;
        q.push(i);
        vis[i] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int j = 0; j < (int)graph_edges[u].size(); j++) {
                int v = graph_edges[u][j];
                if (alive[v] && !vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph_edges[u].push_back(v);
        graph_edges[v].push_back(u);
    }

    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> destroy_order[i];
    }

    for (int i = 0; i < n; i++) {
        alive[i] = true;
    }

    cout << count_components() << '\n';
    for (int i = 1; i <= k; i++) {
        alive[destroy_order[i]] = false;
        cout << count_components() << '\n';
    }

    return 0;
}
