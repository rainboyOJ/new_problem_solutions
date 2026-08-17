/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:54
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Edge {
    int to;
    int length;
};

// 一段“最低价格保持不变”的连续路程：(price, length)
struct Group {
    int price;   // 这段路程统一采用的价格
    int length;  // 这段路程的总长度
};

// 前缀统计：(length, cost) 表示前若干段的总长度与总花费
struct Prefix {
    int length;
    long long cost;
};

// 一段链（一个区间）的“价格摘要”：记录最低价格何时发生下降。
struct Summary {
    int first_price;      // 区间起点城市的价格
    int minimum_price;    // 区间内价格前缀最小值（最小值）
    int first_node;       // 区间起点的树节点
    int last_node;        // 区间终点的树节点
    vector<Group> groups; // 压缩后的 (价格, 长度) 分段列表
    vector<Prefix> prefix;// groups 的前缀长度与花费
};

// 线段树节点：同时保存正向（左到右）和反向（右到左）两套摘要。
struct SegmentNode {
    Summary forward;
    Summary backward;
};

// 查询路径时收集到的一个线段树区间：node 是节点编号，reversed 表示用反向摘要。
struct Piece {
    int node;
    bool reversed;
};

int n, m;
int price[MAXN];        // 每个城市的食物价格
int parent_node[MAXN];  // 树上的父节点
int depth[MAXN];        // 节点深度（根为 0）
int subtree_size[MAXN]; // 子树大小，用于选重儿子
int heavy_son[MAXN];    // 重儿子
int chain_top[MAXN];    // 所在重链的顶端节点
int position[MAXN];     // 节点在 dfs 序（重链优先）中的位置
int node_at[MAXN];      // position -> 节点编号
int edge_to_parent[MAXN]; // 节点到其父节点的边长
vector<Edge> graph[MAXN]; // 邻接表存树
SegmentNode segment_tree[MAXN * 4]; // 线段树
int position_count; // dfs 序分配游标

// 往 summary 的 groups 末尾追加一段 (price_value, length)，
// 若与最后一段价格相同则合并，否则新开一段。
void add_group(Summary &summary, int price_value, int length) {
    if (length == 0) return;
    if (!summary.groups.empty() && summary.groups.back().price == price_value) {
        summary.groups.back().length += length;
    } else {
        Group group = {price_value, length};
        summary.groups.push_back(group);
    }
}

// 根据 groups 重建前缀数组 prefix[i] = 前 i+1 段的总长度与总花费。
void build_prefix(Summary &summary) {
    summary.prefix.resize(summary.groups.size());
    int total_length = 0;
    long long total_cost = 0;
    for (int i = 0; i < (int)summary.groups.size(); i++) {
        total_length += summary.groups[i].length;
        total_cost += 1LL * summary.groups[i].price * summary.groups[i].length;
        summary.prefix[i] = {total_length, total_cost};
    }
}

// 合并两个相邻区间的摘要：left 在前、right 在后，
// middle_length 是连接两个区间的那条边的长度。
Summary merge_summary(const Summary &left, const Summary &right, int middle_length) {
    Summary result;
    result.first_price = left.first_price;
    result.minimum_price = min(left.minimum_price, right.minimum_price);
    result.first_node = left.first_node;
    result.last_node = right.last_node;
    result.groups = left.groups;
    // 连接边使用 left 的最小价格；left 内部的各组价格要与 right 各组取 min 后合并。
    add_group(result, left.minimum_price, middle_length);
    for (int i = 0; i < (int)right.groups.size(); i++) {
        add_group(result, min(left.minimum_price, right.groups[i].price),
                  right.groups[i].length);
    }
    build_prefix(result);
    return result;
}

