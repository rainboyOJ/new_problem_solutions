// brute.cpp：小数据暴力枚举所有删边顺序，直接模拟交换过程。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
};

const int MAXN = 12;

int n;
int initial_pos[MAXN];
vector<Edge> edges;

vector<int> solve_by_greedy_for_sample(); // 大样例兜底，随机对拍只生成 n <= 8。

vector<int> simulate_order(const vector<int> &order) {
    int number_on_node[MAXN];
    int final_pos[MAXN];

    for (int value = 1; value <= n; value++) {
        number_on_node[initial_pos[value]] = value;
    }

    for (int i = 0; i < (int)order.size(); i++) {
        Edge e = edges[order[i]];
        swap(number_on_node[e.u], number_on_node[e.v]);
    }

    for (int node = 1; node <= n; node++) {
        final_pos[number_on_node[node]] = node;
    }

    vector<int> answer(n + 1);
    for (int value = 1; value <= n; value++) {
        answer[value] = final_pos[value];
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> initial_pos[i];
        }

        edges.clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }

        vector<int> best(n + 1, n + 1);

        if (n <= 8) {
            vector<int> order;
            for (int i = 0; i < n - 1; i++) {
                order.push_back(i);
            }

            do {
                vector<int> cur = simulate_order(order);
                if (lexicographical_compare(cur.begin() + 1, cur.end(), best.begin() + 1, best.end())) {
                    best = cur;
                }
            } while (next_permutation(order.begin(), order.end()));
        } else {
            best = solve_by_greedy_for_sample();
        }

        for (int i = 1; i <= n; i++) {
            if (i > 1) {
                cout << ' ';
            }
            cout << best[i];
        }
        cout << '\n';
    }

    return 0;
}

// 下面是和 main.cpp 同思路的简化版，只用于让官方样例中的 n=10 数据也能运行。
const int MAXB = 2005;
vector<int> brute_graph[MAXB];
int first_edge_b[MAXB], last_edge_b[MAXB], chain_count_b[MAXB];

struct LocalOrderB {
    int father[MAXB];
    bool has_prev[MAXB], has_next[MAXB];

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

    void join_next(int x, int y) {
        father[find_root(y)] = find_root(x);
        has_next[x] = true;
        has_prev[y] = true;
    }
} order_b[MAXB];

bool can_end_b(int u, int in_edge) {
    if (in_edge == 0) {
        return false;
    }
    if (last_edge_b[u] != 0 && last_edge_b[u] != in_edge) {
        return false;
    }
    if (order_b[u].has_next[in_edge]) {
        return false;
    }
    if (first_edge_b[u] != 0 && chain_count_b[u] > 1 && order_b[u].same_chain(in_edge, first_edge_b[u])) {
        return false;
    }
    return true;
}

bool can_start_b(int u, int out_edge) {
    if (first_edge_b[u] != 0 && first_edge_b[u] != out_edge) {
        return false;
    }
    if (order_b[u].has_prev[out_edge]) {
        return false;
    }
    if (last_edge_b[u] != 0 && chain_count_b[u] > 1 && order_b[u].same_chain(out_edge, last_edge_b[u])) {
        return false;
    }
    return true;
}

bool can_middle_b(int u, int in_edge, int out_edge) {
    if (in_edge == last_edge_b[u] || out_edge == first_edge_b[u]) {
        return false;
    }
    if (order_b[u].same_chain(in_edge, out_edge)) {
        return false;
    }
    if (order_b[u].has_next[in_edge] || order_b[u].has_prev[out_edge]) {
        return false;
    }
    if (first_edge_b[u] != 0 && last_edge_b[u] != 0 && chain_count_b[u] > 2 &&
        order_b[u].same_chain(in_edge, first_edge_b[u]) &&
        order_b[u].same_chain(out_edge, last_edge_b[u])) {
        return false;
    }
    return true;
}

int dfs_find_b(int u, int parent_from) {
    int best = n + 1;
    if (can_end_b(u, parent_from)) {
        best = min(best, u);
    }
    for (int i = 0; i < (int)brute_graph[u].size(); i++) {
        int v = brute_graph[u][i];
        if (v == parent_from) {
            continue;
        }
        if ((parent_from == 0 && can_start_b(u, v)) ||
            (parent_from != 0 && can_middle_b(u, parent_from, v))) {
            best = min(best, dfs_find_b(v, u));
        }
    }
    return best;
}

bool dfs_apply_b(int u, int parent_from, int target) {
    if (u == target) {
        last_edge_b[u] = parent_from;
        return true;
    }
    for (int i = 0; i < (int)brute_graph[u].size(); i++) {
        int v = brute_graph[u][i];
        if (v == parent_from) {
            continue;
        }
        if (dfs_apply_b(v, u, target)) {
            if (parent_from == 0) {
                first_edge_b[u] = v;
            } else {
                order_b[u].join_next(parent_from, v);
                chain_count_b[u]--;
            }
            return true;
        }
    }
    return false;
}

vector<int> solve_by_greedy_for_sample() {
    for (int i = 1; i <= n; i++) {
        brute_graph[i].clear();
        first_edge_b[i] = last_edge_b[i] = chain_count_b[i] = 0;
        order_b[i].clear(n);
    }
    for (int i = 0; i < (int)edges.size(); i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        brute_graph[u].push_back(v);
        brute_graph[v].push_back(u);
        chain_count_b[u]++;
        chain_count_b[v]++;
    }

    vector<int> result(n + 1);
    for (int value = 1; value <= n; value++) {
        int target = dfs_find_b(initial_pos[value], 0);
        dfs_apply_b(initial_pos[value], 0, target);
        result[value] = target;
    }
    return result;
}
