#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int MAXK = 105;
const int MAXM = 2005;
const int NEG_INF = -1000000000;

struct Edge {
    int to, need, next;
} edges[MAXN * MAXN];

int n, m;
int edge_cnt;
int head[MAXN];
int indeg[MAXN];

int power_val[MAXN];
int buy_cost[MAXN];
int limit_cnt[MAXN];
int min_cost[MAXN];
int vis[MAXN];

int f[MAXN][MAXK][MAXM];
int g[MAXM];
int ans[MAXM];

void add_edge(int u, int v, int w) {
    edge_cnt++;
    edges[edge_cnt].to = v;
    edges[edge_cnt].need = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt;
    indeg[v]++;
}

void solve(int u) {
    if (vis[u]) {
        return;
    }
    vis[u] = 1;

    if (head[u] == 0) {
        limit_cnt[u] = min(limit_cnt[u], m / buy_cost[u]);
        for (int reserved = limit_cnt[u]; reserved >= 0; reserved--) {
            for (int total = reserved; total <= limit_cnt[u]; total++) {
                int cost = total * buy_cost[u];
                f[u][reserved][cost] = power_val[u] * (total - reserved);
            }
        }
        return;
    }

    limit_cnt[u] = 1000000000;
    min_cost[u] = 0;

    for (int e = head[u]; e != 0; e = edges[e].next) {
        int v = edges[e].to;
        solve(v);
        limit_cnt[u] = min(limit_cnt[u], limit_cnt[v] / edges[e].need);
        min_cost[u] += edges[e].need * min_cost[v];
    }

    limit_cnt[u] = min(limit_cnt[u], m / min_cost[u]);

    for (int total = limit_cnt[u]; total >= 0; total--) {
        for (int cost = 0; cost <= m; cost++) {
            g[cost] = NEG_INF;
        }
        g[0] = 0;

        for (int e = head[u]; e != 0; e = edges[e].next) {
            int v = edges[e].to;
            for (int cost = m; cost >= 0; cost--) {
                int best = NEG_INF;
                for (int used = 0; used <= cost; used++) {
                    if (g[cost - used] == NEG_INF || f[v][total * edges[e].need][used] == NEG_INF) {
                        continue;
                    }
                    best = max(best, g[cost - used] + f[v][total * edges[e].need][used]);
                }
                g[cost] = best;
            }
        }

        for (int reserved = 0; reserved <= total; reserved++) {
            for (int cost = 0; cost <= m; cost++) {
                if (g[cost] == NEG_INF) {
                    continue;
                }
                f[u][reserved][cost] =
                    max(f[u][reserved][cost], g[cost] + power_val[u] * (total - reserved));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(f, 0xc0, sizeof(f));

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> power_val[i];
        char type;
        cin >> type;
        if (type == 'A') {
            int c;
            cin >> c;
            for (int j = 1; j <= c; j++) {
                int x, y;
                cin >> x >> y;
                add_edge(i, x, y);
            }
        } else {
            cin >> buy_cost[i] >> limit_cnt[i];
            min_cost[i] = buy_cost[i];
        }
    }

    for (int i = 0; i <= m; i++) {
        ans[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            solve(i);
            for (int cost = m; cost >= 0; cost--) {
                for (int used = 0; used <= cost; used++) {
                    if (f[i][0][used] == NEG_INF) {
                        continue;
                    }
                    ans[cost] = max(ans[cost], ans[cost - used] + f[i][0][used]);
                }
            }
        }
    }

    cout << ans[m] << '\n';
    return 0;
}
