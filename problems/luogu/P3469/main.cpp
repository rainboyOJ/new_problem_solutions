#include <bits/stdc++.h>
using namespace std;

struct Frame {
    int u;          // 当前点
    int iter_edge;  // 当前枚举到哪条边
};

int n, m;
vector<int> head, to, nxt;
int edge_cnt;

vector<int> dfn, low, parent_node, parent_edge;
vector<int> sub_size, child_cnt;
vector<long long> cut_sum, answer;
int dfs_clock;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 非递归 Tarjan 求割点相关贡献。
// answer[u] 统计“封锁 u 以后，无法发生的有序访问次数”。
void solve_component(int start) {
    vector<Frame> st;

    st.push_back({start, head[start]});
    parent_node[start] = 0;
    parent_edge[start] = 0;

    dfn[start] = low[start] = ++dfs_clock;
    sub_size[start] = 1;
    child_cnt[start] = 0;
    cut_sum[start] = 0;
    answer[start] = 2LL * (n - 1);

    while (!st.empty()) {
        Frame &cur = st.back();
        int u = cur.u;

        if (cur.iter_edge != 0) {
            int e = cur.iter_edge;
            cur.iter_edge = nxt[e];
            int v = to[e];

            if (e == (parent_edge[u] ^ 1)) {
                continue;
            }

            if (!dfn[v]) {
                parent_node[v] = u;
                parent_edge[v] = e;
                child_cnt[u]++;

                dfn[v] = low[v] = ++dfs_clock;
                sub_size[v] = 1;
                child_cnt[v] = 0;
                cut_sum[v] = 0;
                answer[v] = 2LL * (n - 1);

                st.push_back({v, head[v]});
                continue;
            }

            if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
            }
            continue;
        }

        st.pop_back();

        // u 的所有儿子都处理完了，现在把“剩余那个大块”的贡献补上。
        answer[u] += 2LL * cut_sum[u] * (n - 1 - cut_sum[u]);

        if (parent_node[u] != 0) {
            int p = parent_node[u];
            sub_size[p] += sub_size[u];
            low[p] = min(low[p], low[u]);

            // 删除 p 后，u 子树会单独裂成一个连通块。
            if (low[u] >= dfn[p]) {
                answer[p] += 2LL * cut_sum[p] * sub_size[u];
                cut_sum[p] += sub_size[u];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    head.assign(n + 1, 0);
    to.assign(2 * m + 5, 0);
    nxt.assign(2 * m + 5, 0);
    edge_cnt = 1;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    dfn.assign(n + 1, 0);
    low.assign(n + 1, 0);
    parent_node.assign(n + 1, 0);
    parent_edge.assign(n + 1, 0);
    sub_size.assign(n + 1, 0);
    child_cnt.assign(n + 1, 0);
    cut_sum.assign(n + 1, 0);
    answer.assign(n + 1, 0);
    dfs_clock = 0;

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            solve_component(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
