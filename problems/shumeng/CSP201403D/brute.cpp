/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:51
 */
// brute.cpp：小数据暴力解，枚举每个候选位置是否增设路由器。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 205;
const int INF = 0x3f3f3f3f;

int n, m, k;
long long r;
long long x[MAXV], y[MAXV];
vector<int> graph[MAXV];
int choose[MAXV];
int best;

bool can_connect(int a, int b) {
    long long dx = x[a] - x[b];
    long long dy = y[a] - y[b];
    return dx * dx + dy * dy <= r * r;
}

int shortest_path() {
    int dist[MAXV];
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (v > n && !choose[v - n]) {
                continue;
            }
            if (dist[v] != INF) {
                continue;
            }
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    return dist[2];
}

void dfs(int pos) {
    if (pos > m) {
        int added = 0;
        for (int i = 1; i <= m; i++) {
            added += choose[i];
        }
        if (added > k) {
            return;
        }
        best = min(best, shortest_path());
        return;
    }

    choose[pos] = 0;
    dfs(pos + 1);
    choose[pos] = 1;
    dfs(pos + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> r;
    int total = n + m;
    for (int i = 1; i <= total; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= total; i++) {
        for (int j = i + 1; j <= total; j++) {
            if (can_connect(i, j)) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    best = INF;
    dfs(1);
    cout << best - 1 << '\n';
    return 0;
}
