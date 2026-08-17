/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int MAXM = 100000;
const int LOG = 20;

// 原树上的边
struct Edge {
    int to;
    int id;
};

// 一条旅游计划的一个路径段：段内最多只能剩一条未翻修的边
struct Segment {
    int left;     // 段的左端点（局部树节点）
    int right;    // 段的右端点（局部树节点）
    int trip;     // 属于哪条旅游计划
    int previous; // 双向链表：同一端点对(key)下的前一条记录
    int next;     // 双向链表：同一端点对(key)下的后一条记录
    unsigned long long key; // 当前端点对 (分量根, 分量根)
    bool valid;   // 该段是否已经可行
};

int n, online_x, station_count, trip_count;
vector<Edge> graph[MAXN + 1]; // 原树邻接表
int edge_u[MAXN];             // 第 i 条边的两个端点
int edge_v[MAXN];
unordered_map<unsigned long long, int> edge_id_map; // 端点对 -> 边编号
bool is_station[MAXN + 1];    // 该城市是否有维修站
vector<int> station_list;     // 维修站列表
vector<int> nonstation_list;  // 非维修站列表

// 原树的倍增 LCA 预处理数据
int parent_node[MAXN + 1];
int depth_node[MAXN + 1];
int ancestor[LOG][MAXN + 1];

// 局部树：把每条“维修站-非维修站”边复制一个边界节点，使每个路径段都有两个端点
int local_node_count;
int terminal_for_edge[MAXN];  // 每条边对应的边界节点编号
int local_edge_left[MAXN];    // 局部树的边两端（含边界节点）
int local_edge_right[MAXN];
vector<set<int> > neighbors;           // 局部树每个分量的邻接分量集合
vector<int> dsu_parent;                // 局部树并查集：已翻修边被收缩
vector<vector<int> > component_members; // 每个分量包含的局部树节点

// 路径段的记录与计数
vector<Segment> segments(1);   // 所有路径段，下标 0 为哨兵
vector<vector<int> > endpoint_segments; // 每个局部树节点关联的路径段
vector<int> bad_segment_count; // 每条计划还没可行的路径段数量
vector<int> segment_seen;      // 用于去重的一轮扫描标记
int seen_round;
long long feasible_trip_count; // 当前可行的旅游计划数量
unordered_map<unsigned long long, int> pair_head; // 端点对 -> 记录链表头

unsigned long long make_key(int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    return (unsigned long long)(unsigned int)u << 32
           | (unsigned int)v;
}

int find_root(int u) {
    if (dsu_parent[u] == u) {
        return u;
    }
    dsu_parent[u] = find_root(dsu_parent[u]);
    return dsu_parent[u];
}

void dfs_tree(int u, int parent) {
    parent_node[u] = parent;
    depth_node[u] = depth_node[parent] + 1;
    ancestor[0][u] = parent;
    for (int i = 1; i < LOG; i++) {
        ancestor[i][u] = ancestor[i - 1][ancestor[i - 1][u]];
    }
    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i].to;
        if (v == parent) {
            continue;
        }
        dfs_tree(v, u);
    }
}

