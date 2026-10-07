/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:08
 * update_at: 2026-10-07 18:12
 */

// 一本通 1717《负环》
// 题意：n 个点 m 条边、无重边无自环的带权有向图，求点数最少的负环含几个点；没有负环输出 0。
//
// 做法：倍增 Floyd（min-plus 矩阵幂）+ 按位贪心，O(n^3 log n)。
//   设 pw[k][i][j] = 从 i 到 j、最多用 2^k 条边的最小权值和（允许停在原地，即主对角线为 0）。
//   于是 pw[0] 是邻接矩阵（对角线改成 0），pw[k] = pw[k-1] (x) pw[k-1]，
//   其中 (x) 是 min-plus 乘法，也就是把“前半段 + 后半段”拼起来取最小值。
//   负环一定以简单环形式出现，最长不超过 n <= 300 条边，所以 9 个二进制位（最大 511 条边）够用。
//   按位从高到低贪心：cur 表示“最多 tot 条边”的最短路矩阵，
//   若 cur (x) pw[k] 的主对角线全非负（说明不存在 <= tot + 2^k 条边的负权闭迹），
//   就接受这一位：cur = cur (x) pw[k]，tot += 2^k；否则跳过。
//   循环结束时再乘一次 pw[0]（一条边）：主对角线出现负数就说明最小负环长度是 tot + 1，否则输出 0。
//
// 关键点：
//   - “存在负权闭迹”等价于“存在负环”（闭迹删掉非负的子回路后必然剩下负环），
//     所以答案就是“存在 <= L 条边的负权闭迹”里最小的那个 L。
//   - 主对角线恒 <= 0，于是所有矩阵元素 <= INF，且真实路径权值绝对值 <= 511 * 10^4 < INF。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;     // 点数上限 300，多开几格防越界
const int MAXB = 8;       // 倍增层数：2^8 = 256，配合按位贪心可表示 0..511 条边
const ll INF = 1000000000000000LL;  // 远大于任何真实路径权值，且两个 INF 相加也不会溢出

int n, m;                     // n 点数，m 边数
ll pw[MAXB + 1][MAXN][MAXN];  // pw[k][i][j]：i 到 j 最多用 2^k 条边的最小权值和
ll cur[MAXN][MAXN];           // 至多 tot 条边的最小权值和矩阵
ll nxt[MAXN][MAXN];           // 一次乘法后的临时结果

// out = a (x) b：min-plus 乘法，含义是“先走 a 的一段、再走 b 的一段”
void mul(const ll a[][MAXN], const ll b[][MAXN], ll out[][MAXN])
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) out[i][j] = INF;
        for (int k = 0; k < n; ++k) {
            if (a[i][k] >= INF) continue;  // 不可达的中间点直接跳过，省一半时间
            for (int j = 0; j < n; ++j) {
                if (b[k][j] >= INF) continue;  // 后半段不可达，不能拿 INF 减权值凑出假路径
                ll v = a[i][k] + b[k][j];
                if (v < out[i][j]) out[i][j] = v;
            }
        }
    }
}

// 主对角线上是否有负数：有就说明存在负权闭迹（等价于存在负环）
bool has_neg_diag(const ll a[][MAXN])
{
    for (int i = 0; i < n; ++i)
        if (a[i][i] < 0) return true;
    return false;
}

int main()
{
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // pw[0]：一条边（或原地不动，权值 0）
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) pw[0][i][j] = INF;
    for (int i = 0; i < n; ++i) pw[0][i][i] = 0;
    for (int e = 0; e < m; ++e) {
        int u, v;
        ll w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) return 0;
        --u;
        --v;
        if (w < pw[0][u][v]) pw[0][u][v] = w;  // 题面保证无重边，这里只作防御
    }

    // 倍增预处理：pw[k] = pw[k-1] 走两遍
    for (int k = 1; k <= MAXB; ++k) mul(pw[k - 1], pw[k - 1], pw[k]);

    // cur 初值 = “至多 0 条边” = 单位矩阵（只能原地不动）
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cur[i][j] = (i == j ? 0 : INF);

    int tot = 0;  // 已经确认“不存在 <= tot 条边的负环”
    for (int k = MAXB; k >= 0; --k) {
        mul(cur, pw[k], nxt);
        if (!has_neg_diag(nxt)) {  // 这一段可以安全接受
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) cur[i][j] = nxt[i][j];
            tot += 1 << k;
        }
    }

    mul(cur, pw[0], nxt);
    printf("%d\n", has_neg_diag(nxt) ? tot + 1 : 0);
    return 0;
}
