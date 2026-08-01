/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 16:45
 */
#include <bits/stdc++.h>
using namespace std;

namespace online_easy_solver {
#define main online_easy_solver_main
#include "../CSP202603E/main.cpp"
#undef main
}

const int MAXN = 100005;
const int MAXM = 100005;
const int MAXQ = 200005;
const int LOGN = 18;
const int INF_TIME = 1000000000;

struct Edge {
    int to;
    int id;
};

struct RawOperation {
    int type;
    int u;
    int v;
};

struct GroupSummary {
    int first;
    int second;
};

// 一个序列被维修站分成若干组，每组只保留最大的两个权值。
struct PathSummary {
    int count;
    GroupSummary first;
    GroupSummary last;
    int inner_best;
    bool ends_reset;
    bool empty;
};

struct SegmentTreeNode {
    PathSummary forward;
    PathSummary backward;
};

struct Trip {
    int start;
    int finish;
};

int n, online_x;
int station_count, trip_count, query_count;
vector<Edge> graph[MAXN];
int edge_u[MAXN], edge_v[MAXN];
int edge_time[MAXN];
bool repaired[MAXN];
bool is_station[MAXN];
unordered_map<unsigned long long, int> edge_id;

int parent_node[MAXN], depth_node[MAXN], heavy_son[MAXN], subtree_size[MAXN];
int top_chain[MAXN], dfn[MAXN], reverse_dfn[MAXN], dfn_count;
int edge_to_parent[MAXN];
int ancestor[LOGN][MAXN];

vector<Trip> trips;
vector<RawOperation> operations;
vector<int> query_repair_count;
vector<int> threshold;

SegmentTreeNode segment_tree[MAXN * 4];

unsigned long long make_edge_key(int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    return (unsigned long long)(unsigned int)u << 32
           | (unsigned int)v;
}

GroupSummary make_group(int value) {
    GroupSummary result;
    result.first = value;
    result.second = 0;
    return result;
}

GroupSummary merge_group(GroupSummary a, GroupSummary b) {
    GroupSummary result;
    result.first = max(a.first, b.first);
    result.second = max(min(a.first, b.first), max(a.second, b.second));
    return result;
}

int group_score(GroupSummary group) {
    return group.second;
}

PathSummary empty_summary() {
    PathSummary result;
    result.count = 0;
    result.first = make_group(0);
    result.last = make_group(0);
    result.inner_best = 0;
    result.ends_reset = false;
    result.empty = true;
    return result;
}

PathSummary one_item_summary(int value, bool reset_after) {
    PathSummary result;
    result.count = 1;
    result.first = make_group(value);
    result.last = result.first;
    result.inner_best = 0;
    result.ends_reset = reset_after;
    result.empty = false;
    return result;
}

int capped_count(int value) {
    return min(value, 3);
}

PathSummary combine_summary(PathSummary left, PathSummary right) {
    if (left.empty) {
        return right;
    }
    if (right.empty) {
        return left;
    }

    PathSummary result;
    result.empty = false;
    result.count = capped_count(left.count + right.count);

    if (left.ends_reset) {
        // 两边之间有维修站边界，最后一组和第一组不会合并。
        result.first = left.first;
        result.last = right.last;
        result.ends_reset = right.ends_reset;
        result.inner_best = max(left.inner_best, right.inner_best);
        if (left.count >= 2) {
            result.inner_best = max(result.inner_best, group_score(left.last));
        }
        if (right.count >= 2) {
            result.inner_best = max(result.inner_best, group_score(right.first));
        }
        return result;
    }

    // 左侧最后一组与右侧第一组属于同一段。
    GroupSummary merged = merge_group(left.last, right.first);
    result.count = capped_count(left.count + right.count - 1);
    result.first = left.count == 1 ? merged : left.first;
    result.last = right.count == 1 ? merged : right.last;
    result.ends_reset = right.ends_reset;
    result.inner_best = max(left.inner_best, right.inner_best);
    if (left.count >= 2 && right.count >= 2) {
        result.inner_best = max(result.inner_best, group_score(merged));
    }
    return result;
}

int summary_answer(PathSummary summary) {
    if (summary.empty) {
        return 0;
    }
    int result = summary.inner_best;
    result = max(result, group_score(summary.first));
    if (summary.count >= 2) {
        result = max(result, group_score(summary.last));
    }
    return result;
}

