/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 09:10
 * update_at: 2026-10-21 09:10
 */
// brute.cpp：n <= 8 的小数据暴力解，用来理解题意并给 main.cpp 当对拍答案。
//
// 暴力思路（完全不涉及 MST，只按题面定义验证）：
//   枚举所有非空的购买集合 S；
//   把叶子按 DFS 序编号 1..m，点 v 的子树叶子是一段区间 [lo_v, hi_v]，
//   对应新图 m+1 个点（0..m）上的边 (lo_v - 1, hi_v)；
//   检查 S 对应的这些边能否让 0..m 全部连通——连通即说明能清零任意叶子向量（题解里有论证）；
//   取连通方案里花费最小者作为第一问答案；
//   再把所有最优集合里的点求并集，升序输出，作为第二问答案。
//
// 复杂度 O(2^n * (n + m))，n <= 8 时约 255 * 16 次操作，随便跑。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;   // n <= 8，留足余量

int n;
int c[MAXN];
vector<int> adj[MAXN];

int par[MAXN];
int lo[MAXN], hi[MAXN];
int m;                 // 叶子个数

// ---------- 并查集：只用来判断 0..m 是否连通 ----------
int fa[MAXN];
int find(int x) {
    while (fa[x] != x) { fa[x] = fa[fa[x]]; x = fa[x]; }
    return x;
}

// 为一次暴力判定准备叶子编号与区间（树是固定的，只需算一次，这里写成函数便于阅读）
void build() {
    // 迭代 DFS 求前序（n <= 8 递归也不会爆栈，但和 main.cpp 保持同一种写法）
    vector<int> ord;
    vector<char> vis(n + 1, 0);
    vector<int> st;
    st.push_back(1);
    vis[1] = 1;
    par[1] = 0;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        ord.push_back(u);
        for (int v : adj[u]) {
            if (!vis[v]) { vis[v] = 1; par[v] = u; st.push_back(v); }
        }
    }

    for (int v = 1; v <= n; ++v) { lo[v] = INT_MAX; hi[v] = -1; }
    m = 0;
    for (int u : ord) {
        // 叶子 = 非根、度数为 1 的点
        if (u != 1 && (int)adj[u].size() == 1) { ++m; lo[u] = hi[u] = m; }
    }
    for (int i = (int)ord.size() - 1; i >= 0; --i) {
        int u = ord[i];
        if (par[u] != 0) {
            int p = par[u];
            lo[p] = min(lo[p], lo[u]);
            hi[p] = max(hi[p], hi[u]);
        }
    }
}

// 检查购买集合（mask 的第 (v-1) 位为 1 表示买了 v）能否清零任意叶子向量
bool feasible(int mask) {
    for (int i = 0; i <= m; ++i) fa[i] = i;
    for (int v = 1; v <= n; ++v) {
        if (!((mask >> (v - 1)) & 1)) continue;
        int a = find(lo[v] - 1), b = find(hi[v]);
        if (a != b) fa[a] = b;
    }
    int r = find(0);
    for (int i = 1; i <= m; ++i) {
        if (find(i) != r) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    build();

    long long best = LLONG_MAX;
    // 第一轮：找出最小花费
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (!feasible(mask)) continue;
        long long cost = 0;
        for (int v = 1; v <= n; ++v) {
            if ((mask >> (v - 1)) & 1) cost += c[v];
        }
        best = min(best, cost);
    }

    // 第二轮：把所有达到最小花费的集合里的点求并集
    vector<char> inAnswer(n + 1, 0);
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (!feasible(mask)) continue;
        long long cost = 0;
        for (int v = 1; v <= n; ++v) {
            if ((mask >> (v - 1)) & 1) cost += c[v];
        }
        if (cost != best) continue;
        for (int v = 1; v <= n; ++v) {
            if ((mask >> (v - 1)) & 1) inAnswer[v] = 1;
        }
    }

    vector<int> answer;
    for (int v = 1; v <= n; ++v) {
        if (inAnswer[v]) answer.push_back(v);
    }

    cout << best << ' ' << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        cout << answer[i] << (i + 1 == answer.size() ? '\n' : ' ');
    }
    return 0;
}
