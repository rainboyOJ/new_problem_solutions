/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-14 23:42
 * update_at: 2026-10-15 11:26
 */
// main3.cpp：差异核心精确分组 + 左右普通 Trie + 二维扫描线。
// 无需 AC 自动机；规则产生矩形，询问产生点，统计同核心的矩形覆盖数。
//
// ==================== 教学导读 ====================
// 【充要条件回顾】规则 s1 = P+A+S、s2 = P+B+S，询问 t1 = X+C+Y、t2 = X+D+Y。
// 规则可用 ⟺ (A,B) = (C,D) 且 P 是 X 的后缀且 S 是 Y 的前缀。
// 先按差异核心 (A,B) 精确分组，组内再数条件②③。
//
// 【转成几何问题】每组建两棵 Trie：左 Trie 插入 P 的反转，右 Trie 插入 S。
// 规则 (P, S) 在左 Trie 的终点是 u、右 Trie 的终点是 v。
// 询问的 rev(X) 在左 Trie 走到最深节点 x、Y 在右 Trie 走到最深节点 y。
//   P 是 X 的后缀 ⟺ rev(P) 是 rev(X) 的前缀 ⟺ x 在 u 的子树里；
//   S 是 Y 的前缀 ⟺ y 在 v 的子树里。
// 用 DFS 序把「子树」变成编号区间，规则 (u, v) 就变成一个矩形
//   [tin[u], tout[u]] × [tin[v], tout[v]]，
// 询问变成一个点 (tin[x], tin[y])。答案 = 覆盖这个点的矩形个数！
//
// 【扫描线】矩形拆成两个事件：左边界 +1（x = tin[u]）、右边界 -1（x = tout[u]+1），
// y 方向用树状数组做区间加；询问点在对应 x 处单点查前缀。按 x 扫完就是答案。
//
// 【复杂度】O((L1+L2) log(L1+L2))，适用于全部数据。比 AC 自动机好写，
// 但同样需要 map 分组来保证「只有核心相同的才互相匹配」。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXNODE = 2500000 + 10; // 两棵 Trie 合计不超过规则单侧总长度 + 2
const int MAXRULE = 200000 + 5;

// Trie 节点：head 是稀疏出边链表头（0 表示无出边），tin/tout 是子树 DFS 序区间
struct Node {
    int head;
    int tin, tout;
};

// Trie 的一条出边，用链式前向星存储
struct Edge {
    int ch, to, nxt;
};

// 一条规则拆成「差异核心 + 左侧 + 右侧」三部分
struct Rule {
    int core;
    int left, right; // 规则两侧字符串在对应 Trie 中的终点
};

// 显式 DFS 栈的一帧，edge 是尚未访问的下一条边
struct Frame {
    int u, edge;
};

// 扫描线事件：规则产生矩形（进入 +1 / 退出 -1），询问产生点。
// core 用来隔离不同差异核心的组：不同组的矩形和点绝不互相计数。
struct Event {
    // 节点、坐标、规则编号均不超过 2500002，用 int 控制大数组内存。
    int core, x;
    int y1, y2; // 矩形的 y 区间 [y1, y2]；询问点时 y1 == y2
    int value; // 矩形进入 +1、退出 -1；查询为 0
    int id;    // 更新为 0，查询为原询问编号
};

Node node[MAXNODE];
Edge edge[MAXNODE];
Rule rule[MAXRULE];
ll bit[MAXNODE]; // 树状数组，只用到 right_size 个位置
int node_cnt, edge_cnt;
int left_root, right_root, right_size;
ll n, q;
vector<Frame> dfs_stack; // 建 DFS 序用的显式栈，避免长链递归爆栈
vector<Event> events;    // 所有规则矩形与询问点的事件
vector<ll> answer;       // answer[id] 是第 id 个询问的答案
map<pair<string, string>, int> core_id; // 精确存储核心左右串，不使用哈希
int core_cnt;

// 动态开点：新建一个 Trie 节点并返回编号
int new_node() {
    node_cnt++;
    node[node_cnt].head = 0;
    node[node_cnt].tin = node[node_cnt].tout = 0;
    return node_cnt;
}

// 在 u 的出边里查找字符 ch 对应的孩子，找不到返回 0
int find_child(int u, int ch) {
    for (int e = node[u].head; e != 0; e = edge[e].nxt) {
        if (edge[e].ch == ch) return edge[e].to;
    }
    return 0;
}

// 取 u 的 ch 孩子，不存在就新建（插入规则时使用）
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

// 求两串的首尾不同位置 [L, R]，L = R = -1 表示两串相同
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

// 读入所有规则，按「差异核心（a 和 b 的差异区间）」精确分组：
// 同一组的规则才可能互相匹配。同时把核心左侧（反转）和右侧分别插入两棵 Trie。
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

// 用显式栈求 Trie 的 DFS 序，子树对应区间 [tin, tout]，返回节点总数
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

// 每条规则产生一个矩形：x 是左侧 Trie 的子树区间，y 是右侧 Trie 的子树区间。
// 矩形进入事件为 +1，退出事件为 -1（x = tout + 1）。
// 之所以子树区间能表达「P 是 X 的后缀」：DFS 序里 u 的子树就是所有以 u 为
// 前缀（即被 rev(P) 前缀匹配）的节点，这正是条件②的全部解。
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

// 读入询问，同样拆出差异核心；核心必须在规则里出现过，否则直接为 0。
// 两侧 Trie 只沿已存在边前进（不回跳），取到的最长前缀节点就是矩形查询的坐标。
// 不回跳是安全的：匹配得越深，节点只会在更深的子树里，而所有规则的左端节点
// 都是某个完整前缀的终点；恰好走到「最深匹配节点」时，它的子树就是
// 全部左端能被匹配的规则，不多不少。
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

// 事件排序：先按核心分组，再按 x 升序；同 x 时更新（id=0）排在查询前，
// 这样左边界被包含、退出位置 tout+1 被排除。
bool cmp_event(const Event &a, const Event &b) {
    if (a.core != b.core) return a.core < b.core;
    if (a.x != b.x) return a.x < b.x;
    return a.id < b.id; // 同坐标先更新后查询，包含左边界、排除 tout+1
}

// 树状数组：矩形事件在 y 区间上做区间加，询问单点查前缀
void bit_add(int pos, ll value) {
    for (; pos <= right_size; pos += pos & -pos) bit[pos] += value;
}

ll bit_query(int pos) {
    ll result = 0;
    for (; pos > 0; pos -= pos & -pos) result += bit[pos];
    return result;
}

// 二维扫描线：按核心组依次处理所有事件，询问得到「覆盖该点的矩形数」。
// 同 x 时先加后查：左边界 x = tin[u] 被包含，右边界 x = tout[u]+1 被排除，
// 恰好对应闭区间 [tin[u], tout[u]]。
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
    left_root = new_node();  // 左侧 Trie 的根，空串对应根
    right_root = new_node(); // 右侧 Trie 的根
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
