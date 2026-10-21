/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-21 08:50
 */
// 糖果：五类大小关系 + 每人至少一颗，求最小糖果总数。
// 全部写成下界形式 x_v >= x_u + w：
//   X=1 相等   -> 两个方向各一条 0 权边
//   X=2 少于   -> x_b >= x_a + 1（整数性让"少于"就是"至少少 1"）
//   X=3 不少于 -> x_a >= x_b，权 0
//   X=4 多于   -> x_a >= x_b + 1
//   X=5 不多于 -> x_b >= x_a，权 0
// 要求最少就是求最长路，初值 1（每人至少一颗）。
// 矛盾判定：权值只有 0/1，所以环权和 = 环上权 1 边的条数；而任何有向环都完全落在
// 某个强连通分量内，于是只需检查每个分量内部有没有权 1 边。全 0 环权和为 0，无害。
// 无解排除后缩点成 DAG，按拓扑序做最长路；同分量点强制相等，最后按分量大小加权求和。
//
// 强连通分量用 Tarjan 递归一遍 DFS 求出：在 DFS 树上用时间戳 dfn 与回溯值 low 判根，
// 用栈收集当前分量，出栈时就得到一个完整 SCC。只需正向图，不需要反图和第二遍遍历。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5; // 点数上界 N <= 1e5

struct Edge {
    int to;
    int w; // 0 表示"不少于"，1 表示"严格多于"
};

struct RawEdge {
    int u, v, w;
};

int n, k;
vector<Edge> g[MAXN];  // 正向图，Tarjan 只用这一张图
vector<RawEdge> edges; // 带权边表，缩点时要用

void add_edge(int u, int v, int w) {
    g[u].push_back({v, w});
    edges.push_back({u, v, w});
}

int dfn[MAXN];    // 第一次访问的时间戳，0 表示未访问
int low[MAXN];    // 从该点出发能回溯到的最小时间戳
int comp[MAXN];   // 每个点所属分量编号，从 1 开始
int tarjan_timer; // 时间戳计数器
int comp_cnt;     // 分量个数
int stk[MAXN];    // Tarjan 的分量收集栈
int stk_top;
bool in_stack[MAXN];

// 从 u 出发做一遍 DFS；返回时 u 所在的分量已经确定（可能已出栈）。
// low[u] == dfn[u] 说明 u 是本分量的根，此时弹出栈中 u 及其之后的所有点，
// 它们恰好构成一个强连通分量。
void tarjan(int u) {
    dfn[u] = low[u] = ++tarjan_timer;
    stk[stk_top++] = u;
    in_stack[u] = true;

    for (const Edge &e : g[u]) {
        int v = e.to;
        if (dfn[v] == 0) {
            tarjan(v);
            // 子树返回后，用子树能回溯到的最早时间戳更新自己
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_stack[v]) {
            // 回边或横叉边指向仍在栈中的点：只能拿 dfn[v] 更新 low[u]。
            // 指向已出栈点的边忽略——那些点属于已完成的分量，不可能再和 u 成环。
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }

    if (low[u] == dfn[u]) {
        comp_cnt++;
        while (true) {
            int v = stk[--stk_top];
            in_stack[v] = false;
            comp[v] = comp_cnt;
            if (v == u) break;
        }
    }
}

bool read_input() {
    cin >> n >> k;
    bool possible = true;

    for (int i = 0; i < k; i++) {
        int kind, a, b;
        cin >> kind >> a >> b;
        if (kind == 1) {
            add_edge(a, b, 0); // x_a >= x_b
            add_edge(b, a, 0); // x_b >= x_a
        } else if (kind == 2) {
            if (a == b) possible = false; // 自己少于自己
            add_edge(a, b, 1);            // x_b >= x_a + 1
        } else if (kind == 3) {
            add_edge(b, a, 0); // x_a >= x_b
        } else if (kind == 4) {
            if (a == b) possible = false; // 自己多于自己
            add_edge(b, a, 1);            // x_a >= x_b + 1
        } else {
            add_edge(a, b, 0); // x_a <= x_b 即 x_b >= x_a
        }
    }
    return possible;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!read_input()) {
        cout << -1 << '\n'; // 自环形式的显式矛盾
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) tarjan(i);
    }

    // 缩点：分量大小、分量 DAG、入度
    vector<long long> comp_size(comp_cnt + 1, 0);
    for (int i = 1; i <= n; i++) comp_size[comp[i]]++;

    // 建立一个新的图
    vector<vector<Edge>> dag(comp_cnt + 1);
    vector<int> indegree(comp_cnt + 1, 0);
    for (const auto &e : edges) {
        int from = comp[e.u];
        int to = comp[e.v];
        if (from == to) {
            // 分量内出现权 1 边，要求 x > x，正环无解
            if (e.w) {
                cout << -1 << '\n';
                return 0;
            }
        } else {
            dag[from].push_back({to, e.w});
            indegree[to]++;
        }
    }

    // 缩点后是 DAG，按拓扑序求每个分量的最长路值，初值 1（每人至少一颗）
    vector<long long> value(comp_cnt + 1, 1);
    queue<int> que;
    for (int c = 1; c <= comp_cnt; c++) {
        if (indegree[c] == 0) que.push(c);
    }

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (const auto &e : dag[u]) {
            long long candidate = value[u] + e.w;
            if (candidate > value[e.to]) value[e.to] = candidate;
            if (--indegree[e.to] == 0) que.push(e.to);
        }
    }

    // 分量内每个点拿同样的糖，按分量大小加权求和
    long long answer = 0;
    for (int c = 1; c <= comp_cnt; c++) {
        answer += value[c] * comp_size[c];
    }
    cout << answer << '\n';

    return 0;
}
