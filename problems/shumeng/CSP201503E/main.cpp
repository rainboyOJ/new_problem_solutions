/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:18
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Edge {
    int to;
    int length;
};

struct Group {
    int price;
    int length;
};

struct Prefix {
    int length;
    long long cost;
};

struct Summary {
    int first_price;
    int minimum_price;
    int first_node;
    int last_node;
    vector<Group> groups;
    vector<Prefix> prefix;
};

struct SegmentNode {
    Summary forward;
    Summary backward;
};

struct Piece {
    int node;
    bool reversed;
};

int n, m;
int price[MAXN], parent_node[MAXN], depth[MAXN], subtree_size[MAXN];
int heavy_son[MAXN], chain_top[MAXN], position[MAXN], node_at[MAXN];
int edge_to_parent[MAXN];
vector<Edge> graph[MAXN];
SegmentNode segment_tree[MAXN * 4];
int position_count;

void add_group(Summary &summary, int price_value, int length) {
    if (length == 0) return;
    if (!summary.groups.empty() && summary.groups.back().price == price_value) {
        summary.groups.back().length += length;
    } else {
        Group group = {price_value, length};
        summary.groups.push_back(group);
    }
}

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

Summary merge_summary(const Summary &left, const Summary &right, int middle_length) {
    Summary result;
    result.first_price = left.first_price;
    result.minimum_price = min(left.minimum_price, right.minimum_price);
    result.first_node = left.first_node;
    result.last_node = right.last_node;
    result.groups = left.groups;
    add_group(result, left.minimum_price, middle_length);
    for (int i = 0; i < (int)right.groups.size(); i++) {
        add_group(result, min(left.minimum_price, right.groups[i].price),
                  right.groups[i].length);
    }
    build_prefix(result);
    return result;
}

long long calculate_cost(const Summary &summary, int current_price) {
    int left = 0;
    int right = (int)summary.groups.size();
    while (left < right) {
        int middle = (left + right) / 2;
        if (summary.groups[middle].price >= current_price) left = middle + 1;
        else right = middle;
    }

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

int find_lca(int u, int v) {
    while (chain_top[u] != chain_top[v]) {
        if (depth[chain_top[u]] > depth[chain_top[v]]) u = parent_node[chain_top[u]];
        else v = parent_node[chain_top[v]];
    }
    return depth[u] < depth[v] ? u : v;
}

long long query_path(int u, int v) {
    int ancestor = find_lca(u, v);
    vector<Piece> pieces;
    while (chain_top[u] != chain_top[ancestor]) {
        collect_segments(1, 1, n, position[chain_top[u]], position[u], true, pieces);
        u = parent_node[chain_top[u]];
    }
    collect_segments(1, 1, n, position[ancestor], position[u], true, pieces);

    vector<vector<Piece> > down_chunks;
    while (chain_top[v] != chain_top[ancestor]) {
        vector<Piece> current_chunk;
        collect_segments(1, 1, n, position[chain_top[v]], position[v], false, current_chunk);
        down_chunks.push_back(current_chunk);
        v = parent_node[chain_top[v]];
    }
    if (position[ancestor] + 1 <= position[v]) {
        vector<Piece> current_chunk;
        collect_segments(1, 1, n, position[ancestor] + 1, position[v], false, current_chunk);
        down_chunks.push_back(current_chunk);
    }
    for (int i = (int)down_chunks.size() - 1; i >= 0; i--) {
        for (int j = 0; j < (int)down_chunks[i].size(); j++) {
            pieces.push_back(down_chunks[i][j]);
        }
    }

    long long answer = 0;
    int current_price = 1000000007;
    int previous_node = 0;
    for (int i = 0; i < (int)pieces.size(); i++) {
        const Summary &summary = pieces[i].reversed ? segment_tree[pieces[i].node].backward
                                                     : segment_tree[pieces[i].node].forward;
        if (previous_node != 0) {
            int edge_length = depth[previous_node] > depth[summary.first_node]
                              ? edge_to_parent[previous_node]
                              : edge_to_parent[summary.first_node];
            answer += 1LL * current_price * edge_length;
        }
        answer += calculate_cost(summary, current_price);
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
