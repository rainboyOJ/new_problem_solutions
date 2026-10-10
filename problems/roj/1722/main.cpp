/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:42
 * update_at: 2026-10-07 18:42
 */
// main.cpp：骑士游戏，在"怪兽产生的怪兽"这张超图上求最小体力，用 SPFA 式松弛求解。
// 设 dp[i] = 彻底消灭一只 i 号怪兽（连同它衍生出的一切）所需的最小体力，则
//     dp[i] = min( K_i , S_i + Σ dp[son] )
// 右边依赖别的 dp，还可能有环（怪兽可以变回自己），于是把每个 i 都初始化成 K_i，
// 谁变小就把"变小了多少"沿反向边推给产生它的怪兽，重新结算一次它的 Σ dp[son]。
// 与 main.py 同一算法：同样的反向边 + 同样的 delta 传播。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;      // 怪兽种数上限 N <= 2e5
const int MAXM = 1000005;     // ΣR_i <= 1e6，反向边条数就是它

int N;                        // 怪兽种数
ll S[MAXN];                   // S[i]：普通攻击 i 号怪兽消耗的体力
ll K[MAXN];                   // K[i]：法术攻击 i 号怪兽消耗的体力
int st[MAXN];                 // st[i]：i 号怪兽的衍生怪编号在 sons[] 里的起始位置（前缀和）
int sons[MAXM];               // 所有衍生怪编号按父亲分组平铺存放，编号用 int 足够（<= 2e5）

int head[MAXN];               // head[u]：反向边链表头，链上每条边指向"会产生 u 的怪兽"
int nxt_edge[MAXM];           // 链式前向星的 next 指针
int edge_to[MAXM];            // edge_to[e]：第 e 条反向边的目标，即父亲怪兽编号
int ecnt;                     // 已加入的反向边条数

__int128 sump[MAXN];          // sump[i] = S_i + Σ dp[son]：普通攻击路线的当前代价
                              // ΣR_i * K_i 可达 1e6 * 5e14 = 5e20，超出 ll，必须用 __int128
ll dp[MAXN];                  // dp[i]：最优代价，恒 <= K_i <= 5e14，ll 装得下
__int128 pend[MAXN];          // pend[i]：dp[i] 已下降但还没推给父亲们的量
bool inq[MAXN];               // inq[i]：i 是否已在队列里，避免重复入队

// 快读：输入全是非负整数，最大 13MB，按块 fread + 手写解析
const int BUFSIZE = 1 << 16;
char ibuf[BUFSIZE];
int ipos = 0, ilen = 0;

// 取下一个字符，缓冲区空了就再读一块；返回 0 表示输入结束
char get_char() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, BUFSIZE, stdin);
        ipos = 0;
        if (ilen <= 0) return 0;
    }
    return ibuf[ipos++];
}

// 读一个非负整数
ll read_int() {
    char c = get_char();
    while (c < '0' || c > '9') {
        if (c == 0) return 0;
        c = get_char();
    }
    ll x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

// 加一条反向边 son -> parent：表示"son 号怪兽是 parent 号怪兽衍生出来的"
void add_edge(int son, int parent) {
    ecnt++;
    edge_to[ecnt] = parent;
    nxt_edge[ecnt] = head[son];
    head[son] = ecnt;
}

void solve() {
    N = read_int();
    st[1] = 1;
    for (int i = 1; i <= N; i++) {
        S[i] = read_int();
        K[i] = read_int();
        int r = read_int();
        st[i + 1] = st[i] + r;
        for (int e = st[i]; e < st[i + 1]; e++) {
            sons[e] = read_int();
        }
    }

    // 反向边 + 初值：dp 全取法术攻击的代价 K_i，于是 sump[i] = S_i + Σ K[son]
    for (int i = 1; i <= N; i++) {
        sump[i] = S[i];
        for (int e = st[i]; e < st[i + 1]; e++) {
            int son = sons[e];
            add_edge(son, i);
            sump[i] += K[son];
        }
    }

    queue<int> q;
    for (int i = 1; i <= N; i++) {
        dp[i] = K[i];
        inq[i] = false;
        pend[i] = 0;
    }
    // 谁一开始就"普通攻击更便宜"，就先把它降下来、入队待传播
    for (int i = 1; i <= N; i++) {
        if (sump[i] < dp[i]) {
            pend[i] += dp[i] - sump[i];
            dp[i] = sump[i];
            inq[i] = true;
            q.push(i);
        }
    }

    // SPFA：出队时把这一轮攒下的下降量 d 推给所有父亲，父亲重新结算后可能继续下降
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        __int128 d = pend[u];
        pend[u] = 0;
        if (d == 0) continue;
        for (int e = head[u]; e != 0; e = nxt_edge[e]) {
            int p = edge_to[e];        // p 会产生 u，u 便宜了 p 的普通攻击也跟着便宜
            sump[p] -= d;
            if (sump[p] < dp[p]) {
                pend[p] += dp[p] - sump[p];
                dp[p] = sump[p];
                if (!inq[p]) {
                    inq[p] = true;
                    q.push(p);
                }
            }
        }
    }

    printf("%lld\n", dp[1]); // 只有 1 号怪兽入侵村庄，答案就是 dp[1]
}

int main() {
    solve();
    return 0;
}
