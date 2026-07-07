#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

struct Edge {
    int u, v, w;
};

int n, q_need;
Edge edges[MAXN];
vector<pair<int, int> > g[MAXN];
int chosen[MAXN]; // chosen[i] = 0/1，表示第 i 条边不保留/保留
int ans;

int calc_chosen_count() {
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (chosen[i] == 1) cnt++;
    }
    return cnt;
}

bool check() {
    if (calc_chosen_count() != q_need) {
        return false;
    }

    vector<int> vis(n + 1, 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    int connected_edges = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (size_t i = 0; i < g[u].size(); i++) {
            int id = g[u][i].second;
            int v = g[u][i].first;
            if (chosen[id] == 0 || vis[v]) {
                continue;
            }
            vis[v] = 1;
            connected_edges++;
            q.push(v);
        }
    }

    return connected_edges == q_need;
}

int calc_answer() {
    vector<int> vis(n + 1, 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    int sum = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (size_t i = 0; i < g[u].size(); i++) {
            int id = g[u][i].second;
            int v = g[u][i].first;
            if (chosen[id] == 0 || vis[v]) {
                continue;
            }
            vis[v] = 1;
            sum += edges[id].w;
            q.push(v);
        }
    }

    return sum;
}

void dfs_choose(int dep) {
    if (dep == n) {
        if (check()) {
            int value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    // 第 dep 条边的 01 选择：0 不保留，1 保留。
    for (int i = 0; i <= 1; i++) {
        chosen[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举保留哪些边，再检查这些边是否仍然和根连通。
    cin >> n >> q_need;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 1; i < n; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        g[edges[i].u].push_back({edges[i].v, i});
        g[edges[i].v].push_back({edges[i].u, i});
        chosen[i] = 0;
    }

    ans = 0;
    dfs_choose(1);
    cout << ans << '\n';
    return 0;
}
