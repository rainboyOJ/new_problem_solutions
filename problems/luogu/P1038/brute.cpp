// brute.cpp：小数据直接按定义递归求值，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, m;
long long init_c[MAXN];
long long u_[MAXN];
int indeg[MAXN], outdeg[MAXN];

struct Edge {
    int from;
    long long w;
};

vector<Edge> pre[MAXN];
bool vis[MAXN];
long long memo[MAXN];

// 直接按定义求神经元 u 的最终状态。
long long dfs(int u) {
    if (vis[u]) {
        return memo[u];
    }
    vis[u] = true;

    if (indeg[u] == 0) {
        memo[u] = init_c[u];
        return memo[u];
    }

    long long sum = -u_[u];
    for (Edge e : pre[u]) {
        long long val = dfs(e.from);
        if (val > 0) {
            sum += val * e.w;
        }
    }

    memo[u] = sum;
    return memo[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> init_c[i] >> u_[i];
        pre[i].clear();
        indeg[i] = 0;
        outdeg[i] = 0;
        vis[i] = false;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        pre[v].push_back({u, w});
        indeg[v]++;
        outdeg[u]++;
    }

    bool has_answer = false;
    for (int i = 1; i <= n; i++) {
        if (outdeg[i] == 0) {
            long long val = dfs(i);
            if (val > 0) {
                cout << i << ' ' << val << '\n';
                has_answer = true;
            }
        }
    }

    if (!has_answer) {
        cout << "NULL\n";
    }

    return 0;
}
