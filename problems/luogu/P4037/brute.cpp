#include <bits/stdc++.h>
using namespace std;

const int NEG_INF = -1000000000;

struct NodeInfo {
    int power;
    char type;
    int cost;
    int limit;
    vector<pair<int, int> > child;
};

int n, m;
NodeInfo nodes[55];
int indeg[55];
int max_make[55];
int min_cost[55];
vector<vector<int> > dp_node[55];
int ans[2005];

void solve(int u) {
    if (!dp_node[u].empty()) {
        return;
    }

    if (nodes[u].type == 'B') {
        max_make[u] = min(nodes[u].limit, m / nodes[u].cost);
        min_cost[u] = nodes[u].cost;
        dp_node[u].assign(max_make[u] + 1, vector<int>(m + 1, NEG_INF));

        for (int reserved = 0; reserved <= max_make[u]; reserved++) {
            for (int total = reserved; total <= max_make[u]; total++) {
                int cost = total * nodes[u].cost;
                dp_node[u][reserved][cost] = nodes[u].power * (total - reserved);
            }
        }
        return;
    }

    max_make[u] = 1000000000;
    min_cost[u] = 0;
    for (size_t i = 0; i < nodes[u].child.size(); i++) {
        int v = nodes[u].child[i].first;
        int need = nodes[u].child[i].second;
        solve(v);
        max_make[u] = min(max_make[u], max_make[v] / need);
        min_cost[u] += need * min_cost[v];
    }
    max_make[u] = min(max_make[u], m / min_cost[u]);

    dp_node[u].assign(max_make[u] + 1, vector<int>(m + 1, NEG_INF));

    for (int total = 0; total <= max_make[u]; total++) {
        vector<int> cur(m + 1, NEG_INF);
        cur[0] = 0;

        for (size_t i = 0; i < nodes[u].child.size(); i++) {
            int v = nodes[u].child[i].first;
            int need = nodes[u].child[i].second;
            vector<int> nxt(m + 1, NEG_INF);
            for (int c1 = 0; c1 <= m; c1++) {
                if (cur[c1] == NEG_INF) {
                    continue;
                }
                for (int c2 = 0; c1 + c2 <= m; c2++) {
                    if (dp_node[v][total * need][c2] == NEG_INF) {
                        continue;
                    }
                    nxt[c1 + c2] = max(nxt[c1 + c2], cur[c1] + dp_node[v][total * need][c2]);
                }
            }
            cur.swap(nxt);
        }

        for (int reserved = 0; reserved <= total; reserved++) {
            for (int cost = 0; cost <= m; cost++) {
                if (cur[cost] == NEG_INF) {
                    continue;
                }
                dp_node[u][reserved][cost] =
                    max(dp_node[u][reserved][cost], cur[cost] + nodes[u].power * (total - reserved));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据精确 DP，用来帮助理解并辅助对拍。
    // 仍按题目的合成树定义做状态，但不做任何额外优化。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> nodes[i].power >> nodes[i].type;
        if (nodes[i].type == 'A') {
            int c;
            cin >> c;
            nodes[i].child.resize(c);
            for (int j = 0; j < c; j++) {
                int x, y;
                cin >> x >> y;
                nodes[i].child[j] = make_pair(x, y);
                indeg[x]++;
            }
        } else {
            cin >> nodes[i].cost >> nodes[i].limit;
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
                    if (dp_node[i][0][used] == NEG_INF) {
                        continue;
                    }
                    ans[cost] = max(ans[cost], ans[cost - used] + dp_node[i][0][used]);
                }
            }
        }
    }

    cout << ans[m] << '\n';
    return 0;
}
