// main.cpp：「一本通 3.6 练习 4」电力 —— 求删去一个点后连通块最多有多少。
// 思路：答案 = 原连通块数 - 1 + max pieces(v)。
// pieces(v) 用一次迭代 Tarjan（dfn/low）统计：非根 v 的 pieces = 1 + 分离孩子数
// （孩子 c 满足 low[c] >= dfn[v]，即 c 的子树绕不开 v）；根的 pieces = 子树数
// （根的分离孩子数恰好就是子树数，但不再加 1）；孤立点自然得 0。

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:13
 * update_at: 2026-10-05 06:13
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

typedef long long ll;

int n, m;
vector<int> g[MAXN]; // 邻接表：g[u] = u 的所有邻点
int dfn[MAXN];       // DFS 进入时刻，0 表示未访问；时刻从 1 开始编号
int low[MAXN];       // low[u] = u 的子树经回边能到达的最小 dfn
int split_cnt[MAXN]; // u 的孩子里 low[child] >= dfn[u] 的个数（分离孩子数）
int tick;            // dfn 计时器
int comps;           // 原图连通块数
int best;            // 所有顶点中「删去后其所在块裂成的块数」的最大值

// 加一条无向边。
void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// 对 start 所在连通块做一次迭代 Tarjan（P 可达 10000，链状图会打穿递归栈）。
// 弹栈时向父回传 low、给父累加分离孩子数，并用当前点更新 best。
void dfs(int start) {
    // 栈帧：[顶点 u, 父顶点 par, 下一条待查邻边下标 i, 邻边总数 sz]
    static int st_u[MAXN], st_par[MAXN], st_i[MAXN], st_sz[MAXN];
    int top = 0;
    tick++;
    dfn[start] = low[start] = tick;
    top++;
    st_u[top] = start;
    st_par[top] = -1;
    st_i[top] = 0;
    st_sz[top] = g[start].size();

    while (top > 0) {
        int u = st_u[top];
        int par = st_par[top];
        int i = st_i[top];
        if (i < st_sz[top]) {
            st_i[top] = i + 1;
            int v = g[u][i];
            if (dfn[v] == 0) {
                // 树边：向下展开，孩子入栈
                tick++;
                dfn[v] = low[v] = tick;
                top++;
                st_u[top] = v;
                st_par[top] = u;
                st_i[top] = 0;
                st_sz[top] = g[v].size();
            } else if (v != par && dfn[v] < dfn[u]) {
                // 回边：无向图对称边只取编号小的一端，防止把父方向的边当回边
                if (dfn[v] < low[u]) low[u] = dfn[v];
            }
        } else {
            // u 的邻边走完：出栈并向父结算
            top--;
            if (par >= 0) {
                if (low[u] < low[par]) low[par] = low[u];
                if (low[u] >= dfn[par]) {
                    // u 的子树绕不开 par，删掉 par 后 u 的子树自成一块
                    split_cnt[par]++;
                }
            }
            // 非根删点后 = 分离孩子数 + 父方向那一大块（+1）；根只有各子树（不加 1）
            int pieces = split_cnt[u] + (par >= 0);
            if (pieces > best) best = pieces;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m) {
        if (n == 0) break; // 读入以 0 0 结束
        for (int i = 0; i < n; i++) {
            g[i].clear();
            dfn[i] = 0;
            split_cnt[i] = 0;
        }
        for (int i = 1; i <= m; i++) { // 保证无重边，直接双向建表
            int a, b;
            cin >> a >> b;
            add_edge(a, b);
        }
        tick = 0;
        comps = 0;
        best = 0;
        for (int i = 0; i < n; i++) {
            if (dfn[i] == 0) { // 未访问点才启动新 DFS（兜底处理多个连通块）
                comps++;
                dfs(i);
            }
        }
        // 删掉 v 不影响 v 之外的连通块：总数 = 其余块 (comps-1) + v 所在块裂成的块数
        cout << comps - 1 + best << "\n";
    }
    return 0;
}
