#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30000 + 5;

int n;
vector<int> g[MAXN];
int val[MAXN];
int parent_arr[MAXN];
int depth_arr[MAXN];

void build_parent() {
    queue<int> q;
    q.push(1);
    parent_arr[1] = 0;
    depth_arr[1] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (v == parent_arr[u]) {
                continue;
            }
            parent_arr[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            q.push(v);
        }
    }
}

long long query_path_sum(int u, int v) {
    long long ans = 0;
    while (depth_arr[u] > depth_arr[v]) {
        ans += val[u];
        u = parent_arr[u];
    }
    while (depth_arr[v] > depth_arr[u]) {
        ans += val[v];
        v = parent_arr[v];
    }
    while (u != v) {
        ans += val[u] + val[v];
        u = parent_arr[u];
        v = parent_arr[v];
    }
    ans += val[u];
    return ans;
}

int query_path_max(int u, int v) {
    int ans = -30000;
    while (depth_arr[u] > depth_arr[v]) {
        ans = max(ans, val[u]);
        u = parent_arr[u];
    }
    while (depth_arr[v] > depth_arr[u]) {
        ans = max(ans, val[v]);
        v = parent_arr[v];
    }
    while (u != v) {
        ans = max(ans, val[u]);
        ans = max(ans, val[v]);
        u = parent_arr[u];
        v = parent_arr[v];
    }
    ans = max(ans, val[u]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个朴素做法：
    // 每次查询都直接沿父亲往上跳，适合小数据对拍。
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    build_parent();

    int q;
    cin >> q;
    while (q--) {
        string op;
        int u, v;
        cin >> op >> u >> v;
        if (op[1] == 'H') {
            val[u] = v;
        } else if (op[1] == 'M') {
            cout << query_path_max(u, v) << '\n';
        } else {
            cout << query_path_sum(u, v) << '\n';
        }
    }

    return 0;
}
