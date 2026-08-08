#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20000 + 5;
const int MAXM = 200000 + 5;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

int dfn[MAXN], low[MAXN], dfs_clock;
bool is_cut[MAXN];
int root;

void init_graph() {
    edge_cnt = 0;
    dfs_clock = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        is_cut[i] = false;
    }
}

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

// u: 当前点
// fa: DFS 树里的父节点
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++dfs_clock;
    int child = 0;

    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];

        if (v == fa) {
            continue;
        }

        if (!dfn[v]) {
            child++;
            tarjan(v, u);

            low[u] = min(low[u], low[v]);

            // 非根节点：如果某个儿子回不到 u 的祖先，那么 u 是割点。
            if (u != root && low[v] >= dfn[u]) {
                is_cut[u] = true;
            }
        }
        else if (dfn[v] < dfn[u]) {
            // 返祖边只能用祖先的 dfn 更新 low。
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 根节点需要单独判断：它必须至少有两棵 DFS 子树。
    if (u == root && child > 1) {
        is_cut[u] = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_graph();

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            root = i;
            tarjan(i, 0);
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (is_cut[i]) {
            cnt++;
        }
    }

    cout << cnt << '\n';
    for (int i = 1; i <= n; i++) {
        if (is_cut[i]) {
            cout << i << ' ';
        }
    }
    cout << '\n';

    return 0;
}