void build_tree_info() {
    vector<int> order;
    order.reserve(n);
    order.push_back(1);
    parent_node[1] = 0;
    depth_node[1] = 0;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int j = 0; j < (int)graph[u].size(); j++) {
            int v = graph[u][j].to;
            if (v == parent_node[u]) {
                continue;
            }
            parent_node[v] = u;
            depth_node[v] = depth_node[u] + 1;
            edge_to_parent[v] = graph[u][j].id;
            order.push_back(v);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        subtree_size[u] = 1;
        heavy_son[u] = 0;
        for (int j = 0; j < (int)graph[u].size(); j++) {
            int v = graph[u][j].to;
            if (parent_node[v] != u) {
                continue;
            }
            subtree_size[u] += subtree_size[v];
            if (heavy_son[u] == 0
                || subtree_size[v] > subtree_size[heavy_son[u]]) {
                heavy_son[u] = v;
            }
        }
    }

    vector<pair<int, int> > stack;
    stack.push_back(make_pair(1, 1));
    while (!stack.empty()) {
        int start = stack.back().first;
        int chain_top = stack.back().second;
        stack.pop_back();
        int u = start;
        while (u != 0) {
            top_chain[u] = chain_top;
            dfn[u] = ++dfn_count;
            reverse_dfn[dfn_count] = u;
            for (int j = (int)graph[u].size() - 1; j >= 0; j--) {
                int v = graph[u][j].to;
                if (parent_node[v] == u && v != heavy_son[u]) {
                    stack.push_back(make_pair(v, v));
                }
            }
            u = heavy_son[u];
        }
    }
    for (int j = 0; j < LOGN; j++) {
        for (int u = 1; u <= n; u++) {
            if (j == 0) {
                ancestor[j][u] = parent_node[u];
            } else {
                ancestor[j][u] = ancestor[j - 1][ancestor[j - 1][u]];
            }
        }
    }
}

int jump_up(int u, int distance) {
    for (int i = 0; i < LOGN; i++) {
        if ((distance >> i) & 1) {
            u = ancestor[i][u];
        }
    }
    return u;
}

int lowest_common_ancestor(int u, int v) {
    if (depth_node[u] < depth_node[v]) {
        swap(u, v);
    }
    u = jump_up(u, depth_node[u] - depth_node[v]);
    if (u == v) {
        return u;
    }
    for (int i = LOGN - 1; i >= 0; i--) {
        if (ancestor[i][u] != ancestor[i][v]) {
            u = ancestor[i][u];
            v = ancestor[i][v];
        }
    }
    return parent_node[u];
}

void pull_segment_tree(int p) {
    segment_tree[p].forward = combine_summary(
        segment_tree[p * 2].forward, segment_tree[p * 2 + 1].forward);
    segment_tree[p].backward = combine_summary(
        segment_tree[p * 2 + 1].backward, segment_tree[p * 2].backward);
}

void build_segment_tree(int p, int l, int r) {
    if (l == r) {
        int u = reverse_dfn[l];
        if (u == 1) {
            segment_tree[p].forward = empty_summary();
            segment_tree[p].backward = empty_summary();
        } else {
            int id = edge_to_parent[u];
            segment_tree[p].forward = one_item_summary(
                edge_time[id], is_station[u]);
            segment_tree[p].backward = one_item_summary(
                edge_time[id], is_station[parent_node[u]]);
        }
        return;
    }
    int mid = (l + r) >> 1;
    build_segment_tree(p * 2, l, mid);
    build_segment_tree(p * 2 + 1, mid + 1, r);
    pull_segment_tree(p);
}

