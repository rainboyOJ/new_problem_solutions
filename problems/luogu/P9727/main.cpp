/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 16:55
 */
// P9727 [EC Final 2022] Aqre
//
// 目标：填 0/1，不能有 4 个连续的同号（横竖都不行），1 必须四连通，且 1 尽量多
// （等价于 0 尽量少）。答案要输出最多的 1 的个数和任意一个合法矩阵。
//
// 【下界】把盘面按 (i+j) mod 4 分成 4 类。任意一个 1x4 的横条或竖条都恰好包含
// 4 个类各一个，所以它内部至少有 1 个 0。于是只要能放 t 个互不相交的 1x4，
// 就有 至少 t 个 0。再注意到同一类里任意两个格子之间的曼哈顿距离都是 4 的倍数，
// 不可能落在同一个 1x4 条里（1x4 条要求 4 个格子连续且刚好 4 长），
// 所以「某一类全取成 0」本身就是一个可行解，代价是该类的大小。
//
// 【结论】最少 0 的个数 z 为：
//   n,m <= 3          : z = 0
//   min = 2, max = b  : z = b / 2
//   min = 3, max = b  : z = 3 * (b / 4) + (b % 4 >= 2 ? 1 : 0)
//   n,m >= 4          : z = n*m/4 - (n%4==2 && m%4==2 ? 1 : 0)
// 其中 n,m >= 4 的情形，n*m/4 恰好等于 (i+j) mod 4 四类中最小类的大小（见下），
// n%4==2 且 m%4==2 时可以比「某一类全 0」再多省一个（多出来的那个 0 来自
// 每行/每列的 4 周期结构正好让两个相邻行错开，从而四类各少一个）。
//
// 【构造】对 n,m >= 4，用「按 4 行循环」的周期结构：
//   第 i 行的 0 只出现在满足 j % 4 == p[i % 4] 的那些列，p 是 0..3 的排列。
// 这样一个 4x4 的周期块里每行每列各有 1 个 0，每类 (i+j)%4 也各有 1 个 0，
// 于是 0 的总数正好等于「若 n,m 都是 4 的倍数」时为 n*m/4 ；
// 当 n,m 不是 4 的倍数时，多出来的那些行/列会按 p 的值把某个类多算几次，
// 只要选对排列 p，总数就正好等于上面的公式，并且连通性也成立。
// 不同 (n%4, m%4) 需要不同的 p，共 16 种情况，直接查表（表由程序离线穷举
// 所有 4! = 24 个排列、逐个验证公式与连通性得到，见 verify 脚本）。
//
// 对 min(n,m) <= 3 的小情形：先把短边方向当作「行数 a = min(n,m)」按
// a x b 构造（a = 2 用周期 [1,3]，a = 3 用周期 [1,3,3]），
// 若原始 n > m 再转置回来。n,m <= 3 时全填 1 即可。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int g[MAXN][MAXN]; // 0/1 矩阵

// TAB[n%4][m%4]：n,m >= 4 时第 i 行的 0 所在列满足 j%4 == TAB[n%4][m%4][i%4]
static const int TAB[4][4][4] = {
    {{0, 2, 1, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 1, 3, 2}},
    {{0, 1, 3, 2}, {1, 2, 0, 3}, {2, 0, 1, 3}, {3, 0, 2, 1}},
    {{0, 2, 1, 3}, {1, 2, 0, 3}, {2, 3, 1, 0}, {0, 3, 1, 2}},
    {{0, 1, 3, 2}, {1, 3, 2, 0}, {0, 2, 3, 1}, {0, 1, 3, 2}},
};

// 最少 0 的个数
long long min_zeros(int nn, int mm) {
    if (nn <= 3 && mm <= 3) return 0;
    int a = nn < mm ? nn : mm;
    int b = nn < mm ? mm : nn;
    if (a == 2) return b / 2;
    if (a == 3) return 3LL * (b / 4) + (b % 4 >= 2 ? 1 : 0);
    long long res = (long long)nn * mm / 4;
    if (nn % 4 == 2 && mm % 4 == 2) res -= 1;
    return res;
}

// 把 a x b（a <= 3）按行周期 q 填进 g，need_trans 表示最终要转置回来
void build_small(int a, int b, const int *q, int qlen, bool need_trans) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            int v = (j % 4 == q[i % qlen]) ? 0 : 1;
            if (need_trans) g[j][i] = v;
            else g[i][j] = v;
        }
    }
}

void solve() {
    if (n <= 3 && m <= 3) {
        // 格子太少，全填 1 一定合法（不可能出现 4 个连续）
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) g[i][j] = 1;
        return;
    }

    int a = n < m ? n : m;
    int b = n < m ? m : n;
    if (a <= 3) {
        bool need_trans = (n != a);
        if (a == 2) {
            int q[2] = {1, 3};
            build_small(a, b, q, 2, need_trans);
        } else {
            int q[3] = {1, 3, 3};
            build_small(a, b, q, 3, need_trans);
        }
        return;
    }

    const int *p = TAB[n % 4][m % 4];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) g[i][j] = (j % 4 == p[i % 4]) ? 0 : 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        solve();
        long long zeros = min_zeros(n, m);
        cout << (long long)n * m - zeros << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << g[i][j];
            cout << '\n';
        }
    }
    return 0;
}
