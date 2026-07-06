// main.cpp：用最大子树链倍增求每个连通块重心，换根枚举每条边两侧组件。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOGN = 20;

int n;
vector<int> g[MAXN];
int subtree_size[MAXN], parent_node[MAXN], heavy_son[MAXN];
int jump_heavy[MAXN][LOGN]; // 沿“最大子树儿子”链向下跳
long long answer;

void rebuild_jump(int u) {
    for (int i = 1; i < LOGN; i++) {
        jump_heavy[u][i] = jump_heavy[jump_heavy[u][i - 1]][i - 1];
    }
}

void add_centroid_sum(int root) {
    int u = root;

    // 沿最大子树方向向下跳，直到再往下会小于半棵树。
    for (int i = LOGN - 1; i >= 0; i--) {
        int v = jump_heavy[u][i];
        if (v != 0 && subtree_size[v] * 2 >= subtree_size[root]) {
            u = v;
        }
    }

    answer += u;
    if (subtree_size[u] * 2 == subtree_size[root]) {
        answer += parent_node[u];
    }
}

void dfs_prepare(int u, int fa) {
    parent_node[u] = fa;
    subtree_size[u] = 1;
    heavy_son[u] = 0;

    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        dfs_prepare(v, u);
        subtree_size[u] += subtree_size[v];
        if (subtree_size[v] > subtree_size[heavy_son[u]]) {
            heavy_son[u] = v;
        }
    }

    jump_heavy[u][0] = heavy_son[u];
    rebuild_jump(u);
}

void dfs_reroot(int u, int fa) {
    int first = 0;
    int second = 0;

    // 找出当前 u 的最大、次大相邻组件。换根时要临时排除正在走向的儿子。
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (subtree_size[v] >= subtree_size[first]) {
            second = first;
            first = v;
        } else if (subtree_size[v] >= subtree_size[second]) {
            second = v;
        }
    }

    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }

        // 删边 (u,v) 后，v 这一侧就是以 v 为根的连通块。
        add_centroid_sum(v);

        int old_size_u = subtree_size[u];
        int old_size_v = subtree_size[v];
        int old_parent_u = parent_node[u];
        int old_parent_v = parent_node[v];
        int old_jump_u = jump_heavy[u][0];

        // 临时把 u 这一侧看成一个以 u 为根的连通块。
        jump_heavy[u][0] = (v == first) ? second : first;
        rebuild_jump(u);
        subtree_size[u] -= subtree_size[v];
        subtree_size[v] += subtree_size[u];
        add_centroid_sum(u);

        // 换根进入 v 的方向。
        parent_node[u] = v;
        parent_node[v] = fa;
        dfs_reroot(v, u);

        // 恢复现场。
        parent_node[u] = old_parent_u;
        parent_node[v] = old_parent_v;
        subtree_size[u] = old_size_u;
        subtree_size[v] = old_size_v;
        jump_heavy[u][0] = old_jump_u;
        rebuild_jump(u);
    }
}

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        subtree_size[i] = 0;
        parent_node[i] = 0;
        heavy_son[i] = 0;
        for (int j = 0; j < LOGN; j++) {
            jump_heavy[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    answer = 0;
    dfs_prepare(1, 0);
    dfs_reroot(1, 0);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
