// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m;
vector<int> graph[MAXN];
int close_order[MAXN];
bool alive[MAXN];
bool vis[MAXN];

bool check_connected() {
    int start = 0;
    for (int i = 1; i <= n; i++) {
        if (alive[i]) {
            start = i;
            break;
        }
    }

    if (start == 0) {
        return true;
    }

    for (int i = 1; i <= n; i++) {
        vis[i] = false;
    }

    queue<int> q;
    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (!alive[v] || vis[v]) {
                continue;
            }
            vis[v] = true;
            q.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (alive[i] && !vis[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        alive[i] = true;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        cin >> close_order[i];
    }

    for (int i = 1; i <= n; i++) {
        cout << (check_connected() ? "YES" : "NO") << '\n';
        alive[close_order[i]] = false;
    }

    return 0;
}
