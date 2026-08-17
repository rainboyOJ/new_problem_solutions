/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
    int x1, x2, y1, y2, value;
};

// 线段树节点保存所有落在该 x 子区间内的左下角点，并按 y 排序。
struct PointNode {
    vector<pair<int, int> > points;
    vector<int> rmq;
};

vector<PointNode> point_tree;
vector<vector<pair<int, int> > > point_by_x;
vector<int> logarithm_table;

void build_point_rmq(int node) {
    int length = (int)point_tree[node].points.size();
    if (length == 0) return;
    int level_count = logarithm_table[length] + 1;
    point_tree[node].rmq.assign(length * level_count, 0);
    for (int i = 0; i < length; i++) {
        point_tree[node].rmq[i] = point_tree[node].points[i].second;
    }
    for (int level = 1; level < level_count; level++) {
        int step = 1 << level;
        int half = step >> 1;
        int offset = level * length;
        int previous_offset = (level - 1) * length;
        for (int i = 0; i + step <= length; i++) {
            point_tree[node].rmq[offset + i] = max(point_tree[node].rmq[previous_offset + i],
                                                    point_tree[node].rmq[previous_offset + i + half]);
        }
    }
}

void build_point_tree(int node, int left, int right) {
    if (left == right) {
        point_tree[node].points = point_by_x[left];
        sort(point_tree[node].points.begin(), point_tree[node].points.end());
        build_point_rmq(node);
        return;
    }
    int middle = (left + right) >> 1;
    build_point_tree(node << 1, left, middle);
    build_point_tree(node << 1 | 1, middle + 1, right);
    vector<pair<int, int> > &first = point_tree[node << 1].points;
    vector<pair<int, int> > &second = point_tree[node << 1 | 1].points;
    point_tree[node].points.reserve(first.size() + second.size());
    merge(first.begin(), first.end(), second.begin(), second.end(),
          back_inserter(point_tree[node].points));
    build_point_rmq(node);
}

int query_point_node(int node, int y1, int y2) {
    vector<pair<int, int> > &points = point_tree[node].points;
    if (points.empty()) return 0;
    int left = lower_bound(points.begin(), points.end(), make_pair(y1, -1)) - points.begin();
    int right = upper_bound(points.begin(), points.end(), make_pair(y2, INT_MAX)) - points.begin() - 1;
    if (left > right) return 0;
    int length = right - left + 1;
    int level = logarithm_table[length];
    int offset = level * (int)points.size();
    int step = 1 << level;
    return max(point_tree[node].rmq[offset + left], point_tree[node].rmq[offset + right - step + 1]);
}

int query_point_rectangle(int node, int left, int right, int query_left, int query_right,
                          int y1, int y2) {
    if (query_right < left || right < query_left) return 0;
    if (query_left <= left && right <= query_right) return query_point_node(node, y1, y2);
    int middle = (left + right) >> 1;
    return max(query_point_rectangle(node << 1, left, middle, query_left, query_right, y1, y2),
               query_point_rectangle(node << 1 | 1, middle + 1, right, query_left, query_right, y1, y2));
}

struct CoverUpdate {
    int point, left, right, value;
};

struct CoverQuery {
    int left, right, point, id;
};

struct HeapItem {
    int value, id;

    bool operator<(const HeapItem &other) const {
        if (value != other.value) return value < other.value;
        return id > other.id;
    }
};

struct SweepEvent {
    int coordinate, type, id;
};

bool sweep_event_less(const SweepEvent &first, const SweepEvent &second) {
    if (first.coordinate != second.coordinate) return first.coordinate < second.coordinate;
    return first.type < second.type;
}

vector<priority_queue<HeapItem> > cover_heap;
vector<char> cover_active;
vector<int> cover_segment;
int cover_limit;

void cover_clean(int point) {
    while (!cover_heap[point].empty() && !cover_active[cover_heap[point].top().id]) {
        cover_heap[point].pop();
    }
}

