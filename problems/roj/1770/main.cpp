/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:25
 * update_at: 2026-10-08 01:25
 */
// main.cpp：跳跳棋（roj 1770）。
// 博弈模型（证明见题解）：第 i 行与第 i+1 行之间 Bob 只需考虑保留一段连续的门区间 [l, r]，
// 他靠“留着左右两端的门、Alice 一迈步就封掉她那一侧的临时门”逼 Alice 在该行里扫荡一遍。
// 站在 (i,j) 的 Alice 只有三种结局：
//   * 区间退化成 [j,j]：直接下楼，付 cost[j]；
//   * 右门就是 j（l<=j==r）：只能一路向左扫到 l 再从 l 下楼，付 (pre[j-1]-pre[l-1]) + cost[l]；
//   * 左门就是 j（l==j<=r）：只能一路向右扫到 r 再从 r 下楼，付 (pre[r]-pre[j]) + cost[r]；
//   * 两门夹住 j（l<j<r）：先往左扫到 l 再折返到 r 下楼，或先往右扫到 r 再折返到 l 下楼，
//     Alice 取较省的一侧：min(v1, v2)。其中
//        v1 = (pre[j-1]-pre[l-1]) + (pre[r]-pre[l]) + cost[r]   （向左扫到底再折返，从 r 下楼）
//        v2 = (pre[r]-pre[j])     + (pre[r-1]-pre[l-1]) + cost[l]（向右扫到底再折返，从 l 下楼）
// Bob 取使 Alice 代价最大的区间，故 f[i][j] = max_{l<=j<=r} V(l,r,j)。
// 自下而上倒推，最后 Alice 在第 1 行挑最优起点：ans = min_j (a[1][j] + f[1][j])。
// 注意 n = 1 时 Alice 一开始就站在第 n 行，答案直接是第 1 行的最小值。
// 本文件是最直白的 O(n*m^3) 三重循环写法；main.py 用同一模型但压到 O(n*m^2*log m)。
// 复杂度：T=10、n=m=100 时约 1.7e8 次简单运算，实测 0.13 s（限时 3000 ms）。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105; // 题面上限 n, m <= 100，留一点安全余量

int n, m;          // 棋盘行数、列数
ll a[MAXN][MAXN];  // a[i][j]：第 i 行第 j 列格子上的数字
ll f[MAXN][MAXN];  // f[i][j]：Alice 站在 (i,j)（该格已付）后，到第 n 行还需付的最小罚分
ll pre[MAXN];      // 本行的前缀和，pre[k] = a[i][1] + ... + a[i][k]
ll cost[MAXN];     // cost[c] = a[i+1][c] + f[i+1][c]：在 (i,c) 下楼的总代价

// 处理一组数据并输出答案
void solve_case() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }

    if (n == 1) { // Alice 一开始已经在第 n 行，游戏立刻结束
        ll ans = a[1][1];
        for (int j = 2; j <= m; j++) {
            ans = min(ans, a[1][j]);
        }
        printf("%lld\n", ans);
        return;
    }

    for (int j = 1; j <= m; j++) { // 第 n 行不用再往下走
        f[n][j] = 0;
    }

    for (int i = n - 1; i >= 1; i--) { // 自下而上倒推
        pre[0] = 0;
        for (int k = 1; k <= m; k++) {
            pre[k] = pre[k - 1] + a[i][k];
        }
        for (int c = 1; c <= m; c++) {
            cost[c] = a[i + 1][c] + f[i + 1][c];
        }

        for (int j = 1; j <= m; j++) {
            ll best = cost[j]; // 区间 [j,j]：Bob 只留 j 这一列的门，Alice 直接下楼

            for (int l = 1; l <= j - 1; l++) { // 右门就是 j，只能向左扫
                best = max(best, (pre[j - 1] - pre[l - 1]) + cost[l]);
            }
            for (int r = j + 1; r <= m; r++) { // 左门就是 j，只能向右扫
                best = max(best, (pre[r] - pre[j]) + cost[r]);
            }
            for (int l = 1; l <= j - 1; l++) { // 两门夹住 j，Alice 挑较省的一侧
                for (int r = j + 1; r <= m; r++) {
                    ll go_left = (pre[j - 1] - pre[l - 1]) + (pre[r] - pre[l]) + cost[r];
                    ll go_right = (pre[r] - pre[j]) + (pre[r - 1] - pre[l - 1]) + cost[l];
                    best = max(best, min(go_left, go_right));
                }
            }
            f[i][j] = best;
        }
    }

    ll ans = a[1][1] + f[1][1]; // Alice 在第 1 行挑一个起点
    for (int j = 2; j <= m; j++) {
        ans = min(ans, a[1][j] + f[1][j]);
    }
    printf("%lld\n", ans);
}

int main() {
    int T; // 数据组数
    if (scanf("%d", &T) != 1) {
        return 0;
    }
    while (T--) {
        solve_case();
    }
    return 0;
}
