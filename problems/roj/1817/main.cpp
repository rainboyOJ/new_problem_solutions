/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:35
 * update_at: 2026-10-08 06:35
 */

// 一本通 1817《染色游戏》（输入 N，随后 N-1 行边；题面写「N 行」是笔误，两组样例都只有 N-1 行）
//
// 核心恒等式：树的任意点集导出子图是森林，"连通块数 = 点数 - 边数"，于是
//   K_A - K_B = (|V_A| - |V_B|) - (|E_A| - |E_B|)。
// 记 x_i = +1 表示点 i 被 Alice 染红、-1 表示被 Bob 染蓝，d_i 为点 i 的度数，
// 逐边统计可得 |E_B| - |E_A| = -(1/2) * Σ_i d_i * x_i，而 |V_A| - |V_B| = Σ_i x_i，
// 合起来 K_A - K_B = (1/2) * Σ_i (2 - d_i) * x_i。
//
// 也就是说：每个点的贡献是独立线性的，只看它被谁抢到，权值 w_i = 2 - d_i，
// 抢的人拿 +w_i、对手拿 -w_i，而抢到一个点还等于从对手手里夺走它，双方都优先抢
// 当前权值最大的点，故答案 = (W_1 - W_2 + W_3 - W_4 + ...) / 2，W 为 w 的降序排列。
// 又 w_i = 2 - d_i，w 降序恰是 d 升序，实现里直接对度数排序。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n;            // 点数，题面上限 100000
ll deg[MAXN];    // deg[v] = 点 v 的度数；度数升序排列后其下标奇偶就是抢点的先后

int main() {
    if (scanf("%lld", &n) != 1) return 0;   // 防御性：空输入直接结束
    for (ll i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        ++deg[u];
        ++deg[v];
    }

    sort(deg + 1, deg + n + 1);             // 度数升序 <=> 权值 2-deg 降序

    ll sum = 0;                             // sum = Σ_奇数位 w - Σ_偶数位 w（此时 w 已按降序被取）
    for (ll i = 1; i <= n; ++i) {
        ll w = 2 - deg[i];                  // 升序里下标小 => 度数小 => 权值大 => Alice 先抢
        if (i & 1) sum += w;                // 奇数轮由 Alice 抢走：得 +w
        else sum -= w;                      // 偶数轮由 Bob 抢走：得 -w
    }

    // Σ_i w_i = 2n - 2(n-1) = 2 恒为偶数，任意改符号不改变奇偶性，故整除精确（负数亦然）
    printf("%lld\n", sum / 2);
    return 0;
}
