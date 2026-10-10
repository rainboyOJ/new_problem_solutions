/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:26
 * update_at: 2026-10-07 20:26
 */

// 环上计数：多组数据，每组求
//   ans1 = 不在任何简单环上的边数（= 桥数）
//   ans2 = 在至少两个简单环上的边数（= 「边数 > 点数」的点双连通分量里的边数之和）
// 读到 0 0 结束。n <= 1e4，m <= 1e5，点从 0 开始编号。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;   // 点数上限 1e4，留一点余量
const int MAXM = 200005;  // 无向边存成两条有向边：2 * 1e5

typedef long long ll;

// 链式前向星。边从 2 开始编号，于是 e 与 e ^ 1 互为反向边，
// 「跳过父边」只要比较 e == (fe ^ 1)，不用额外存每条边的起点。
int head[MAXN];   // head[u]：点 u 的第一条出边
int eto[MAXM];    // eto[e]：边 e 的终点
int enxt[MAXM];   // enxt[e]：与 e 同起点的下一条边
int edge_cnt;

int dfn[MAXN];     // dfn[u]：u 的 dfs 序，0 表示未访问
int low[MAXN];     // low[u]：u 的子树能通过回边到达的最小 dfn
int vstamp[MAXN];  // 统计块内点数用的时间戳：等于当前块号表示本块内已数过
int estack[MAXM];  // 边栈：每次弹栈结束就得到一个点双（块）
int estop;

ll ans1, ans2;  // 一组数据的两个答案

// 迭代 dfs 的一帧。深链可长达 1e4，递归写法有爆栈风险，故用显式栈。
struct Frame {
    int u;   // 当前点
    int it;  // 正在处理的出边编号，0 表示邻接表已走完
    int fe;  // 进入 u 的树边编号，0 表示 u 是本次 dfs 的根
};
Frame fstk[MAXN];

// 读入一组数据：n 个点、m 条边，并重置本组用到的全局数组
void read_graph(int n, int m) {
    edge_cnt = 2;  // 边编号从 2 开始，0 和 1 留给「空边」
    for (int i = 0; i < n; i++) {
        head[i] = 0;
        dfn[i] = 0;
        low[i] = 0;
        vstamp[i] = 0;  // 块号从 1 开始，0 天然表示「还没在块里出现过」
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        eto[edge_cnt] = v;
        enxt[edge_cnt] = head[u];
        head[u] = edge_cnt++;
        eto[edge_cnt] = u;
        enxt[edge_cnt] = head[v];
        head[v] = edge_cnt++;
    }
}

// 弹边栈直到弹出入边 pe，得到一个点双。返回块内边数，点数由调用方用块号去重统计。
// 块内边数与点数决定了这个块的性质：边数 > 点数时块内每条边都在至少两个简单环上。
int pop_block(int pe, int blk_id) {
    int ecnt = 0;
    int vcnt = 0;
    while (true) {
        int e = estack[estop--];
        ecnt++;
        int a = eto[e ^ 1];  // 边 e 的起点 = 反向边的终点
        int b = eto[e];      // 边 e 的终点
        if (vstamp[a] != blk_id) {
            vstamp[a] = blk_id;
            vcnt++;
        }
        if (vstamp[b] != blk_id) {
            vstamp[b] = blk_id;
            vcnt++;
        }
        if (e == pe) break;  // 回到入边，本块弹完
    }
    return ecnt > vcnt ? ecnt : 0;  // 边数 <= 点数时该块不贡献 ans2
}

// 从点 s 出发迭代 dfs，求以它所在连通块里所有点双
void dfs_from(int s, int &timer, int &blk_id) {
    dfn[s] = low[s] = ++timer;
    int top = 0;
    fstk[0].u = s;
    fstk[0].it = head[s];
    fstk[0].fe = 0;

    while (top >= 0) {
        int u = fstk[top].u;
        int it = fstk[top].it;
        if (it != 0) {
            fstk[top].it = enxt[it];  // 先推进游标，后面可以自由访问栈
            if (it == (fstk[top].fe ^ 1)) continue;  // 是父边的反向边，跳过
            int v = eto[it];
            if (dfn[v] == 0) {
                estack[++estop] = it;  // 树边入栈
                dfn[v] = low[v] = ++timer;
                top++;
                fstk[top].u = v;
                fstk[top].it = head[v];
                fstk[top].fe = it;
            } else if (dfn[v] < dfn[u]) {
                estack[++estop] = it;  // 回边：只从较深的一端入栈一次
                low[u] = min(low[u], dfn[v]);
            }
        } else {
            int fe = fstk[top].fe;
            top--;  // 弹出 u
            if (fe == 0) continue;  // 根节点，其块已在子节点返回时全部弹完
            int p = fstk[top].u;
            low[p] = min(low[p], low[u]);
            if (low[u] >= dfn[p]) {
                if (low[u] > dfn[p]) ans1++;  // 割边：不在任何简单环上
                blk_id++;
                ans2 += pop_block(fe, blk_id);
            }
        }
    }
}

// 处理一组数据并输出一行答案
void solve_group(int n, int m) {
    read_graph(n, m);

    ans1 = 0;
    ans2 = 0;
    estop = 0;
    int timer = 0;
    int blk_id = 0;

    // 孤立点不构成块，但它的 head 为 0，dfs 进来也只会立刻弹出，无需特判
    for (int s = 0; s < n; s++) {
        if (dfn[s] == 0) dfs_from(s, timer, blk_id);
    }
    cout << ans1 << ' ' << ans2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;  // 结束标志
        solve_group(n, m);
    }
    return 0;
}
