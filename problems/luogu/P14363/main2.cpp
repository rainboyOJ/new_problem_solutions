/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-14 23:42
 * update_at: 2026-10-14 23:42
 */
// main2.cpp：差异核心精确分组 + 左右普通 Trie + 二维扫描线。
// 无需 AC 自动机；规则产生矩形，询问产生点，统计同核心的矩形覆盖数。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXNODE = 2500000 + 10; // 两棵 Trie 合计不超过规则单侧总长度 + 2
const int MAXRULE = 200000 + 5;

struct Node {
    int head;
    int tin, tout;
};

struct Edge {
    int ch, to, nxt;
};

struct Rule {
    int core;
    int left, right; // 规则两侧字符串在对应 Trie 中的终点
};

struct Frame {
    int u, edge; // 显式 DFS 栈，edge 是尚未访问的下一条边
};

struct Event {
    // 节点、坐标、规则编号均不超过 2500002，用 int 控制大数组内存。
    int core, x;
    int y1, y2;
    int value; // 矩形进入 +1、退出 -1；查询为 0
    int id;    // 更新为 0，查询为原询问编号
};

Node node[MAXNODE];
Edge edge[MAXNODE];
Rule rule[MAXRULE];
ll bit[MAXNODE];
int node_cnt, edge_cnt;
int left_root, right_root, right_size;
ll n, q;
vector<Frame> dfs_stack;
vector<Event> events;
vector<ll> answer;
map<pair<string, string>, int> core_id; // 精确存储核心左右串，不使用哈希
int core_cnt;

int new_node() {
    node_cnt++;
    node[node_cnt].head = 0;
    node[node_cnt].tin = node[node_cnt].tout = 0;
    return node_cnt;
}

int find_child(int u, int ch) {
    for (int e = node[u].head; e != 0; e = edge[e].nxt) {
        if (edge[e].ch == ch) return edge[e].to;
    }
    return 0;
}

int get_child(int u, int ch) {
    int v = find_child(u, ch);
    if (v != 0) return v;
    v = new_node();
    edge_cnt++;
    edge[edge_cnt].ch = ch;
    edge[edge_cnt].to = v;
    edge[edge_cnt].nxt = node[u].head;
    node[u].head = edge_cnt;
    return v;
}

void find_diff(const string &a, const string &b, ll &L, ll &R) {
    L = R = -1;
    ll len = a.size();
    for (ll i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            if (L == -1) L = i;
            R = i;
        }
    }
}

void read_rules() {
    for (ll i = 1; i <= n; i++) {
        string a, b;
        cin >> a >> b;
        ll L, R;
        find_diff(a, b, L, R);
        if (L == -1) continue; // 恒等规则不能把原串变成不同的目标串

        pair<string, string> key(a.substr(L, R - L + 1), b.substr(L, R - L + 1));
        auto it = core_id.find(key);
        if (it == core_id.end()) {
            core_cnt++;
            core_id[key] = core_cnt;
            rule[i].core = core_cnt;
        } else {
            rule[i].core = it->second;
        }

        // 左侧反转后插入，右侧正向插入；空串对应根。
        int u = left_root;
        for (ll j = L - 1; j >= 0; j--) u = get_child(u, a[j] - 'a');
        rule[i].left = u;
        u = right_root;
        ll len = a.size();
        for (ll j = R + 1; j < len; j++) u = get_child(u, a[j] - 'a');
        rule[i].right = u;
    }
}

int build_dfs_order(int root) {
    int timer = 0;
    dfs_stack.clear();
    node[root].tin = ++timer;
    dfs_stack.push_back({root, node[root].head});
    while (!dfs_stack.empty()) {
        int u = dfs_stack.back().u;
        int e = dfs_stack.back().edge;
        if (e == 0) {
            node[u].tout = timer;
            dfs_stack.pop_back();
        } else {
            dfs_stack.back().edge = edge[e].nxt;
            int v = edge[e].to;
            node[v].tin = ++timer;
            dfs_stack.push_back({v, node[v].head});
        }
    }
    return timer;
}

void make_rectangles() {
    for (ll i = 1; i <= n; i++) {
        if (rule[i].core == 0) continue;
        int u = rule[i].left, v = rule[i].right;
        Event event;
        event.core = rule[i].core;
        event.x = node[u].tin;
        event.y1 = node[v].tin;
        event.y2 = node[v].tout;
        event.value = 1;
        event.id = 0;
        events.push_back(event);
        event.x = node[u].tout + 1;
        event.value = -1;
        events.push_back(event);
    }
}

void read_queries() {
    for (ll id = 1; id <= q; id++) {
        string a, b;
        cin >> a >> b;
        if (a.size() != b.size()) continue;
        ll L, R;
        find_diff(a, b, L, R);
        if (L == -1) continue; // 题目保证询问的两串不同

        pair<string, string> key(a.substr(L, R - L + 1), b.substr(L, R - L + 1));
        auto it = core_id.find(key);
        if (it == core_id.end()) continue;

        // 不新增节点，也不回跳：遇到缺边就停止，保留所有已匹配的前缀。
        int u = left_root;
        for (ll j = L - 1; j >= 0; j--) {
            int v = find_child(u, a[j] - 'a');
            if (v == 0) break;
            u = v;
        }
        int v = right_root;
        ll len = a.size();
        for (ll j = R + 1; j < len; j++) {
            int w = find_child(v, a[j] - 'a');
            if (w == 0) break;
            v = w;
        }
        Event event;
        event.core = it->second;
        event.x = node[u].tin;
        event.y1 = event.y2 = node[v].tin;
        event.value = 0;
        event.id = id;
        events.push_back(event);
    }
}

bool cmp_event(const Event &a, const Event &b) {
    if (a.core != b.core) return a.core < b.core;
    if (a.x != b.x) return a.x < b.x;
    return a.id < b.id; // 同坐标先更新后查询，包含左边界、排除 tout+1
}

void bit_add(int pos, ll value) {
    for (; pos <= right_size; pos += pos & -pos) bit[pos] += value;
}

ll bit_query(int pos) {
    ll result = 0;
    for (; pos > 0; pos -= pos & -pos) result += bit[pos];
    return result;
}

void solve_events() {
    sort(events.begin(), events.end(), cmp_event);
    for (size_t i = 0; i < events.size(); i++) {
        const Event &event = events[i];
        if (event.id == 0) {
            bit_add(event.y1, event.value);
            bit_add(event.y2 + 1, -event.value);
        } else {
            answer[event.id] = bit_query(event.y1);
        }
        // 每个核心组的所有进入、退出事件都处理完后，树状数组自然恢复为 0。
        // 必须保留最后一个查询之后的退出事件，才能安全地进入下一组。
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    left_root = new_node();
    right_root = new_node();
    events.reserve(2 * n + q);
    answer.assign(q + 1, 0);
    read_rules();
    build_dfs_order(left_root);
    right_size = build_dfs_order(right_root);
    vector<Frame>().swap(dfs_stack); // DFS 已结束，释放长链栈的容量
    make_rectangles();
    read_queries();
    solve_events();
    for (ll i = 1; i <= q; i++) cout << answer[i] << '\n';
    return 0;
}