void update_segment_tree(int p, int l, int r, int position) {
    if (l == r) {
        int u = reverse_dfn[l];
        if (u == 1) {
            segment_tree[p].forward = empty_summary();
            segment_tree[p].backward = empty_summary();
        } else {
            int id = edge_to_parent[u];
            segment_tree[p].forward = one_item_summary(
                edge_time[id], is_station[u]);
            segment_tree[p].backward = one_item_summary(
                edge_time[id], is_station[parent_node[u]]);
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (position <= mid) {
        update_segment_tree(p * 2, l, mid, position);
    } else {
        update_segment_tree(p * 2 + 1, mid + 1, r, position);
    }
    pull_segment_tree(p);
}

PathSummary query_forward(int p, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {
        return empty_summary();
    }
    if (ql <= l && r <= qr) {
        return segment_tree[p].forward;
    }
    int mid = (l + r) >> 1;
    return combine_summary(query_forward(p * 2, l, mid, ql, qr),
                           query_forward(p * 2 + 1, mid + 1, r, ql, qr));
}

PathSummary query_backward(int p, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {
        return empty_summary();
    }
    if (ql <= l && r <= qr) {
        return segment_tree[p].backward;
    }
    int mid = (l + r) >> 1;
    return combine_summary(query_backward(p * 2 + 1, mid + 1, r, ql, qr),
                           query_backward(p * 2, l, mid, ql, qr));
}

PathSummary query_path(int u, int v) {
    PathSummary left = empty_summary();
    PathSummary right = empty_summary();
    while (top_chain[u] != top_chain[v]) {
        if (depth_node[top_chain[u]] >= depth_node[top_chain[v]]) {
            PathSummary part = query_backward(1, 1, n,
                                               dfn[top_chain[u]], dfn[u]);
            left = combine_summary(left, part);
            u = parent_node[top_chain[u]];
        } else {
            PathSummary part = query_forward(1, 1, n,
                                              dfn[top_chain[v]], dfn[v]);
            right = combine_summary(part, right);
            v = parent_node[top_chain[v]];
        }
    }
    if (u != v) {
        if (depth_node[u] >= depth_node[v]) {
            PathSummary part = query_backward(1, 1, n,
                                               dfn[v] + 1, dfn[u]);
            left = combine_summary(left, part);
        } else {
            PathSummary part = query_forward(1, 1, n,
                                              dfn[u] + 1, dfn[v]);
            right = combine_summary(part, right);
        }
    }
    return combine_summary(left, right);
}

int decode_edge(int raw_u, int raw_v, int previous_answer) {
    int u = raw_u ^ (online_x * previous_answer);
    int v = raw_v ^ (online_x * previous_answer);
    unordered_map<unsigned long long, int>::iterator it;
    it = edge_id.find(make_edge_key(u, v));
    if (it == edge_id.end()) {
        return 0;
    }
    return it->second;
}

void compute_thresholds() {
    build_segment_tree(1, 1, n);
    threshold.assign(trip_count, 0);
    for (int i = 0; i < trip_count; i++) {
        threshold[i] = summary_answer(query_path(trips[i].start,
                                                  trips[i].finish));
    }
}

int run_hard_x0() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> online_x;
    edge_id.reserve(2 * n + 10);
    for (int i = 1; i < n; i++) {
        cin >> edge_u[i] >> edge_v[i];
        graph[edge_u[i]].push_back({edge_v[i], i});
        graph[edge_v[i]].push_back({edge_u[i], i});
        edge_id[make_edge_key(edge_u[i], edge_v[i])] = i;
    }
    cin >> station_count;
    for (int i = 0; i < station_count; i++) {
        int u;
        cin >> u;
        is_station[u] = true;
    }
    cin >> trip_count;
    trips.resize(trip_count);
    for (int i = 0; i < trip_count; i++) {
        cin >> trips[i].start >> trips[i].finish;
    }
    cin >> query_count;
    operations.resize(query_count);
    for (int i = 0; i < query_count; i++) {
        cin >> operations[i].type;
        operations[i].u = operations[i].v = 0;
        if (operations[i].type == 1) {
            cin >> operations[i].u >> operations[i].v;
        }
    }

    // X=0 时可以先恢复所有翻修时刻，再离线计算每个计划的完成时刻。
    int repair_count = 0;
    query_repair_count.assign(query_count, -1);
    for (int i = 0; i < query_count; i++) {
        if (operations[i].type == 1) {
            int id = decode_edge(operations[i].u, operations[i].v, 0);
            if (id != 0 && !repaired[id]) {
                repaired[id] = true;
                edge_time[id] = ++repair_count;
            }
        } else {
            query_repair_count[i] = repair_count;
        }
    }

    for (int i = 1; i < n; i++) {
        if (!repaired[i]) {
            edge_time[i] = INF_TIME;
        }
    }
    build_tree_info();
    compute_thresholds();

    vector<int> answer_count(repair_count + 1, 0);
    for (int i = 0; i < trip_count; i++) {
        if (threshold[i] <= repair_count) {
            answer_count[threshold[i]]++;
        }
    }
    for (int i = 1; i <= repair_count; i++) {
        answer_count[i] += answer_count[i - 1];
    }
    for (int i = 0; i < query_count; i++) {
        if (operations[i].type == 2) {
            int answer = answer_count[query_repair_count[i]];
            cout << answer << '\n';
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input((istreambuf_iterator<char>(cin)),
                 istreambuf_iterator<char>());
    istringstream input_stream(input);
    int input_n, input_x;
    input_stream >> input_n >> input_x;
    input_stream.clear();
    input_stream.seekg(0);
    cin.rdbuf(input_stream.rdbuf());

    if (input_x == 1) {
        return online_easy_solver::online_easy_solver_main();
    }
    return run_hard_x0();
}
