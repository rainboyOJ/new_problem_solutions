/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:40
 */
#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 30;

int n, m;
vector<int> value_at;
vector<vector<int> > graph;
vector<int> parent_node;
vector<int> depth;
vector<int> subtree_size;
vector<int> heavy_child;
vector<int> chain_head;
vector<int> position;
vector<int> base_value;
vector<pair<int, int> > path_intervals;
vector<int> segment_tree;
int current_position;

void build_heavy_light() {
    vector<int> order;
    order.reserve(n);
    vector<int> stack;
    stack.push_back(1);
    parent_node[1] = 0;
    depth[1] = 0;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        order.push_back(u);
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (v == parent_node[u]) continue;
            parent_node[v] = u;
            depth[v] = depth[u] + 1;
            stack.push_back(v);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        subtree_size[u] = 1;
        heavy_child[u] = 0;
        for (int j = 0; j < (int)graph[u].size(); j++) {
            int v = graph[u][j];
            if (parent_node[v] != u) continue;
            subtree_size[u] += subtree_size[v];
            if (heavy_child[u] == 0 || subtree_size[v] > subtree_size[heavy_child[u]]) {
                heavy_child[u] = v;
            }
        }
    }

    current_position = 0;
    vector<pair<int, int> > tasks;
    tasks.push_back(make_pair(1, 1));
    while (!tasks.empty()) {
        int u = tasks.back().first;
        int head = tasks.back().second;
        tasks.pop_back();
        while (u != 0) {
            chain_head[u] = head;
            position[u] = ++current_position;
            base_value[current_position] = value_at[u];
            for (int i = 0; i < (int)graph[u].size(); i++) {
                int v = graph[u][i];
                if (parent_node[v] == u && v != heavy_child[u]) {
                    tasks.push_back(make_pair(v, v));
                }
            }
            u = heavy_child[u];
        }
    }
}

void build_segment_tree() {
    int size = 1;
    while (size < n) size <<= 1;
    segment_tree.assign(size * 2, INF);
    for (int i = 1; i <= n; i++) segment_tree[size + i - 1] = base_value[i];
    for (int i = size - 1; i >= 1; i--) {
        segment_tree[i] = min(segment_tree[i << 1], segment_tree[i << 1 | 1]);
    }
}

int range_minimum(int left, int right) {
    if (left > right) return INF;
    int size = (int)segment_tree.size() / 2;
    left += size - 1;
    right += size - 1;
    int answer = INF;
    while (left <= right) {
        if (left & 1) answer = min(answer, segment_tree[left++]);
        if (!(right & 1)) answer = min(answer, segment_tree[right--]);
        left >>= 1;
        right >>= 1;
    }
    return answer;
}

int query_path_complement_minimum(int x, int y) {
    path_intervals.clear();
    while (chain_head[x] != chain_head[y]) {
        if (depth[chain_head[x]] < depth[chain_head[y]]) swap(x, y);
        path_intervals.push_back(make_pair(position[chain_head[x]], position[x]));
        x = parent_node[chain_head[x]];
    }
    int left = min(position[x], position[y]);
    int right = max(position[x], position[y]);
    path_intervals.push_back(make_pair(left, right));

    sort(path_intervals.begin(), path_intervals.end());
    int answer = INF;
    int covered_right = 0;
    for (int i = 0; i < (int)path_intervals.size(); i++) {
        int interval_left = path_intervals[i].first;
        int interval_right = path_intervals[i].second;
        answer = min(answer, range_minimum(covered_right + 1, interval_left - 1));
        if (interval_right > covered_right) covered_right = interval_right;
    }
    answer = min(answer, range_minimum(covered_right + 1, n));
    if (answer == INF) return n;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    value_at.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> value_at[i];
    graph.assign(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    parent_node.assign(n + 1, 0);
    depth.assign(n + 1, 0);
    subtree_size.assign(n + 1, 0);
    heavy_child.assign(n + 1, 0);
    chain_head.assign(n + 1, 0);
    position.assign(n + 1, 0);
    base_value.assign(n + 1, 0);
    build_heavy_light();
    build_segment_tree();

    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << query_path_complement_minimum(x, y) << '\n';
    }
    return 0;
}