void cover_point_update(int node, int left, int right, int position, int value) {
    if (left == right) {
        cover_segment[node] = value;
        return;
    }
    int middle = (left + right) >> 1;
    if (position <= middle) cover_point_update(node << 1, left, middle, position, value);
    else cover_point_update(node << 1 | 1, middle + 1, right, position, value);
    cover_segment[node] = max(cover_segment[node << 1], cover_segment[node << 1 | 1]);
}

int cover_range_query(int node, int left, int right, int query_left, int query_right) {
    if (query_right < left || right < query_left) return 0;
    if (query_left <= left && right <= query_right) return cover_segment[node];
    int middle = (left + right) >> 1;
    return max(cover_range_query(node << 1, left, middle, query_left, query_right),
               cover_range_query(node << 1 | 1, middle + 1, right, query_left, query_right));
}

void solve_point_interval_cover(const vector<CoverUpdate> &updates,
                                const vector<CoverQuery> &queries, int limit, vector<int> &answer) {
    cover_limit = limit;
    cover_heap.clear();
    cover_heap.resize(limit + 1);
    cover_active.assign(updates.size(), 0);
    cover_segment.assign(4 * limit + 5, 0);
    vector<SweepEvent> events;
    events.reserve(updates.size() * 2 + queries.size());
    for (int i = 0; i < (int)updates.size(); i++) {
        events.push_back({updates[i].left, 1, i});
        events.push_back({updates[i].right + 1, 0, i});
    }
    for (int i = 0; i < (int)queries.size(); i++) events.push_back({queries[i].point, 2, i});
    sort(events.begin(), events.end(), sweep_event_less);
    // 扫描区间的左、右端点，在线段树中维护每个点坐标上的最大权值。
    for (int i = 0; i < (int)events.size(); i++) {
        SweepEvent event = events[i];
        if (event.type == 1) {
            cover_active[event.id] = 1;
            cover_heap[updates[event.id].point].push({updates[event.id].value, event.id});
            int point = updates[event.id].point;
            cover_clean(point);
            cover_point_update(1, 1, cover_limit, point, cover_heap[point].top().value);
        } else if (event.type == 0) {
            cover_active[event.id] = 0;
            int point = updates[event.id].point;
            cover_clean(point);
            int value = cover_heap[point].empty() ? 0 : cover_heap[point].top().value;
            cover_point_update(1, 1, cover_limit, point, value);
        } else {
            int value = cover_range_query(1, 1, cover_limit,
                                          queries[event.id].left, queries[event.id].right);
            answer[queries[event.id].id] = max(answer[queries[event.id].id], value);
        }
    }
}

vector<priority_queue<HeapItem> > stabbing_heap;
vector<char> stabbing_active;
int stabbing_limit;

void add_stabbing_interval(int node, int left, int right, int query_left, int query_right,
                           int value, int id) {
    if (query_right < left || right < query_left) return;
    if (query_left <= left && right <= query_right) {
        stabbing_heap[node].push({value, id});
        return;
    }
    int middle = (left + right) >> 1;
    add_stabbing_interval(node << 1, left, middle, query_left, query_right, value, id);
    add_stabbing_interval(node << 1 | 1, middle + 1, right, query_left, query_right, value, id);
}

int query_stabbing_point(int node, int left, int right, int position) {
    while (!stabbing_heap[node].empty() && !stabbing_active[stabbing_heap[node].top().id]) {
        stabbing_heap[node].pop();
    }
    int result = stabbing_heap[node].empty() ? 0 : stabbing_heap[node].top().value;
    if (left == right) return result;
    int middle = (left + right) >> 1;
    if (position <= middle) return max(result, query_stabbing_point(node << 1, left, middle, position));
    return max(result, query_stabbing_point(node << 1 | 1, middle + 1, right, position));
}

