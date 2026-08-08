#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n;
long long w[MAXN], h[MAXN];
int left_son[MAXN], right_son[MAXN], parent_node[MAXN];
long long sub_width[MAXN];
long long ans[MAXN];

int build_tree(int l, int r) {
    if (l > r) {
        return 0;
    }

    int root = l;
    for (int i = l + 1; i <= r; i++) {
        if (h[i] > h[root]) {
            root = i;
        }
    }

    left_son[root] = build_tree(l, root - 1);
    right_son[root] = build_tree(root + 1, r);
    if (left_son[root] != 0) {
        parent_node[left_son[root]] = root;
    }
    if (right_son[root] != 0) {
        parent_node[right_son[root]] = root;
    }
    return root;
}

long long dfs_width(int u) {
    if (u == 0) {
        return 0;
    }
    sub_width[u] = w[u] + dfs_width(left_son[u]) + dfs_width(right_son[u]);
    return sub_width[u];
}

// 慢速版本仍然使用同样的递归水位模型，只是建树改成 O(n^2)。
long long flood_subtree(int u, int side, long long cap, long long start) {
    if (u == 0) {
        return 0;
    }

    long long first_cost = 0;
    long long second_cost = 0;
    long long reach_top_time = start;

    if (side == 0) {
        first_cost = flood_subtree(left_son[u], 0, h[u], start);
        reach_top_time = start + first_cost;
        second_cost = flood_subtree(right_son[u], 0, h[u], reach_top_time);
    } else {
        first_cost = flood_subtree(right_son[u], 1, h[u], start);
        reach_top_time = start + first_cost;
        second_cost = flood_subtree(left_son[u], 1, h[u], reach_top_time);
    }

    ans[u] = reach_top_time + second_cost + sub_width[u];
    return first_cost + second_cost + sub_width[u] * (cap - h[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> h[i];
        left_son[i] = right_son[i] = parent_node[i] = 0;
        sub_width[i] = ans[i] = 0;
    }

    int root = build_tree(1, n);
    dfs_width(root);

    int source = 1;
    for (int i = 2; i <= n; i++) {
        if (h[i] < h[source]) {
            source = i;
        }
    }

    long long active_width = w[source];
    long long current_time = 0;
    ans[source] = active_width;

    int cur = source;
    while (parent_node[cur] != 0) {
        int p = parent_node[cur];

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
