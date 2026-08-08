#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;
const int MAXM = 40005;

int n, S;
int head[MAXN], to[MAXM], nxt[MAXM], cost[MAXM], edge_cnt;
int parent_node[MAXN], parent_cost[MAXN];
int order_list[MAXN], order_cnt;
int remain_need[MAXN];
int answer;
bool impossible;

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
    parent_cost[1] = 0;
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

void solve() {
    build_tree_order();
    answer = 0;
    impossible = false;

    for (int idx = order_cnt - 1; idx >= 0; idx--) {
        int u = order_list[idx];
        int best = 0;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == parent_node[u]) {
                continue;
            }

            int w = cost[i];
            if (w >= S) {
                impossible = true;
                return;
            }

            // 子树里最长的“还没在途中放大”的链，继续经过这条边往上走。
            int need = remain_need[v] + w;

            if (need >= S) {
                // 如果再往上走就断掉，只能在儿子 v 这里安装放大器。
                answer++;
                // 安装后从 u 往下到 v 这条边仍然要承受 w 的衰减。
                if (w > best) {
                    best = w;
                }
            } else {
                if (need > best) {
                    best = need;
                }
            }
        }

        remain_need[u] = best;
    }
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

    solve();

    if (impossible) {
        cout << "No solution.\n";
    } else {
        cout << answer << '\n';
    }

    return 0;
}
