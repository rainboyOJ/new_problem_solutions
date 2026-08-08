#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
long long val[MAXN];
int adj[MAXN][MAXN];

bool is_connected_mask(int mask) {
    if (mask == 0) {
        return true;
    }

    int start = -1;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            start = i;
            break;
        }
    }

    queue<int> q;
    int vis = 0;
    q.push(start);
    vis |= (1 << start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (!adj[u][v]) {
                continue;
            }
            if (!(mask & (1 << v))) {
                continue;
            }
            if (vis & (1 << v)) {
                continue;
            }
            vis |= (1 << v);
            q.push(v);
        }
    }

    return vis == mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个小数据精确暴力：
    // 枚举点集，再判断是否连通并统计点权和。
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u][v] = adj[v][u] = 1;
    }

    long long ans = 0;
    int total = 1 << n;
    for (int mask = 0; mask < total; mask++) {
        if (!is_connected_mask(mask)) {
            continue;
        }
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += val[i];
            }
        }
        ans = max(ans, sum);
    }

    cout << ans << '\n';
    return 0;
}
