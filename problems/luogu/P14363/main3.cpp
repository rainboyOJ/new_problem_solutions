/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-14 23:42
 * update_at: 2026-10-16 19:41
 */
// main3.cpp：map 精确分组差异核心，每组普通插入左右 Trie。
// 与 main.cpp 使用相同的分组和建树方式，计数改用 DFS 序矩形与二维扫描线。
//
// 【匹配条件】规则 s1=P+A+S、s2=P+B+S，询问 t1=X+C+Y、t2=X+D+Y。
// 规则可用 ⟺ (A,B)=(C,D)，P 是 X 的后缀，S 是 Y 的前缀。
// 组内把反转的 P、X 插入左 Trie，把正向的 S、Y 插入右 Trie。
// 规则左终点是询问左终点的祖先，且规则右终点是询问右终点的祖先，才合法。
//
// 【矩形与点】DFS 序把节点 u 的子树变成区间 [tin[u],tout[u]]。
// 规则的左右终点为 u、v，就生成矩形：
//   [tin[u],tout[u]] × [tin[v],tout[v]]。
// 询问的左右终点为 x、y，就生成点 (tin[x],tin[y])。
// 答案就是本组内覆盖询问点的规则矩形数，重复规则分别计数。
//
// 【扫描线】矩形在 x=tin[u] 时给 y 区间加 1，在 x=tout[u]+1 时减 1。
// 按 x 排序，同坐标先更新后查询；树状数组维护 y 方向的差分，单点查覆盖数。
// 时间 O((L1+L2) log(L1+L2))，空间 O(L1+L2)（固定 26 字母表）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXGROUP = 200000 + 10; // 核心组数不超过规则数 n
const int MAXNODE = 5000000 + 10; // 规则与有效询问的单侧总长度至多 5000000，另有两个根

// 普通 Trie；节点编号与 DFS 序至多 5000002，用 int 控制内存。
struct Node {
    int ch[26];
    int tin, tout; // 该节点子树的 DFS 序闭区间
};

struct Record {
    string a; // 两侧不变，只保留原串，目标串只用于找差异核心
    int l, r; // 首尾差异位置，0-based
    int left, right; // 本条记录在左右 Trie 中的终点
    int query_id; // 规则为 0，询问为原始询问编号
};

struct Event {
    int x;
    int y1, y2; // 更新区间 [y1,y2]；查询点时 y1==y2
    int value; // 更新为 +1 或 -1，查询为 0
    int query_id; // 更新为 0，查询为原始询问编号
};

Node node[MAXNODE];
vector<int> group_records[MAXGROUP]; // group_records[g]：属于第 g 个核心组的记录编号
bool has_query[MAXGROUP]; // has_query[g]：第 g 组是否包含询问
ll bit[MAXNODE]; // 右 Trie 的 DFS 序上维护差分数组
int node_cnt, group_cnt, dfs_timer, right_size;
ll n, q;
map<pair<string, string>, int> core_id;
vector<Record> records(1); // 完整记录从编号 1 开始保存
vector<Event> events; // 当前核心组的矩形更新与点查询
vector<ll> answer; // answer[id]：第 id 个询问的答案

int new_node() {
    node_cnt++;
    // 组间复用节点池，清空旧孩子和 DFS 序。
    for (int c = 0; c < 26; c++) node[node_cnt].ch[c] = 0;
    node[node_cnt].tin = node[node_cnt].tout = 0;
    return node_cnt;
}

int get_child(int u, int ch) {
    if (node[u].ch[ch] == 0) node[u].ch[ch] = new_node();
    return node[u].ch[ch];
}

// 与主解相同：按差异核心分组，保存规则与有效询问。
void read_record(int query_id) {
    string a, b;
    cin >> a >> b;
    if (a.size() != b.size()) return;
    int l = -1, r = -1;
    ll len = a.size();
    for (ll i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            if (l == -1) l = i;
            r = i;
        }
    }
    if (l == -1) return; // 恒等规则不能得到题目要求的不同目标串

    pair<string, string> key(a.substr(l, r - l + 1), b.substr(l, r - l + 1));
    auto it = core_id.find(key);
    int g;
    if (it == core_id.end()) {
        if (query_id != 0) return; // 规则中没有这个核心，询问答案为 0
        g = ++group_cnt;
        core_id[key] = g;
    } else {
        g = it->second;
    }
    if (query_id != 0) has_query[g] = true;

    Record current;
    current.a = move(a);
    current.l = l;
    current.r = r;
    current.left = current.right = 0;
    current.query_id = query_id;
    records.push_back(move(current));
    int record_id = records.size() - 1;
    group_records[g].push_back(record_id);
}

