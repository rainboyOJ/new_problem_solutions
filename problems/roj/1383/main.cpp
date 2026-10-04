/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:20
 * update_at: 2026-10-05 00:20
 */
#include <cstdio>
#include <bitset>
using namespace std;

typedef long long ll;

const int MAXN = 205;

// 题目含义：第 i 个营员愿意把资料拷贝给他这一行给出的营员。
// 一张光盘放在 p 手里，能覆盖的正是 p 在有向图上可达的所有点（含 p 自己）。
// 答案 = 缩点后有向无环图中入度为 0 的强连通分量（源分量）个数。

bitset<MAXN> reach[MAXN]; // reach[i] = i 能到达的点集（含 i 自己）的位掩码
bitset<MAXN> pred[MAXN];  // pred[i] = 能到达 i 的点集的位掩码，即闭包矩阵的第 i 列
char counted[MAXN];       // counted[i] = 1 表示 i 所在的源分量已经统计过，用于去重

int main() {
    ll n;
    scanf("%lld", &n);

    for (ll i = 1; i <= n; i++) {
        reach[i].set(i); // 自己也算可达，闭包与 SCC 判定都依赖这一点
        ll j;
        scanf("%lld", &j);
        while (j != 0) { // 每行以 0 结束
            reach[i].set(j);
            scanf("%lld", &j);
        }
    }

    // Floyd 式传递闭包：i 能到 k，就能到 k 能到的一切
    for (ll k = 1; k <= n; k++) {
        for (ll i = 1; i <= n; i++) {
            if (reach[i].test(k)) {
                reach[i] |= reach[k];
            }
        }
    }

    // 转置闭包矩阵：reach[j] 的第 i 位为 1，说明 j 能到 i，即 j 属于 pred[i]
    for (ll j = 1; j <= n; j++) {
        for (ll i = 1; i <= n; i++) {
            if (reach[j].test(i)) {
                pred[i].set(j);
            }
        }
    }

    // 统计源分量个数：SCC(i) = reach[i] & pred[i]。
    // pred[i] 中所有点都能被 i 反过来到达（pred[i] 是 reach[i] 的子集）时，
    // 没有任何外部边能进入 i 所在分量，它就是源分量；同一分量去重只算一次。
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        if (counted[i]) {
            continue;
        }
        if ((pred[i] & ~reach[i]).none()) {
            ans++;
            bitset<MAXN> scc = reach[i] & pred[i];
            for (ll j = 1; j <= n; j++) {
                if (scc.test(j)) {
                    counted[j] = 1;
                }
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}
