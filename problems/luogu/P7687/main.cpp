#include <bits/stdc++.h>
using namespace std;

struct Frame {
    int u;
    int in_edge;
    int iter_edge;
};

int n, m, cnt_a, cnt_b;
int total_a, total_b;

vector<int> service_a, service_b;
vector<int> head, to, nxt, edge_id;
vector<int> eu, ev;

vector<int> dfn, low, parent_node, parent_edge;
vector<int> sub_a, sub_b;
vector<int> answer_flag;

int edge_cnt;
int dfs_clock;

void add_edge(int u, int v, int id) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    edge_id[edge_cnt] = id;
    head[u] = edge_cnt;
}

// 非递归 Tarjan 找桥，同时统计每棵 DFS 子树中的 A/B 服务点数量。
void solve_component(int start) {
    vector<Frame> st;
    st.push_back({start, 0, head[start]});

    dfn[start] = low[start] = ++dfs_clock;
    sub_a[start] = service_a[start];
    sub_b[start] = service_b[start];

    while (!st.empty()) {
        Frame &cur = st.back();
        int u = cur.u;

        if (cur.iter_edge != 0) {
            int e = cur.iter_edge;
            cur.iter_edge = nxt[e];
            int v = to[e];

            if (e == (cur.in_edge ^ 1)) {
                continue;
            }

            if (!dfn[v]) {
                parent_node[v] = u;
                parent_edge[v] = e;

                dfn[v] = low[v] = ++dfs_clock;
                sub_a[v] = service_a[v];
                sub_b[v] = service_b[v];

                st.push_back({v, e, head[v]});
                continue;
            }

            if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
            }
            continue;
        }

        st.pop_back();

        if (cur.in_edge != 0) {
            int p = parent_node[u];

            sub_a[p] += sub_a[u];
            sub_b[p] += sub_b[u];
            low[p] = min(low[p], low[u]);

            if (low[u] > dfn[p]) {
                int other_a = total_a - sub_a[u];
                int other_b = total_b - sub_b[u];

                if (sub_a[u] == 0 || sub_b[u] == 0 || other_a == 0 || other_b == 0) {
                    answer_flag[edge_id[cur.in_edge]] = 1;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> cnt_a >> cnt_b;

    service_a.assign(n + 1, 0);
    service_b.assign(n + 1, 0);

    for (int i = 1; i <= cnt_a; i++) {
        int x;
        cin >> x;
        service_a[x] = 1;
    }
    for (int i = 1; i <= cnt_b; i++) {
        int x;
        cin >> x;
        service_b[x] = 1;
    }

    total_a = cnt_a;
    total_b = cnt_b;

    head.assign(n + 1, 0);
    to.assign(2 * m + 5, 0);
    nxt.assign(2 * m + 5, 0);
    edge_id.assign(2 * m + 5, 0);
    eu.assign(m + 1, 0);
    ev.assign(m + 1, 0);

    edge_cnt = 1;

    for (int i = 1; i <= m; i++) {
        cin >> eu[i] >> ev[i];
        add_edge(eu[i], ev[i], i);
        add_edge(ev[i], eu[i], i);
    }

    dfn.assign(n + 1, 0);
    low.assign(n + 1, 0);
    parent_node.assign(n + 1, 0);
    parent_edge.assign(n + 1, 0);
    sub_a.assign(n + 1, 0);
    sub_b.assign(n + 1, 0);
    answer_flag.assign(m + 1, 0);

    dfs_clock = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            solve_component(i);
        }
    }

    int answer_cnt = 0;
    for (int i = 1; i <= m; i++) {
        answer_cnt += answer_flag[i];
    }

    cout << answer_cnt << '\n';
    for (int i = 1; i <= m; i++) {
        if (answer_flag[i]) {
            cout << eu[i] << ' ' << ev[i] << '\n';
        }
    }

    return 0;
}