// 与主解相同：规则和询问一起插入，左侧反转、右侧正向，空侧对应根。
// 矩形计数需要同时记住每条记录的左右终点。
void build_group(int g, int left_root, int right_root) {
    for (auto record_id : group_records[g]) {
        int u = left_root;
        for (ll i = records[record_id].l - 1; i >= 0; i--) {
            u = get_child(u, records[record_id].a[i] - 'a');
        }
        records[record_id].left = u;

        u = right_root;
        ll len = records[record_id].a.size();
        for (ll i = records[record_id].r + 1; i < len; i++) {
            u = get_child(u, records[record_id].a[i] - 'a');
        }
        records[record_id].right = u;
    }
}

// 进入时编号，访问完所有孩子后记录子树右端点。
void dfs_order(int u) {
    node[u].tin = ++dfs_timer;
    for (int c = 0; c < 26; c++) {
        int v = node[u].ch[c];
        if (v != 0) dfs_order(v);
    }
    node[u].tout = dfs_timer;
}

// 每条规则生成矩形的两个更新事件，每个询问生成一个点查询。
void make_events(int g) {
    events.clear();
    for (auto record_id : group_records[g]) {
        int u = records[record_id].left;
        int v = records[record_id].right;
        Event event;
        event.x = node[u].tin;
        event.y1 = node[v].tin;
        event.y2 = node[v].tout;
        event.value = 1;
        event.query_id = records[record_id].query_id;
        if (event.query_id == 0) {
            events.push_back(event); // x=tin[u]，矩形开始覆盖
            event.x = node[u].tout + 1;
            event.value = -1;
            events.push_back(event); // x=tout[u]+1，矩形结束覆盖
        } else {
            event.y2 = event.y1;
            event.value = 0;
            events.push_back(event);
        }
    }
}

// 同一横坐标先处理全部更新，再回答询问，保证矩形边界是闭区间。
bool cmp_event(const Event &a, const Event &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.query_id < b.query_id;
}

void bit_add(int pos, ll value) {
    for (; pos <= right_size; pos += pos & -pos) bit[pos] += value;
}

ll bit_query(int pos) {
    ll result = 0;
    for (; pos > 0; pos -= pos & -pos) result += bit[pos];
    return result;
}

// 差分数组在左端加、右端后一位减，前缀和就是该位置的覆盖数。
void bit_range_add(int l, int r, ll value) {
    bit_add(l, value);
    bit_add(r + 1, -value);
}

void solve_events() {
    // 每组只清空本组右 Trie 用到的坐标，互不影响，总清理量受总长度控制。
    fill(bit + 1, bit + right_size + 1, 0);
    sort(events.begin(), events.end(), cmp_event);
    for (const auto &event : events) {
        if (event.query_id == 0) {
            bit_range_add(event.y1, event.y2, event.value);
        } else {
            answer[event.query_id] = bit_query(event.y1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    records.reserve(n + q + 1);
    events.reserve(2 * n + q);
    answer.assign(q + 1, 0);
    for (ll i = 1; i <= n; i++) read_record(0);
    for (ll i = 1; i <= q; i++) read_record(i);
    core_id.clear();

    for (int g = 1; g <= group_cnt; g++) {
        if (!has_query[g]) continue;
        node_cnt = 0;
        int left_root = new_node();
        int right_root = new_node();
        build_group(g, left_root, right_root);

        // 两棵树分别从 1 编号，构成独立的横、纵坐标。
        dfs_timer = 0;
        dfs_order(left_root);
        dfs_timer = 0;
        dfs_order(right_root);
        right_size = dfs_timer;
        make_events(g);
        solve_events();
    }
    for (ll i = 1; i <= q; i++) cout << answer[i] << '\n';
    return 0;
}