// 已知进入该摘要前的最低价格 current_price，计算完整走完这段的花费。
// groups 按价格升序排列，二分找到第一个价格小于 current_price 的分段。
long long calculate_cost(const Summary &summary, int current_price) {
    int left = 0;
    int right = (int)summary.groups.size();
    while (left < right) {
        int middle = (left + right) / 2;
        if (summary.groups[middle].price >= current_price) left = middle + 1;
        else right = middle;
    }

    // 前 fixed_count 段（价格 >= current_price）改按 current_price 计费，其余段维持原价。
    int fixed_count = left;
    int fixed_length = 0;
    long long fixed_cost = 0;
    if (fixed_count > 0) {
        fixed_length = summary.prefix[fixed_count - 1].length;
        fixed_cost = summary.prefix[fixed_count - 1].cost;
    }
    long long total_cost = 0;
    if (!summary.prefix.empty()) {
        total_cost = summary.prefix.back().cost;
    }
    return 1LL * current_price * fixed_length + total_cost - fixed_cost;
}

// 迭代完成 DFS 序、子树大小、重儿子、重链划分等预处理。
void build_tree_info() {
    vector<int> order;
    vector<int> stack_nodes;
    stack_nodes.push_back(1);
    parent_node[1] = 0;
    depth[1] = 0;
    while (!stack_nodes.empty()) {
        int u = stack_nodes.back();
        stack_nodes.pop_back();
        order.push_back(u);
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i].to;
            if (v == parent_node[u]) continue;
            parent_node[v] = u;
            edge_to_parent[v] = graph[u][i].length;
            depth[v] = depth[u] + 1;
            stack_nodes.push_back(v);
        }
    }
    // 逆序处理 order，得到子树大小并选出每个节点的重儿子。
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        subtree_size[u] = 1;
        heavy_son[u] = 0;
        for (int j = 0; j < (int)graph[u].size(); j++) {
            int v = graph[u][j].to;
            if (parent_node[v] != u) continue;
            subtree_size[u] += subtree_size[v];
            if (heavy_son[u] == 0 || subtree_size[v] > subtree_size[heavy_son[u]]) {
                heavy_son[u] = v;
            }
        }
    }

    // 从每条链顶端出发，沿重儿子一路给节点分配连续的 dfs 序。
    vector<pair<int, int> > chains;
    chains.push_back(make_pair(1, 1));
    while (!chains.empty()) {
        pair<int, int> current = chains.back();
        chains.pop_back();
        int u = current.first;
        int top = current.second;
        while (u != 0) {
            chain_top[u] = top;
            position[u] = ++position_count;
            node_at[position_count] = u;
            for (int i = 0; i < (int)graph[u].size(); i++) {
                int v = graph[u][i].to;
                if (parent_node[v] == u && v != heavy_son[u]) {
                    chains.push_back(make_pair(v, v));
                }
            }
            u = heavy_son[u];
        }
    }
}

// 建线段树：叶子节点是单个节点，非叶合并左右儿子的摘要。
// 相邻节点间那条边的长度由右儿子第一个节点的 edge_to_parent 给出。
void build_segment_tree(int index, int left, int right) {
    if (left == right) {
        int u = node_at[left];
        segment_tree[index].forward.first_price = price[u];
        segment_tree[index].forward.minimum_price = price[u];
        segment_tree[index].forward.first_node = u;
        segment_tree[index].forward.last_node = u;
        segment_tree[index].backward = segment_tree[index].forward;
        return;
    }
    int middle = (left + right) / 2;
    build_segment_tree(index * 2, left, middle);
    build_segment_tree(index * 2 + 1, middle + 1, right);
    int middle_length = edge_to_parent[node_at[middle + 1]];
    segment_tree[index].forward = merge_summary(segment_tree[index * 2].forward,
                                                 segment_tree[index * 2 + 1].forward,
                                                 middle_length);
    segment_tree[index].backward = merge_summary(segment_tree[index * 2 + 1].backward,
                                                  segment_tree[index * 2].backward,
                                                  middle_length);
}

