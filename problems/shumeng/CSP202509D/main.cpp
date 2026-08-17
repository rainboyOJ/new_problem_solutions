/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 23:02
 */
#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 30;

// 树链剖分相关数组
int n, m;
vector<int> value_at;       // 每个节点上的权值（0..n-1 的排列）
vector<vector<int> > graph; // 邻接表
vector<int> parent_node;    // 父节点
vector<int> depth;          // 深度
vector<int> subtree_size;   // 子树大小
vector<int> heavy_child;    // 重儿子
vector<int> chain_head;     // 所在链的链头
vector<int> position;       // 节点在剖分序列中的下标(1 起)
vector<int> base_value;     // 剖分序列 position 位置上的权值
vector<pair<int, int> > path_intervals; // 一条路径拆出的剖分区间列表
vector<int> segment_tree;   // 区间最小值线段树(数组实现)
int current_position;       // 剖分序列当前分配到的下标

// 建剖分：先算子树大小和重儿子，再把重链连续编号
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

// 查询剖分序列上 [left, right] 的最小值（闭区间）
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

// 查询路径 (x,y) 之外所有节点权值的最小值。
// 因为权值是 0..n-1 的排列，路径外的第一个缺失值就是路径内权值的 mex。
int query_path_complement_minimum(int x, int y) {
    path_intervals.clear();
    // 用树链剖分把路径拆成 O(log n) 个剖分区间
    while (chain_head[x] != chain_head[y]) {
        if (depth[chain_head[x]] < depth[chain_head[y]]) swap(x, y);
        path_intervals.push_back(make_pair(position[chain_head[x]], position[x]));
        x = parent_node[chain_head[x]];
    }
    int left = min(position[x], position[y]);
    int right = max(position[x], position[y]);
    path_intervals.push_back(make_pair(left, right));

    // 把路径区间按左端点排序，扫描它们之间的空隙求最小值
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
    // 路径覆盖整棵树时不存在路径外节点，mex 为 n
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