void solve_rectangle_stabbing(const vector<Rectangle> &updates, const vector<Rectangle> &queries,
                              int limit, vector<int> &answer) {
    stabbing_limit = limit;
    stabbing_heap.clear();
    stabbing_heap.resize(4 * limit + 5);
    stabbing_active.assign(updates.size(), 0);
    vector<SweepEvent> events;
    events.reserve(updates.size() * 2 + queries.size());
    for (int i = 0; i < (int)updates.size(); i++) {
        events.push_back({updates[i].x1, 1, i});
        events.push_back({updates[i].x2 + 1, 0, i});
    }
    for (int i = 0; i < (int)queries.size(); i++) events.push_back({queries[i].x1, 2, i});
    sort(events.begin(), events.end(), sweep_event_less);
    // 扫描修改矩形的 x 区间，在线段树节点堆中保存覆盖的 y 区间。
    for (int i = 0; i < (int)events.size(); i++) {
        SweepEvent event = events[i];
        if (event.type == 1) {
            stabbing_active[event.id] = 1;
            add_stabbing_interval(1, 1, stabbing_limit, updates[event.id].y1,
                                  updates[event.id].y2, updates[event.id].value, event.id);
        } else if (event.type == 0) {
            stabbing_active[event.id] = 0;
        } else {
            int value = query_stabbing_point(1, 1, stabbing_limit, queries[event.id].y1);
            answer[event.id] = max(answer[event.id], value);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dimension, query_count;
    cin >> dimension >> query_count;
    vector<Rectangle> updates(dimension);
    for (int i = 0; i < dimension; i++) {
        cin >> updates[i].x1 >> updates[i].x2 >> updates[i].y1 >> updates[i].y2 >> updates[i].value;
    }
    vector<Rectangle> queries(query_count);
    for (int i = 0; i < query_count; i++) {
        cin >> queries[i].x1 >> queries[i].x2 >> queries[i].y1 >> queries[i].y2;
        queries[i].value = 0;
    }

    vector<int> answer(query_count, 0);

    // 情形一：修改矩形左下角落在查询矩形内。
    point_by_x.assign(dimension + 1, vector<pair<int, int> >());
    for (int i = 0; i < dimension; i++) {
        point_by_x[updates[i].x1].push_back(make_pair(updates[i].y1, updates[i].value));
    }
    logarithm_table.assign(dimension + 1, 0);
    for (int i = 2; i <= dimension; i++) logarithm_table[i] = logarithm_table[i >> 1] + 1;
    point_tree.assign(4 * dimension + 5, PointNode());
    build_point_tree(1, 1, dimension);
    for (int i = 0; i < query_count; i++) {
        answer[i] = max(answer[i], query_point_rectangle(1, 1, dimension,
                                                           queries[i].x1, queries[i].x2,
                                                           queries[i].y1, queries[i].y2));
    }
    point_tree.clear();
    point_by_x.clear();

    vector<CoverUpdate> cover_updates(dimension);
    vector<CoverQuery> cover_queries(query_count);

    // 情形二：修改矩形左下角的 x 在查询范围内，修改 y 区间覆盖查询 y1。
    // 情形三：交换 x、y 后执行同样的算法。
    for (int i = 0; i < dimension; i++) {
        cover_updates[i] = {updates[i].x1, updates[i].y1, updates[i].y2, updates[i].value};
    }
    for (int i = 0; i < query_count; i++) {
        cover_queries[i] = {queries[i].x1, queries[i].x2, queries[i].y1, i};
    }
    solve_point_interval_cover(cover_updates, cover_queries, dimension, answer);

    for (int i = 0; i < dimension; i++) {
        cover_updates[i] = {updates[i].y1, updates[i].x1, updates[i].x2, updates[i].value};
    }
    for (int i = 0; i < query_count; i++) {
        cover_queries[i] = {queries[i].y1, queries[i].y2, queries[i].x1, i};
    }
    solve_point_interval_cover(cover_updates, cover_queries, dimension, answer);

    // 情形四：修改矩形覆盖查询矩形的左下角。
    solve_rectangle_stabbing(updates, queries, dimension, answer);
    for (int i = 0; i < query_count; i++) cout << answer[i] << '\n';
    return 0;
}