// 收集查询区间 [query_left, query_right] 覆盖的线段树节点。
// reversed 为 true 时按右子树优先的顺序收集，保证返回的 pieces 沿路径顺序排列。
void collect_segments(int index, int left, int right, int query_left, int query_right,
                      bool reversed, vector<Piece> &pieces) {
    if (query_left <= left && right <= query_right) {
        Piece piece = {index, reversed};
        pieces.push_back(piece);
        return;
    }
    int middle = (left + right) / 2;
    if (!reversed) {
        if (query_left <= middle) {
            collect_segments(index * 2, left, middle, query_left, query_right, reversed, pieces);
        }
        if (query_right > middle) {
            collect_segments(index * 2 + 1, middle + 1, right, query_left, query_right,
                             reversed, pieces);
        }
    } else {
        if (query_right > middle) {
            collect_segments(index * 2 + 1, middle + 1, right, query_left, query_right,
                             reversed, pieces);
        }
        if (query_left <= middle) {
            collect_segments(index * 2, left, middle, query_left, query_right, reversed, pieces);
        }
    }
}

// 用重链跳到相同链上，深度较浅者就是 LCA。
int find_lca(int u, int v) {
    while (chain_top[u] != chain_top[v]) {
        if (depth[chain_top[u]] > depth[chain_top[v]]) u = parent_node[chain_top[u]];
        else v = parent_node[chain_top[v]];
    }
    return depth[u] < depth[v] ? u : v;
}

// 查询从 u 到 v 的最小花费。
// 上行段（u -> LCA）按反向摘要读取，下行段（LCA -> v）按正向摘要读取。
long long query_path(int u, int v) {
    int ancestor = find_lca(u, v);
    vector<Piece> pieces;
    // 收集 u 到 LCA 的上行重链段，反向读取。
    while (chain_top[u] != chain_top[ancestor]) {
        collect_segments(1, 1, n, position[chain_top[u]], position[u], true, pieces);
        u = parent_node[chain_top[u]];
    }
    collect_segments(1, 1, n, position[ancestor], position[u], true, pieces);

    // 收集 LCA 到 v 的下行重链段，正向读取；每段内部保持祖先到子孙的顺序。
    vector<vector<Piece> > down_chunks;
    while (chain_top[v] != chain_top[ancestor]) {
        vector<Piece> current_chunk;
        collect_segments(1, 1, n, position[chain_top[v]], position[v], false, current_chunk);
        down_chunks.push_back(current_chunk);
        v = parent_node[chain_top[v]];
    }
    // LCA 自身不重复计费，从 position[ancestor]+1 开始。
    if (position[ancestor] + 1 <= position[v]) {
        vector<Piece> current_chunk;
        collect_segments(1, 1, n, position[ancestor] + 1, position[v], false, current_chunk);
        down_chunks.push_back(current_chunk);
    }
    // 下行的链段按从深到浅收集，需倒序拼接到 pieces 末尾。
    for (int i = (int)down_chunks.size() - 1; i >= 0; i--) {
        for (int j = 0; j < (int)down_chunks[i].size(); j++) {
            pieces.push_back(down_chunks[i][j]);
        }
    }

    long long answer = 0;
    int current_price = 1000000007; // 走到路径起点时还没有买过食物，取足够大的初值
    int previous_node = 0;
    for (int i = 0; i < (int)pieces.size(); i++) {
        const Summary &summary = pieces[i].reversed ? segment_tree[pieces[i].node].backward
                                                     : segment_tree[pieces[i].node].forward;
        // 相邻两块摘要之间还有一条边，用上一块结束时已有的最低价格计费。
        if (previous_node != 0) {
            int edge_length = depth[previous_node] > depth[summary.first_node]
                              ? edge_to_parent[previous_node]
                              : edge_to_parent[summary.first_node];
            answer += 1LL * current_price * edge_length;
        }
        answer += calculate_cost(summary, current_price);
        // 走完这块后，手里始终保留走过的所有城市中的最低价格。
        current_price = min(current_price, summary.minimum_price);
        previous_node = summary.last_node;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> price[i];
    for (int i = 1; i < n; i++) {
        int u, v, length;
        cin >> u >> v >> length;
        graph[u].push_back({v, length});
        graph[v].push_back({u, length});
    }
    build_tree_info();
    build_segment_tree(1, 1, n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << query_path(u, v) << '\n';
    }
    return 0;
}