// main.cpp：按数字从小到大贪心确定最终位置，维护每个点周围边的删除顺序约束。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

struct LocalOrder {
    int father[MAXN];
    bool has_prev[MAXN]; // has_prev[x]：在当前点处，连向 x 的边前面已经固定有一条边
    bool has_next[MAXN]; // has_next[x]：在当前点处，连向 x 的边后面已经固定有一条边

    void clear(int n) {
        for (int i = 1; i <= n; i++) {
            father[i] = i;
            has_prev[i] = false;
            has_next[i] = false;
        }
    }

    int find_root(int x) {
        if (father[x] == x) {
            return x;
        }
        father[x] = find_root(father[x]);
        return father[x];
    }

    bool same_chain(int x, int y) {
        return find_root(x) == find_root(y);
    }

    // 在某个点 u 周围，加入“边 x 必须紧接在边 y 之前删除”的关系。
    void join_next(int x, int y) {
        int fx = find_root(x);
        int fy = find_root(y);
        father[fy] = fx;
        has_next[x] = true;
        has_prev[y] = true;
    }
};

int n;
int start_pos[MAXN];       // start_pos[i]：数字 i 初始所在节点
vector<int> graph_edge[MAXN];

int first_edge[MAXN];      // first_edge[u]：点 u 周围已固定的第一条删除边，记录对端点
int last_edge[MAXN];       // last_edge[u]：点 u 周围已固定的最后一条删除边，记录对端点
int chain_count[MAXN];     // 点 u 周围还剩多少条局部关系链
LocalOrder order_info[MAXN];

void clear_case() {
    for (int i = 1; i <= n; i++) {
        graph_edge[i].clear();
        first_edge[i] = 0;
        last_edge[i] = 0;
        chain_count[i] = 0;
        order_info[i].clear(n);
    }
}

bool can_be_end(int u, int in_edge) {
    if (in_edge == 0) {
        return false;
    }
    if (last_edge[u] != 0 && last_edge[u] != in_edge) {
        return false;
    }
    if (order_info[u].has_next[in_edge]) {
        return false;
    }
    if (first_edge[u] != 0 && chain_count[u] > 1 && order_info[u].same_chain(in_edge, first_edge[u])) {
        return false;
    }
    return true;
}

bool can_leave_start(int u, int out_edge) {
    if (first_edge[u] != 0 && first_edge[u] != out_edge) {
        return false;
    }
    if (order_info[u].has_prev[out_edge]) {
        return false;
    }
    if (last_edge[u] != 0 && chain_count[u] > 1 && order_info[u].same_chain(out_edge, last_edge[u])) {
        return false;
    }
    return true;
}

bool can_pass_middle(int u, int in_edge, int out_edge) {
    if (in_edge == last_edge[u]) {
        return false;
    }
    if (out_edge == first_edge[u]) {
        return false;
    }
    if (order_info[u].same_chain(in_edge, out_edge)) {
        return false;
    }
    if (order_info[u].has_next[in_edge]) {
        return false;
    }
    if (order_info[u].has_prev[out_edge]) {
        return false;
    }
    if (first_edge[u] != 0 && last_edge[u] != 0 && chain_count[u] > 2 &&
        order_info[u].same_chain(in_edge, first_edge[u]) &&
        order_info[u].same_chain(out_edge, last_edge[u])) {
        return false;
    }
    return true;
}

int find_best_target(int u, int parent_from) {
    int best = n + 1;

    if (can_be_end(u, parent_from)) {
        best = min(best, u);
    }

    for (int i = 0; i < (int)graph_edge[u].size(); i++) {
        int v = graph_edge[u][i];
        if (v == parent_from) {
            continue;
        }

        bool ok = false;
        if (parent_from == 0) {
            ok = can_leave_start(u, v);
        } else {
            ok = can_pass_middle(u, parent_from, v);
        }

        if (ok) {
            best = min(best, find_best_target(v, u));
        }
    }

    return best;
}

bool apply_path(int u, int parent_from, int target) {
    if (u == target) {
        last_edge[u] = parent_from;
        return true;
    }

    for (int i = 0; i < (int)graph_edge[u].size(); i++) {
        int v = graph_edge[u][i];
        if (v == parent_from) {
            continue;
        }
        if (apply_path(v, u, target)) {
            if (parent_from == 0) {
                first_edge[u] = v;
            } else {
                order_info[u].join_next(parent_from, v);
                chain_count[u]--;
            }
            return true;
        }
    }
    return false;
}

void solve_case() {
    cin >> n;
    clear_case();

    for (int i = 1; i <= n; i++) {
        cin >> start_pos[i];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph_edge[u].push_back(v);
        graph_edge[v].push_back(u);
        chain_count[u]++;
        chain_count[v]++;
    }

    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    for (int value = 1; value <= n; value++) {
        int target = find_best_target(start_pos[value], 0);
        apply_path(start_pos[value], 0, target);

        if (value > 1) {
            cout << ' ';
        }
        cout << target;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        solve_case();
    }

    return 0;
}
