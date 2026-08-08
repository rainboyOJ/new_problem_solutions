// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n, m, p, q;
vector<int> ga[MAXN], gb[MAXN];
bool vis[MAXN];

int bfs_count(vector<int> g[], int start, int limit) {
    for (int i = 1; i <= limit; i++) {
        vis[i] = false;
    }

    queue<int> que;
    que.push(start);
    vis[start] = true;
    int cnt = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        cnt++;

        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                que.push(v);
            }
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> p >> q;

    for (int i = 1; i <= n; i++) {
        ga[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        gb[i].clear();
    }

    for (int i = 1; i <= p; i++) {
        int x, y;
        cin >> x >> y;
        ga[x].push_back(y);
        ga[y].push_back(x);
    }

    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        x = -x;
        y = -y;
        gb[x].push_back(y);
        gb[y].push_back(x);
    }

    int cnt_a = bfs_count(ga, 1, n);
    int cnt_b = bfs_count(gb, 1, m);

    cout << min(cnt_a, cnt_b) << '\n';
    return 0;
}
