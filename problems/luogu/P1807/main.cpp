#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;
const int MAXM = 50005;
const long long NEG_INF = -(1LL << 60);

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], indeg[MAXN], edge_cnt;
long long weight_[MAXM], dp[MAXN];

// 加一条 u -> v, 边权为 w 的有向边。
void add_edge(int u, int v, long long w) {
    ++edge_cnt;
    to[edge_cnt] = v;
    weight_[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    ++indeg[v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    for (int i = 1; i <= n; ++i) {
        dp[i] = NEG_INF;
    }
    dp[1] = 0;

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (dp[u] != NEG_INF) {
                dp[v] = max(dp[v], dp[u] + weight_[i]);
            }
            --indeg[v];
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    if (dp[n] == NEG_INF) {
        cout << -1 << '\n';
    } else {
        cout << dp[n] << '\n';
    }

    return 0;
}
