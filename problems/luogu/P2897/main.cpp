#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long w[MAXN], h[MAXN];
int left_son[MAXN], right_son[MAXN], parent_node[MAXN];
int stk[MAXN], top_idx;
long long sub_width[MAXN];
long long ans[MAXN];

void build_cartesian_tree() {
    top_idx = 0;

    for (int i = 1; i <= n; i++) {
        left_son[i] = right_son[i] = parent_node[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int last = 0;
        while (top_idx > 0 && h[stk[top_idx]] < h[i]) {
            last = stk[top_idx];
            top_idx--;
        }
        if (top_idx > 0) {
            right_son[stk[top_idx]] = i;
            parent_node[i] = stk[top_idx];
        }
        if (last != 0) {
            left_son[i] = last;
            parent_node[last] = i;
        }
        stk[++top_idx] = i;
    }
}

long long dfs_width(int u) {
    if (u == 0) {
        return 0;
    }
    sub_width[u] = w[u] + dfs_width(left_son[u]) + dfs_width(right_son[u]);
    return sub_width[u];
}

// 在一个子树中灌水：
// side=0 表示水从这个子树的左边进入，side=1 表示从右边进入。
// cap 表示外侧“挡板”的高度，且保证 cap > h[u]。
// start 表示开始往这个子树里灌水的时刻。
// 返回把整个子树都灌到高度 cap 所需的总时间。
long long flood_subtree(int u, int side, long long cap, long long start) {
    if (u == 0) {
        return 0;
    }

    long long first_cost = 0;
    long long second_cost = 0;
    long long reach_top_time = start;

    if (side == 0) {
        // 从左边进来，要先把左子树灌到当前根的高度，才能第一次碰到根顶。
        first_cost = flood_subtree(left_son[u], 0, h[u], start);
        reach_top_time = start + first_cost;

        // 根顶被碰到后，水会从根顶继续流向右子树。
        second_cost = flood_subtree(right_son[u], 0, h[u], reach_top_time);
    } else {
        // 从右边进入时完全对称。
        first_cost = flood_subtree(right_son[u], 1, h[u], start);
        reach_top_time = start + first_cost;
        second_cost = flood_subtree(left_son[u], 1, h[u], reach_top_time);
    }

    // 当两侧都被灌到 h[u] 以后，整棵子树才会作为一个整体继续上升。
    ans[u] = reach_top_time + second_cost + sub_width[u];

    return first_cost + second_cost + sub_width[u] * (cap - h[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> h[i];
    }

    build_cartesian_tree();

    int root = stk[1];
    int source = 1;
    for (int i = 2; i <= n; i++) {
        if (h[i] < h[source]) {
            source = i;
        }
    }

    dfs_width(root);

    long long active_width = w[source];
    long long current_time = 0;
    ans[source] = active_width;

    int cur = source;
    while (parent_node[cur] != 0) {
        int p = parent_node[cur];

        // 先把当前已经连通的水体整体抬到父节点的高度。
        current_time += active_width * (h[p] - h[cur]);

        int sibling = 0;
        long long sibling_cost = 0;

        if (left_son[p] == cur) {
            sibling = right_son[p];
            sibling_cost = flood_subtree(sibling, 0, h[p], current_time);
        } else {
            sibling = left_son[p];
            sibling_cost = flood_subtree(sibling, 1, h[p], current_time);
        }

        current_time += sibling_cost;
        active_width += w[p] + sub_width[sibling];

        ans[p] = current_time + active_width;
        cur = p;
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
