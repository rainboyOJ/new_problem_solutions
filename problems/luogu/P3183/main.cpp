#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int indeg[MAXN], outdeg[MAXN];
int dp[MAXN]; // dp[i] 表示从任意起点走到 i 的食物链条数。

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        indeg[v]++;
        outdeg[u]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
            // 只有不是孤立点的源点，才能作为一条食物链的起点。
            if (outdeg[i] > 0) {
                dp[i] = 1;
            }
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            dp[v] += dp[u];
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        // 只有真正形成路径的汇点才计入答案，孤立点的 dp 仍然是 0。
        if (outdeg[i] == 0) {
            ans += dp[i];
        }
    }

    cout << ans << '\n';
    return 0;
}
