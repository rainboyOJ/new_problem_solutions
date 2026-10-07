/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:13
 * update_at: 2026-10-07 18:13
 */

// 一本通 1720《均值最小环》：求带权有向图中所有环的"平均边权"最小值，无环输出约定字符串。
//
// 做法：01 分数规划 + 二分答案 + SPFA 判负环（同 UVA11090 / BZOJ1486 / P3199）。
//   * 二分 λ：把每条边权改成 w - λ，图中存在负环 ⟺ 存在环使 Σw/len < λ，即 λ 偏大。
//   * 判负环用多源 SPFA：dis[] 全 0（等价加一个到所有点的 0 权虚拟源），图可以不连通；
//     用"最短路边数 >= n 必有重复顶点 ⇒ 该回路为负"来判定。
//   * 无环要先精确判掉（DFS 三色标记），否则二分在无环图上永远判不出负环，
//     会把答案当成 0.00 输出，与约定的 "PaPaFish is laying egg!" 不符。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;    // 点数上限 1000
const int MAXM = 10005;   // 边数上限 10000
const double EPS = 1e-12; // 浮点比较容差

// 链式前向星：head[u] 为 u 的第一条出边编号，0 表示没有出边
int head[MAXN];
int nxt[MAXM];
int to_[MAXM];
ll wt[MAXM];   // 边权，题面 0 <= w <= 1e7，用 ll 存
int eid;       // 已分配的边编号

ll n, m;       // 点数和边数

// 加一条 u -> v 权值为 w 的有向边
void add_edge(ll u, ll v, ll w) {
    eid++;
    to_[eid] = v;
    wt[eid] = w;
    nxt[eid] = head[u];
    head[u] = eid;
}

// 三色标记判环：0 = 未访问，1 = 在当前 DFS 栈上，2 = 已完成
int color[MAXN];
int stk_v[MAXN];  // 迭代版 DFS 的顶点栈
int stk_e[MAXN];  // 迭代版 DFS 的"下一条待枚举出边"栈

// 图中是否存在环（迭代 DFS，避免 n=1000 递归深度问题）
bool has_cycle() {
    for (int i = 1; i <= n; i++) color[i] = 0;
    for (int s = 1; s <= n; s++) {
        if (color[s] != 0) continue;
        int top = 0;
        stk_v[0] = s;
        stk_e[0] = head[s];
        color[s] = 1;
        while (top >= 0) {
            int u = stk_v[top];
            int e = stk_e[top];
            if (e == 0) {          // u 的出边枚举完了，u 成为已完成点
                color[u] = 2;
                top--;
                continue;
            }
            stk_e[top] = nxt[e];   // 先把下一条出边记下，再决定是否深入
            int v = to_[e];
            if (color[v] == 1) return true;  // 指向栈上的点 ⇒ 有环
            if (color[v] == 0) {
                color[v] = 1;
                top++;
                stk_v[top] = v;
                stk_e[top] = head[v];
            }
        }
    }
    return false;
}

// SPFA 判负环用：dis[i] = 虚拟源点到 i 的当前最短距离，cnt[i] = 该最短路的边数
double dis[MAXN];
int cnt[MAXN];
char inq[MAXN];           // 是否在队列中，只有 0/1，用 char 省内存
int que[MAXN * 128];      // 手写循环队列，容量按最坏入队次数放大

// 把每条边权改成 w - lambda 后，图中是否存在负环
bool has_negative_cycle(double lambda) {
    int qh = 0, qt = 0;
    for (int i = 1; i <= n; i++) {
        dis[i] = 0.0;         // 多源起点：等价于虚拟源点连 0 权边到每个点
        cnt[i] = 0;
        inq[i] = 1;
        que[qt++] = i;
    }
    while (qh < qt) {
        int u = que[qh++];
        inq[u] = 0;
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to_[e];
            double nd = dis[u] + (double)wt[e] - lambda;
            if (nd < dis[v] - EPS) {
                dis[v] = nd;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return true;  // 最短路用了 >= n 条边 ⇒ 绕出了负环
                if (!inq[v]) {
                    inq[v] = 1;
                    que[qt++] = v;
                }
            }
        }
        if (qt > MAXN * 128 - MAXN - 5) {  // 队列吃紧就整体前移，正常不会走到
            int k = 0;
            for (int i = qh; i < qt; i++) que[k++] = que[i];
            qh = 0;
            qt = k;
        }
    }
    return false;
}

// 读入一个整数（题面全为非负整数，负数只是容错）
ll read_int() {
    int c = getchar();
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    ll sgn = 1;
    if (c == '-') {
        sgn = -1;
        c = getchar();
    }
    ll x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return sgn * x;
}

int main() {
    n = read_int();
    m = read_int();

    ll maxw = 0;   // 答案的上界：最小平均环的平均值一定不超过最大边权
    for (ll i = 0; i < m; i++) {
        ll u = read_int(), v = read_int(), w = read_int();
        add_edge(u, v, w);
        if (w > maxw) maxw = w;
    }

    if (!has_cycle()) {   // ① 无环：输出约定字符串
        printf("PaPaFish is laying egg!\n");
        return 0;
    }

    // ② 01 分数规划：答案 ans ∈ [0, maxw]，二分找最小的"存在负环"的 λ
    double lo = 0.0, hi = (double)maxw;
    for (int it = 0; it < 60; it++) {
        double mid = (lo + hi) * 0.5;
        if (has_negative_cycle(mid)) hi = mid;  // 存在负环 ⇒ ans <= mid
        else lo = mid;
    }
    printf("%.2f\n", (lo + hi) * 0.5);
    return 0;
}
