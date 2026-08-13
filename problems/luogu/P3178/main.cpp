/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 23:00
 */
// main.cpp：P3178 树上操作，树链剖分 + 双树状数组（区间加、区间和）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
long long w[MAXN];       // 每个点的初始权值
vector<int> g[MAXN];     // 树的邻接表

// 树链剖分相关数组
int parent[MAXN];    // 父亲
int depth[MAXN];     // 深度，根为 1
int sz[MAXN];        // 子树大小
int heavy[MAXN];     // 重儿子（子树最大的儿子）
int top[MAXN];       // 重链链头
int dfn[MAXN];       // DFS 新编号 1..n
int timer;           // dfn 分配计数器
int order[MAXN];     // 第一次遍历得到的节点顺序
int order_cnt;       // order 的长度

// 仿 rbook 模板 fenwick-range-add-sum：双树状数组，区间加、区间和。
// bit_diff 维护差分 b[i]，bit_weighted 维护 i * b[i]。
template <typename T>
struct RangeFenwick {
    int n = 0;
    vector<T> bit_diff, bit_weighted;

    RangeFenwick(int n = 0) { init(n); }

    void init(int size) {
        n = size;
        bit_diff.assign(n + 1, 0);
        bit_weighted.assign(n + 1, 0);
    }

    static int lowbit(int x) { return x & -x; }

    void add(vector<T> &bit, int pos, T value) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            bit[i] += value;
        }
    }

    T sum(const vector<T> &bit, int pos) const {
        T answer = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            answer += bit[i];
        }
        return answer;
    }

    // 原数组区间 [left, right] 每个位置都加上 value
    void range_add(int left, int right, T value) {
        add(bit_diff, left, value);
        add(bit_diff, right + 1, -value);
        add(bit_weighted, left, value * static_cast<T>(left));
        add(bit_weighted, right + 1, -value * static_cast<T>(right + 1));
    }

    // 原数组前缀和：P(pos) = (pos+1) * sum(b, pos) - sum(i*b, pos)
    T prefix_sum(int pos) const {
        return static_cast<T>(pos + 1) * sum(bit_diff, pos)
             - sum(bit_weighted, pos);
    }

    T range_sum(int left, int right) const {
        return prefix_sum(right) - prefix_sum(left - 1);
    }
};

RangeFenwick<long long> bit;

// 第一遍：按 BFS 顺序求 parent/depth，并逆序统计子树大小、选出重儿子。
void build_hld() {
    order_cnt = 0;
    order[++order_cnt] = 1;
    parent[1] = 0;
    depth[1] = 1;
    for (int i = 1; i <= order_cnt; i++) {
        int u = order[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == parent[u]) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            order[++order_cnt] = v;
        }
    }
    for (int i = 1; i <= n; i++) sz[i] = 1;
    for (int i = order_cnt; i >= 2; i--) {
        int u = order[i];
        sz[parent[u]] += sz[u];
        if (sz[u] > sz[heavy[parent[u]]]) heavy[parent[u]] = u;
    }
}

// 第二遍：用链栈分配 dfn，保证每条重链编号连续、子树编号连续。
void build_dfn() {
    timer = 0;
    vector<pair<int, int>> chain_stack; // (当前节点, 所在链头)
    chain_stack.push_back(make_pair(1, 1));
    while (!chain_stack.empty()) {
        int u = chain_stack.back().first;
        int chain_top = chain_stack.back().second;
        chain_stack.pop_back();
        while (u != 0) {
            top[u] = chain_top;
            dfn[u] = ++timer;
            // 轻儿子开新链入栈，重儿子继续沿当前链走。
            for (int j = 0; j < (int)g[u].size(); j++) {
                int v = g[u][j];
                if (v != parent[u] && v != heavy[u]) {
                    chain_stack.push_back(make_pair(v, v));
                }
            }
            u = heavy[u];
        }
    }
}

// 查询从 x 到根 1 的路径点权和：拆成若干重链区间求和。
long long root_path_sum(int x) {
    long long answer = 0;
    while (top[x] != top[1]) {
        answer += bit.range_sum(dfn[top[x]], dfn[x]);
        x = parent[top[x]];
    }
    answer += bit.range_sum(dfn[1], dfn[x]);
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_hld();
    build_dfn();

    bit.init(n);
    // 初始权值：每个 dfn 位置单独区间加。
    for (int i = 1; i <= n; i++) {
        bit.range_add(dfn[i], dfn[i], w[i]);
    }

    while (m--) {
        int opt, x;
        long long a;
        cin >> opt >> x;
        if (opt == 1) { // 单点加：区间加退化为单点
            cin >> a;
            bit.range_add(dfn[x], dfn[x], a);
        } else if (opt == 2) { // 子树加：子树在 dfn 上是连续区间
            cin >> a;
            bit.range_add(dfn[x], dfn[x] + sz[x] - 1, a);
        } else { // 根路径和：重链区间求和
            cout << root_path_sum(x) << '\n';
        }
    }

    return 0;
}
