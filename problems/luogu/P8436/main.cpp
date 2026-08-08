#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 5;
const int MAXM = 4000000 + 5;

int n, m;

// 链式前向星存图，边编号从 0 开始，方便用 i ^ 1 找反向边。
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

// Tarjan 找桥需要的时间戳数组。
int dfn[MAXN], low[MAXN], dfs_clock;
bool is_bridge[MAXM];

// 非递归 DFS 需要记录当前处理到哪一条边。
int iter_edge[MAXN];
int parent_node[MAXN], parent_edge[MAXN];

// 第二遍忽略桥做 DFS 染色。
bool vis[MAXN];
int comp_iter[MAXN];

vector< vector<int> > answer;

void init_graph(int n) {
    edge_cnt = 0;
    dfs_clock = 0;
    answer.clear();

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        vis[i] = false;
    }
}

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

// 非递归 Tarjan：先找出所有桥。
void tarjan_bridge() {
    vector<int> st;
    st.reserve(n);

    for (int start = 1; start <= n; start++) {
        if (dfn[start]) {
            continue;
        }

        parent_node[start] = 0;
        parent_edge[start] = -1;
        st.push_back(start);

        while (!st.empty()) {
            int u = st.back();

            if (!dfn[u]) {
                dfn[u] = low[u] = ++dfs_clock;
                iter_edge[u] = head[u];
            }

            int &i = iter_edge[u];
            if (i != -1) {
                int e = i;
                i = nxt[i];
                int v = to[e];

                if (e == (parent_edge[u] ^ 1)) {
                    continue;
                }

                if (!dfn[v]) {
                    parent_node[v] = u;
                    parent_edge[v] = e;
                    st.push_back(v);
                    continue;
                }

                // 已访问点只在它是祖先时更新 low。
                if (dfn[v] < dfn[u]) {
                    low[u] = min(low[u], dfn[v]);
                }
                continue;
            }

            st.pop_back();
            if (parent_edge[u] != -1) {
                int p = parent_node[u];
                low[p] = min(low[p], low[u]);

                if (low[u] > dfn[p]) {
                    is_bridge[parent_edge[u]] = true;
                    is_bridge[parent_edge[u] ^ 1] = true;
                }
            }
        }
    }
}

// 第二遍 DFS：忽略所有桥，遍历顺序尽量保持和递归版一致。
void collect_component(int start) {
    vector<int> comp;
    vector<int> st;

    vis[start] = true;
    comp.push_back(start);
    comp_iter[start] = head[start];
    st.push_back(start);

    while (!st.empty()) {
        int u = st.back();
        int &i = comp_iter[u];
        bool advanced = false;

        while (i != -1) {
            int e = i;
            i = nxt[i];
            int v = to[e];

            if (is_bridge[e] || vis[v]) {
                continue;
            }

            vis[v] = true;
            comp.push_back(v);
            comp_iter[v] = head[v];
            st.push_back(v);
            advanced = true;
            break;
        }

        if (!advanced && i == -1) {
            st.pop_back();
        }
    }

    answer.push_back(comp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_graph(n);

    for (int i = 0; i < 2 * m; i++) {
        is_bridge[i] = false;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    tarjan_bridge();

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            collect_component(i);
        }
    }

    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i].size();
        for (size_t j = 0; j < answer[i].size(); j++) {
            cout << ' ' << answer[i][j];
        }
        cout << '\n';
    }

    return 0;
}
