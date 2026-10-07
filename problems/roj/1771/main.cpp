/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:19
 * update_at: 2026-10-08 01:19
 */

// 1771 仓库选址：树上换根 DP + 按位异或的低位拆分
// 因为 M <= 15，异或只作用于距离的二进制低 4 位，于是
//     dis xor M = dis + ((dis mod 16) xor M) - (dis mod 16)
// 只要同时维护「距离和」与「距离 mod 16 的分布」就能 O(16n) 求全部答案。

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005; // 节点数上限
const int K = 16;        // 距离取模的模数，也是余数桶个数（M <= 15 只占低 4 位）

struct Edge {
    int to;  // 边的另一端
    int nxt; // 同一起点的下一条边编号，0 表示没有
    ll w;    // 边权（航线长度）
};

Edge edge[2 * MAXN]; // 无向边存两条
int head[MAXN];      // head[u] 为 u 的第一条边编号
int edge_cnt;        // 已经加入的边数

int n;      // 星球数
ll M;       // 题目常数 M
ll delta[K]; // delta[r] = (r xor M) - r，把异或改写成加减法的修正量

int parent_[MAXN]; // parent_[u]：u 在 1 号点为根的树中的父亲
ll pedge[MAXN];    // pedge[u]：u 到父亲的边权
int order_[MAXN];  // 先序遍历序列，父亲一定排在儿子前面
int order_cnt;
bool vis[MAXN];
int stack_[MAXN]; // 迭代 DFS 的显式栈，避免递归在链状树上爆栈

ll sub_sum[MAXN];    // sub_sum[u]：u 的子树内所有点到 u 的距离之和
int sub_size[MAXN];  // sub_size[u]：u 的子树大小
ll sub_cnt[MAXN][K]; // sub_cnt[u][r]：u 的子树内到 u 距离 mod 16 == r 的点数

ll all_sum[MAXN];    // all_sum[u]：全树所有点到 u 的距离之和
ll all_cnt[MAXN][K]; // all_cnt[u][r]：全树中到 u 距离 mod 16 == r 的点数

// 加一条无向边
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].w = w;
    edge[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}

// 迭代先序遍历定根，得到 parent_ / pedge / order_（不用递归，避免链状数据爆栈）
void build_order() {
    int top = 0;
    vis[1] = true;
    stack_[top++] = 1;
    while (top > 0) {
        int u = stack_[--top];
        order_[++order_cnt] = u;
        for (int e = head[u]; e != 0; e = edge[e].nxt) {
            int v = edge[e].to;
            if (vis[v]) continue;
            vis[v] = true;
            parent_[v] = u;
            pedge[v] = edge[e].w;
            stack_[top++] = v;
        }
    }
}

// 自底向上汇总子树信息：距离和 sub_sum 与余数分布 sub_cnt
void subtree_dp() {
    for (int u = 1; u <= n; ++u) {
        sub_size[u] = 1;
        sub_sum[u] = 0;
        sub_cnt[u][0] = 1; // 只有自己，距离 0
    }
    // 逆先序保证处理 u 时它的儿子都已汇总完毕
    for (int idx = order_cnt; idx >= 2; --idx) {
        int u = order_[idx];
        int p = parent_[u];
        ll w = pedge[u];
        int e = w % K;
        sub_sum[p] += sub_sum[u] + sub_size[u] * w; // 子树 u 的点到 p 都要多走 w
        sub_size[p] += sub_size[u];
        for (int r = 0; r < K; ++r) {
            sub_cnt[p][(r + e) % K] += sub_cnt[u][r]; // 子树 u 的点到 p 的距离多走 w
        }
    }
}

// 自顶向下换根：由父亲 p 的全树信息推出儿子 u 的全树信息
void reroot_dp() {
    all_sum[1] = sub_sum[1];
    for (int r = 0; r < K; ++r) all_cnt[1][r] = sub_cnt[1][r];

    for (int idx = 2; idx <= order_cnt; ++idx) {
        int u = order_[idx];
        int p = parent_[u];
        ll w = pedge[u];
        int e = w % K;
        ll rest[K]; // 全树去掉 u 子树后，剩下的点到 p 的距离余数分布
        for (int j = 0; j < K; ++j) {
            // 子树 u 在 p 处的余数桶里落在 (j - e) mod K，扣掉它才是「外部点」
            rest[j] = all_cnt[p][j] - sub_cnt[u][((j - e) % K + K) % K];
        }
        for (int r = 0; r < K; ++r) {
            // 外部点到 u 的距离 = 到 p 的距离 + w，余数整体后移 e
            all_cnt[u][r] = sub_cnt[u][r] + rest[((r - e) % K + K) % K];
        }
        // 外部点（n - sub_size[u] 个）距离各加 w，子树内点（sub_size[u] 个）各减 w
        all_sum[u] = all_sum[p] + (n - 2 * sub_size[u]) * w;
    }
}

int main() {
    if (scanf("%d %lld", &n, &M) != 2) return 0;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, c);
    }

    for (int r = 0; r < K; ++r) delta[r] = (r ^ M) - r;

    build_order();
    subtree_dp();
    reroot_dp();

    for (int u = 1; u <= n; ++u) {
        ll ans = all_sum[u];
        for (int r = 0; r < K; ++r) {
            // 距离 0 的那个点就是 u 自己，题面只统计「其他星球」，要扣掉
            ll cnt = all_cnt[u][r] - (r == 0 ? 1 : 0);
            ans += delta[r] * cnt;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
