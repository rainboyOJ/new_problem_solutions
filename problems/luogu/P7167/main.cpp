/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 13:30
 * update_at: 2026-08-05 14:00
 */
// 单调栈求每个圆盘的下一个更大直径（next 链），倍增维护跳跃表与容量前缀和。
// 查询与 rbook《倍增跳跃》模板同构：从大步到小步试探，能跳就跳。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 20;

int n, q;
long long D[MAXN], C[MAXN];  // 直径、容量
int nxt[MAXN];               // nxt[i]：i 下方第一个 D 更大的圆盘，0 表示水池

int up[LOG][MAXN];           // up[k][i]：沿 next 链向上 2^k 步到达的圆盘
long long sum[LOG][MAXN];    // sum[k][i]：从 i 向上 2^k 步经过圆盘的容量和（含 i，不含终点）

int stk[MAXN], stk_top;      // 单调栈

// 查询：向圆盘 r 倒入 v 体积的水，返回水停下的圆盘编号（流入水池返回 0）。
// 从大步到小步试探：跳过的 2^k 个圆盘都能装满且水还有剩余，就整段跳过去。
int fountain_query(int r, long long v) {
    int cur = r;
    long long need = v;   // 剩余还需装下的水量

    for (int k = LOG - 1; k >= 0; k--) {
        int nxt_disk = up[k][cur];
        if (nxt_disk != 0 && sum[k][cur] < need) {
            need -= sum[k][cur];   // 这段圆盘全部装满
            cur = nxt_disk;
        }
    }

    // 跳不动时只有两种可能：
    // 1. cur 装得下剩余的水（含恰好装满，因为"大于容量才溢出"）→ 停在 cur
    // 2. cur 也会装满，而它上面没有更大的圆盘 → 流入水池
    return (C[cur] >= need) ? cur : 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> D[i] >> C[i];

    // 从右往左维护 D 严格递减的单调栈，栈顶就是第一个 D 更大的圆盘
    for (int i = n; i >= 1; i--) {
        while (stk_top > 0 && D[stk[stk_top]] <= D[i]) stk_top--;
        nxt[i] = (stk_top > 0) ? stk[stk_top] : 0;
        stk[++stk_top] = i;
    }

    // 倍增表：up[0][i] = 直接父，sum[0][i] = 自己的容量
    for (int i = 1; i <= n; i++) {
        up[0][i] = nxt[i];
        sum[0][i] = C[i];
    }
    for (int k = 1; k < LOG; k++)
        for (int i = 1; i <= n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
            sum[k][i] = sum[k - 1][i] + sum[k - 1][up[k - 1][i]];
        }

    for (int t = 0; t < q; t++) {
        int r;
        long long v;
        cin >> r >> v;
        cout << fountain_query(r, v) << '\n';
    }

    return 0;
}
