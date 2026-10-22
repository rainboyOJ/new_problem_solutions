/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 09:10
 * update_at: 2026-10-21 09:10
 */
// CF1120D Power Tree
// 题意：给一棵以 1 为根的树，每个点有权值 c_v。买一些点，买完之后对任意叶子取值，
//       都能通过「给某个已买点的子树内所有叶子同时加同一个整数」把叶子清零。
//       第一问：最小花费；第二问：哪些点出现在某个最优购买集合里。
//
// ===== 关键建模（本文件的核心，全部推导浓缩在下面几行）=====
// 把叶子按 DFS 序编号 1..m。点 v 的子树内叶子恰好是一段连续区间 [lo_v, hi_v]。
// 「给 v 的子树叶子整体 +x」 等价于在一维差分数组 d[0..m] 上做两次点修改：
//     d[lo_v - 1] += x ,  d[hi_v] -= x
// 于是每个点 v 唯一对应新图上的边 (lo_v - 1, hi_v)，边权 c_v；新图共 m+1 个点（编号 0..m）。
//
// 第一问 = 这张新图的最小生成树权值。为什么？
//   * 购买集合 S 能清零任意叶子向量 <=> {差分向量 of v | v in S} 张成整个 m 维空间
//     （叶子向量与差分向量一一对应，后者有 m 个自由度且和为 0 的约束由 d[0], d[m] 抵消）。
//   * 每个向量都是 (+1 在 lo-1) + (-1 在 hi) 的形式，恰好是一条「边上两端一加一减」的模式；
//     这样一族向量的秩为 m（满秩）当且仅当它们对应的边让 0..m 这 m+1 个点全部连通。
//     （连通 -> 沿任一生成树自底向上可依次独立调整每个点；不连通 -> 某个连通块内的差分和为 0，
//       存在张成不到的向量。）
//   * 「边集让 0..m 连通」当且仅当它包含一棵生成树，因此取权值最小的生成树最省。
//   顺带一提：所有叶子点 v 的区间是 [k,k]，给出边 (k-1, k)，所以新图必然连通（一条链），MST 一定存在。
//
// 第二问 = 判定每条边是否属于「某棵」MST，等价判定：把所有权值严格小于 c_e 的边加进来时，
//   e 的两个端点是否还不连通。实现上就是分组 Kruskal：
//   处理到权值 w 这一组时，并查集里恰好是「只用 < w 的边」的连通状态，
//   先拿这个基线状态对组内所有边判一次，再统一把整组合并掉。
//   这样做避免了「对每条边重建一次并查集」的 O(n^2)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// n <= 2e5
const int MAXN = 200005;

int n;
int c[MAXN];                 // c[v]：买下点 v 的花费
vector<int> adj[MAXN];       // 原树邻接表

int par[MAXN];               // 迭代 DFS 得到的父亲
int lo[MAXN], hi[MAXN];      // 点 v 的子树内叶子编号区间 [lo, hi]

// 新图上的一条边：连接 u、v，权 w，来源顶点 id
struct Edge {
    int u, v, w, id;
    bool operator<(const Edge &o) const { return w < o.w; }
};
vector<Edge> edge;

// ---- 并查集（路径压缩 + 按大小合并），本题只需按大小合并即可保证复杂度 ----
int fa[MAXN], sz[MAXN];

void dsu_init(int n) {
    for (int i = 0; i <= n; ++i) { fa[i] = i; sz[i] = 1; }
}

int find(int x) {
    while (fa[x] != x) { fa[x] = fa[fa[x]]; x = fa[x]; }  // 路径减半，迭代写法不递归
    return x;
}

// 合并成功返回 true（这条边被 MST 采纳）
bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    fa[b] = a; sz[a] += sz[b];
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

    // ---------- 1. 显式栈求 DFS 序（n = 2e5 的链会爆递归栈，必须迭代） ----------
    // 栈式 DFS：弹出 u 时把未访问的儿子全部压栈，之后最晚压入的儿子最先被完整展开，
    // 因此得到的 preorder 是真正的 DFS 前序，每棵子树在其中是连续一段，叶子也按 DFS 序出现。
    vector<int> ord;
    ord.reserve(n);
    {
        vector<char> vis(n + 1, 0);
        vector<int> st;
        st.reserve(n);
        st.push_back(1);
        vis[1] = 1;
        par[1] = 0;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            ord.push_back(u);
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    par[v] = u;
                    st.push_back(v);
                }
            }
        }
    }

    // ---------- 2. 叶子按 DFS 序编号 1..m ----------
    // 题面定义：叶子 = 非根、度数为 1 的点。
    int m = 0;
    for (int v = 1; v <= n; ++v) { lo[v] = INT_MAX; hi[v] = -1; }
    for (int u : ord) {
        if (u != 1 && (int)adj[u].size() == 1) {   // u 是叶子
            ++m;
            lo[u] = hi[u] = m;
        }
    }

    // 逆着 DFS 序回溯，把子树的叶子区间并到父亲：O(n)
    for (int i = (int)ord.size() - 1; i >= 0; --i) {
        int u = ord[i];
        if (par[u] != 0) {
            int p = par[u];
            if (lo[u] < lo[p]) lo[p] = lo[u];
            if (hi[u] > hi[p]) hi[p] = hi[u];
        }
    }

    // ---------- 3. 建新图：m+1 个点（0..m），点 v 对应边 (lo_v - 1, hi_v) ----------
    edge.reserve(n);
    for (int v = 1; v <= n; ++v) {
        edge.push_back(Edge{lo[v] - 1, hi[v], c[v], v});
    }
    sort(edge.begin(), edge.end());

    // ---------- 4. 按权值分组的 Kruskal，同时回答两问 ----------
    dsu_init(m);
    ll total = 0;                 // 第一问：MST 总权值
    vector<int> answer;           // 第二问：属于某棵 MST 的边对应的点
    answer.reserve(n);

    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && edge[j].w == edge[i].w) ++j;   // [i, j) 是本组同权边

        // (a) 先用「只看 < w 的边」的并查集基线判断组内每条边
        //     两端在基线里不连通 <=> 存在某棵 MST 含这条边
        for (int k = i; k < j; ++k) {
            if (find(edge[k].u) != find(edge[k].v)) answer.push_back(edge[k].id);
        }
        // (b) 再把整组统一合并（同一组内先判后合，避免组内边互相影响判断）
        for (int k = i; k < j; ++k) {
            if (unite(edge[k].u, edge[k].v)) total += edge[k].w;
        }
        i = j;
    }

    sort(answer.begin(), answer.end());

    cout << total << ' ' << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        cout << answer[i] << (i + 1 == answer.size() ? '\n' : ' ');
    }
    return 0;
}
