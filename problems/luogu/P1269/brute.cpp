#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAXM = 55;

int n, S;
int head[MAXN], to[MAXM], nxt[MAXM], cost[MAXM], edge_cnt;
int parent_node[MAXN], parent_cost[MAXN];
int order_list[MAXN], order_cnt;
bool chosen[MAXN];

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    cost[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void build_tree_order() {
    static int q[MAXN];
    int l = 0, r = 0;
    q[r++] = 1;
    parent_node[1] = 0;
    order_cnt = 0;
    while (l < r) {
        int u = q[l++];
        order_list[order_cnt++] = u;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == parent_node[u]) {
                continue;
            }
            parent_node[v] = u;
            parent_cost[v] = cost[i];
            q[r++] = v;
        }
    }
}

bool check_mask() {
    static int strength[MAXN];
    strength[1] = S;

    for (int idx = 1; idx < order_cnt; idx++) {
        int u = order_list[idx];
        int p = parent_node[u];
        strength[u] = strength[p] - parent_cost[u];
        if (strength[u] <= 0) {
            return false;
        }
        if (chosen[u]) {
            strength[u] = S;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int u = 1; u <= n; u++) {
        int k;
        cin >> k;
        for (int i = 0; i < k; i++) {
            int v, w;
            cin >> v >> w;
            if (u < v) {
                add_edge(u, v, w);
                add_edge(v, u, w);
            }
        }
    }
    cin >> S;

    build_tree_order();

    // brute.cpp：枚举所有非根节点是否安装放大器，只适合很小数据对拍。
    int total = n - 1;
    int best = -1;

    for (int mask = 0; mask < (1 << total); mask++) {
        int cnt = 0;
        for (int i = 0; i < total; i++) {
            chosen[i + 2] = ((mask >> i) & 1);
            if (chosen[i + 2]) {
                cnt++;
            }
        }
        if (best != -1 && cnt >= best) {
            continue;
        }
        if (check_mask()) {
            best = cnt;
        }
    }

    if (best == -1) {
        cout << "No solution.\n";
    } else {
        cout << best << '\n';
    }

    return 0;
}