int jump_up(int u, int distance) {
    for (int i = 0; i < LOG; i++) {
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
    for (int i = LOG - 1; i >= 0; i--) {
        if (ancestor[i][u] != ancestor[i][v]) {
            u = ancestor[i][u];
            v = ancestor[i][v];
        }
    }
    return parent_node[u];
}

int distance_tree(int u, int v) {
    int w = lowest_common_ancestor(u, v);
    return depth_node[u] + depth_node[v] - 2 * depth_node[w];
}

bool on_path(int x, int u, int v) {
    return distance_tree(u, x) + distance_tree(x, v) == distance_tree(u, v);
}

int next_on_path(int u, int v) {
    int w = lowest_common_ancestor(u, v);
    if (u != w) {
        return parent_node[u];
    }
    int distance = depth_node[v] - depth_node[u] - 1;
    return jump_up(v, distance);
}

int get_edge_id(int u, int v) {
    unordered_map<unsigned long long, int>::iterator it;
    it = edge_id_map.find(make_key(u, v));
    return it == edge_id_map.end() ? 0 : it->second;
}

void add_record(int id) {
    Segment &segment = segments[id];
    pair_head[segment.key];
    int head = pair_head[segment.key];
    segment.previous = 0;
    segment.next = head;
    if (head != 0) {
        segments[head].previous = id;
    }
    pair_head[segment.key] = id;
}

void remove_record(int id) {
    Segment &segment = segments[id];
    int head = pair_head[segment.key];
    if (segment.previous == 0) {
        head = segment.next;
    } else {
        segments[segment.previous].next = segment.next;
    }
    if (segment.next != 0) {
        segments[segment.next].previous = segment.previous;
    }
    if (head == 0) {
        pair_head.erase(segment.key);
    } else {
        pair_head[segment.key] = head;
    }
    segment.previous = 0;
    segment.next = 0;
}

void make_segment_valid(int id, bool already_removed) {
    if (segments[id].valid) {
        return;
    }
    if (!already_removed) {
        remove_record(id);
    }
    segments[id].valid = true;
    int trip = segments[id].trip;
    bad_segment_count[trip]--;
    if (bad_segment_count[trip] == 0) {
        feasible_trip_count++;
    }
}

void make_pair_valid(int u, int v) {
    unsigned long long key = make_key(u, v);
    unordered_map<unsigned long long, int>::iterator it = pair_head.find(key);
    if (it == pair_head.end()) {
        return;
    }
    int id = it->second;
    while (id != 0) {
        int next = segments[id].next;
        make_segment_valid(id, false);
        id = next;
    }
}

void update_moved_record(int id) {
    if (segments[id].valid) {
        return;
    }
    remove_record(id);
    int left_root = find_root(segments[id].left);
    int right_root = find_root(segments[id].right);
    if (left_root == right_root
        || neighbors[left_root].find(right_root) != neighbors[left_root].end()) {
        make_segment_valid(id, true);
        return;
    }
    segments[id].key = make_key(left_root, right_root);
    add_record(id);
}

// 一条道路被翻修：把局部树中对应的边收缩。
// 收缩会让“左分量与右分量的其它邻居”之间距离从 2 变为 1，从而激活相应端点对；
// 左分量内部的所有路径段需要重新计算所在分量并更新记录。小并大控制总代价。
void repair_local_edge(int edge_id) {
    int left_root = find_root(local_edge_left[edge_id]);
    int right_root = find_root(local_edge_right[edge_id]);
    if (left_root == right_root) {
        return;
    }
    if (component_members[left_root].size()
        > component_members[right_root].size()) {
        swap(left_root, right_root);
    }

    // 收缩后，right_root 与 left_root 的每个邻居之间距离变为 1，这些端点对全部可行。
    for (set<int>::iterator it = neighbors[left_root].begin();
         it != neighbors[left_root].end(); ++it) {
        int other = *it;
        if (other != right_root) {
            make_pair_valid(right_root, other);
        }
    }

    vector<int> old_neighbors;
    for (set<int>::iterator it = neighbors[left_root].begin();
         it != neighbors[left_root].end(); ++it) {
        old_neighbors.push_back(*it);
    }
    for (int i = 0; i < (int)old_neighbors.size(); i++) {
        int other = old_neighbors[i];
        if (other == right_root) {
            continue;
        }
        neighbors[other].erase(left_root);
        neighbors[other].insert(right_root);
        neighbors[right_root].insert(other);
    }
    neighbors[right_root].erase(left_root);
    neighbors[left_root].clear();
    dsu_parent[left_root] = right_root;

    seen_round++;
    for (int i = 0; i < (int)component_members[left_root].size(); i++) {
        int vertex = component_members[left_root][i];
        for (int j = 0; j < (int)endpoint_segments[vertex].size(); j++) {
            int id = endpoint_segments[vertex][j];
            if (segment_seen[id] == seen_round) {
                continue;
            }
            segment_seen[id] = seen_round;
            update_moved_record(id);
        }
    }
    component_members[right_root].insert(component_members[right_root].end(),
                                         component_members[left_root].begin(),
                                         component_members[left_root].end());
    component_members[left_root].clear();
}

int endpoint_local_node(int vertex, int toward, int edge_id) {
    if (!is_station[vertex]) {
        return vertex;
    }
    return terminal_for_edge[edge_id];
}

// 建局部树：每条“维修站-非维修站”边插入一个边界节点，避免维修站两侧被错误连在一起。
// 这样一条路径段的两个端点都落在局部树里，两端“同分量或相邻”就代表段内至多一条未翻修边。
void build_local_tree() {
    local_node_count = n;
    for (int i = 1; i < n; i++) {
        if (is_station[edge_u[i]] == is_station[edge_v[i]]) {
            if (!is_station[edge_u[i]]) {
                local_edge_left[i] = edge_u[i];
                local_edge_right[i] = edge_v[i];
            }
        } else {
            int station = is_station[edge_u[i]] ? edge_u[i] : edge_v[i];
            int nonstation = is_station[edge_u[i]] ? edge_v[i] : edge_u[i];
            int terminal = ++local_node_count;
            terminal_for_edge[i] = terminal;
            local_edge_left[i] = terminal;
            local_edge_right[i] = nonstation;
        }
    }

    dsu_parent.resize(local_node_count + 1);
    component_members.resize(local_node_count + 1);
    neighbors.resize(local_node_count + 1);
    endpoint_segments.resize(local_node_count + 1);
    for (int i = 1; i <= local_node_count; i++) {
        dsu_parent[i] = i;
        component_members[i].push_back(i);
    }
    for (int i = 1; i < n; i++) {
        if (local_edge_left[i] == 0) {
            continue;
        }
        neighbors[local_edge_left[i]].insert(local_edge_right[i]);
        neighbors[local_edge_right[i]].insert(local_edge_left[i]);
    }
}

// 为一条计划添加一个非平凡路径段 (a, b)，段端点都是局部树节点。
// 段尚未可行，先按当前端点所在分量建立记录，等待后续边翻修后被激活。
void add_trip_segment(int trip, int a, int b) {
    int left_root = find_root(a);
    int right_root = find_root(b);
    Segment segment;
    segment.left = a;
    segment.right = b;
    segment.trip = trip;
    segment.previous = 0;
    segment.next = 0;
    segment.key = make_key(left_root, right_root);
    segment.valid = false;
    segments.push_back(segment);
    int id = (int)segments.size() - 1;
    endpoint_segments[a].push_back(id);
    endpoint_segments[b].push_back(id);
    bad_segment_count[trip]++;
    add_record(id);
}

void add_trip_segment_by_boundary(int trip, int left, int right) {
    if (distance_tree(left, right) <= 1) {
        return;
    }
    int next_left = next_on_path(left, right);
    int next_right = next_on_path(right, left);
    int edge_left = get_edge_id(left, next_left);
    int edge_right = get_edge_id(right, next_right);
    int local_left = endpoint_local_node(left, next_left, edge_left);
    int local_right = endpoint_local_node(right, next_right, edge_right);
    add_trip_segment(trip, local_left, local_right);
}

// 把一条旅游计划沿路径拆成若干路径段。
// 维修站数量少时枚举路径上的维修站做切分；否则改为枚举非维修站的连续段，
// 两种方式取枚举代价较小的一侧。
void build_trip_segments(int trip, int start, int finish) {
    vector<pair<int, int> > points;
    points.push_back(make_pair(0, start));
    int total_distance = distance_tree(start, finish);
    if (station_list.size() <= nonstation_list.size()) {
        // 枚举路径上出现的维修站，相邻维修站之间构成一段
        for (int i = 0; i < (int)station_list.size(); i++) {
            int station = station_list[i];
            if (station == start || station == finish) {
                continue;
            }
            if (on_path(station, start, finish)) {
                points.push_back(make_pair(distance_tree(start, station), station));
            }
        }
        points.push_back(make_pair(total_distance, finish));
        sort(points.begin(), points.end());
        for (int i = 1; i < (int)points.size(); i++) {
            add_trip_segment_by_boundary(trip, points[i - 1].second,
                                         points[i].second);
        }
        return;
    }

    // 非维修站较少时，直接枚举路径上的非维修站连续段。
    points.clear();
    for (int i = 0; i < (int)nonstation_list.size(); i++) {
        int vertex = nonstation_list[i];
        if (on_path(vertex, start, finish)) {
            points.push_back(make_pair(distance_tree(start, vertex), vertex));
        }
    }
    sort(points.begin(), points.end());
    int i = 0;
    while (i < (int)points.size()) {
        int j = i;
        while (j + 1 < (int)points.size()
               && points[j + 1].first == points[j].first + 1) {
            j++;
        }
        int left = points[i].first == 0
                       ? start
                       : next_on_path(points[i].second, start);
        int right = points[j].first == total_distance
                        ? finish
                        : next_on_path(points[j].second, finish);
        add_trip_segment_by_boundary(trip, left, right);
        i = j + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> online_x;
    edge_id_map.reserve(2 * n + 10);
    for (int i = 1; i < n; i++) {
        cin >> edge_u[i] >> edge_v[i];
        graph[edge_u[i]].push_back({edge_v[i], i});
        graph[edge_v[i]].push_back({edge_u[i], i});
        edge_id_map[make_key(edge_u[i], edge_v[i])] = i;
    }
    cin >> station_count;
    station_list.resize(station_count);
    for (int i = 0; i < station_count; i++) {
        cin >> station_list[i];
        is_station[station_list[i]] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!is_station[i]) {
            nonstation_list.push_back(i);
        }
    }
    depth_node[0] = -1;
    dfs_tree(1, 0);
    build_local_tree();

    cin >> trip_count;
    bad_segment_count.assign(trip_count, 0);
    for (int i = 0; i < trip_count; i++) {
        int start, finish;
        cin >> start >> finish;
        build_trip_segments(i, start, finish);
    }
    segment_seen.assign(segments.size(), 0);
    feasible_trip_count = 0;
    for (int i = 0; i < trip_count; i++) {
        if (bad_segment_count[i] == 0) {
            feasible_trip_count++;
        }
    }

    int query_count;
    cin >> query_count;
    int last_answer = 0;
    while (query_count--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            u ^= online_x * last_answer;
            v ^= online_x * last_answer;
            int edge_id = get_edge_id(u, v);
            if (edge_id != 0) {
                repair_local_edge(edge_id);
            }
        } else {
            cout << feasible_trip_count << '\n';
            last_answer = (int)feasible_trip_count;
        }
    }
    return 0;
}
