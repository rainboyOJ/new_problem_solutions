#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250005;
const int LOG = 20;
const long long INF = (1LL << 60);

int n, query_count;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_weight[MAXN * 2], edge_cnt;
int depth_node[MAXN], dfn[MAXN], tout[MAXN], timer_dfn;
int up[MAXN][LOG + 1];
int min_up[MAXN][LOG + 1]; // min_up[x][j] 表示 x 向上跳 2^j 步路径上的最小边权。

int virtual_head[MAXN], virtual_to[MAXN], virtual_nxt[MAXN], virtual_weight[MAXN], virtual_cnt;
bool is_key[MAXN];          // 当前询问中的能源点标记。
long long dp[MAXN];         // 虚树 DP：从该点向下切断所有能源点的最小代价。

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void add_virtual_edge(int u, int v, int w) {
    virtual_cnt++;
    virtual_to[virtual_cnt] = v;
    virtual_weight[virtual_cnt] = w;
    virtual_nxt[virtual_cnt] = virtual_head[u];
    virtual_head[u] = virtual_cnt;
}

void read_tree() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
}

void build_lca() {
    static int iter_edge[MAXN];
    static int stack_node[MAXN];

    for (int i = 1; i <= n; i++) {
        iter_edge[i] = head[i];
    }

    int top = 1;
    stack_node[top] = 1;
    depth_node[1] = 1;
    min_up[1][0] = (int)1e9;
    dfn[1] = ++timer_dfn;

    // 迭代 DFS 生成 dfn/tout，避免 25 万深度时递归爆栈。
    while (top > 0) {
        int u = stack_node[top];
        int &edge_id = iter_edge[u];
        if (edge_id == 0) {
            tout[u] = timer_dfn;
            top--;
            continue;
        }

        int current_edge = edge_id;
        edge_id = nxt[edge_id];
        int v = to[current_edge];
        if (v == up[u][0]) {
            continue;
        }

        up[v][0] = u;
        min_up[v][0] = edge_weight[current_edge];
        depth_node[v] = depth_node[u] + 1;
        for (int j = 1; j <= LOG; j++) {
            up[v][j] = up[up[v][j - 1]][j - 1];
            min_up[v][j] = min(min_up[v][j - 1], min_up[up[v][j - 1]][j - 1]);
        }

        dfn[v] = ++timer_dfn;
        iter_edge[v] = head[v];
        stack_node[++top] = v;
    }
}

bool is_ancestor(int x, int y) {
    return dfn[x] <= dfn[y] && tout[y] <= tout[x];
}

int lca(int x, int y) {
    if (is_ancestor(x, y)) {
        return x;
    }
    if (is_ancestor(y, x)) {
        return y;
    }

    for (int j = LOG; j >= 0; j--) {
        if (up[x][j] != 0 && !is_ancestor(up[x][j], y)) {
            x = up[x][j];
        }
    }
    return up[x][0];
}

int min_edge_on_path(int x, int y) {
    int answer = (int)1e9;
    if (depth_node[x] < depth_node[y]) {
        swap(x, y);
    }

    int diff = depth_node[x] - depth_node[y];
    for (int j = LOG; j >= 0; j--) {
        if ((diff & (1 << j)) != 0) {
            answer = min(answer, min_up[x][j]);
            x = up[x][j];
        }
    }

    if (x == y) {
        return answer;
    }

    for (int j = LOG; j >= 0; j--) {
        if (up[x][j] != up[y][j]) {
            answer = min(answer, min_up[x][j]);
            answer = min(answer, min_up[y][j]);
            x = up[x][j];
            y = up[y][j];
        }
    }
    answer = min(answer, min_up[x][0]);
    answer = min(answer, min_up[y][0]);
    return answer;
}

bool cmp_dfn(int x, int y) {
    return dfn[x] < dfn[y];
}

long long solve_one_query(vector<int> &key_nodes) {
    vector<int> nodes = key_nodes;
    sort(nodes.begin(), nodes.end(), cmp_dfn);

    int original_size = (int)nodes.size();
    for (int i = 0; i + 1 < original_size; i++) {
        nodes.push_back(lca(nodes[i], nodes[i + 1]));
    }
    nodes.push_back(1);

    sort(nodes.begin(), nodes.end(), cmp_dfn);
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    for (int i = 0; i < (int)nodes.size(); i++) {
        virtual_head[nodes[i]] = 0;
        dp[nodes[i]] = 0;
    }
    virtual_cnt = 0;

    // 单调栈建虚树：相邻虚树节点之间的边权为原树路径上的最小边权。
    vector<int> stack_nodes;
    for (int i = 0; i < (int)nodes.size(); i++) {
        int x = nodes[i];
        while (!stack_nodes.empty() && !is_ancestor(stack_nodes.back(), x)) {
            stack_nodes.pop_back();
        }
        if (!stack_nodes.empty()) {
            int parent = stack_nodes.back();
            add_virtual_edge(parent, x, min_edge_on_path(parent, x));
        }
        stack_nodes.push_back(x);
    }

    // 虚树 DP：对每个子树，要么切掉连接父亲的这条路径，要么继续在子树内部切。
    for (int i = (int)nodes.size() - 1; i >= 0; i--) {
        int u = nodes[i];
        long long sum = 0;
        for (int e = virtual_head[u]; e != 0; e = virtual_nxt[e]) {
            int v = virtual_to[e];
            long long cut_cost = virtual_weight[e];
            if (is_key[v]) {
                sum += cut_cost;
            } else {
                sum += min(dp[v], cut_cost);
            }
        }
        dp[u] = sum;
    }

    return dp[1];
}

void solve() {
    build_lca();

    cin >> query_count;
    for (int qi = 1; qi <= query_count; qi++) {
        int k;
        cin >> k;
        vector<int> key_nodes(k);
        for (int i = 0; i < k; i++) {
            cin >> key_nodes[i];
            is_key[key_nodes[i]] = true;
        }

        cout << solve_one_query(key_nodes) << '\n';

        for (int i = 0; i < k; i++) {
            is_key[key_nodes[i]] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_tree();
    solve();

    return 0;
}
