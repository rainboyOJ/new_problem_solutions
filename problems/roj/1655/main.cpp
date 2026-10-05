/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:48
 * update_at: 2026-10-06 00:48
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_SIDE = 1000; // 题面 m、n 的上界，欧拉函数表按它建一次

ll m, n;
ll phi[MAX_SIDE + 1]; // phi[t] 为欧拉函数，表示不超过 t 且与 t 互质的正整数个数

// 埃氏筛法预处理 phi[1..MAX_SIDE]。
void build_phi() {
    for (int i = 1; i <= MAX_SIDE; i++) {
        phi[i] = i;
    }
    for (int p = 2; p <= MAX_SIDE; p++) {
        if (phi[p] == p) { // 还没被更小的质数除过，说明 p 是质数
            for (int k = p; k <= MAX_SIDE; k += p) {
                phi[k] -= phi[k] / p;
            }
        }
    }
}

// 组合数 C(x, 3)：从 x 个点里任取 3 个。
ll comb3(ll x) {
    return x * (x - 1) * (x - 2) / 6;
}

// [0, total] 上的点对 (x1, x2)，满足 x1 < x2 且 x2 - x1 能被 step 整除。
// 距离取 k * step（k >= 1）时左端点有 total + 1 - k * step 种选法，对 k 求和即得。
ll count_pairs(ll total, ll step) {
    ll cnt = total / step; // 距离最大能取到 cnt * step，于是 k 只遍历 1..cnt
    return cnt * (total + 1) - step * cnt * (cnt + 1) / 2;
}

void solve() {
    ll rows = m + 1; // 每个方向上的格点数
    ll cols = n + 1;
    ll limit = min(m, n); // 位移分量超过它，另一个方向就放不下第二个点

    // 斜向共线：位移 (dx, dy) 的最大公约数为 g 时，线段中间夹着 g - 1 个格点，
    // 也就是以这两点为端点的共线三点组数。由 Σ_{t | g} φ(t) = g 得
    // g - 1 = Σ_{t | g, t >= 2} φ(t)，交换求和次序后第 t 层只要数横纵坐标差
    // 都被 t 整除的点对数，两者相乘再按 φ(t) 加权即可。
    ll slanted = 0;
    for (ll t = 2; t <= limit; t++) {
        ll pairs_x = count_pairs(m, t);
        ll pairs_y = count_pairs(n, t);
        slanted += phi[t] * pairs_x * pairs_y;
    }
    slanted *= 2; // dy 可正可负，右下与右上两种方向对称

    // 水平共线：每条水平格线上任取 3 点；垂直同理。
    ll axis_aligned = cols * comb3(rows) + rows * comb3(cols);

    // 补集计数：全部三点组减去共线三点组。
    ll total = comb3(rows * cols);
    cout << total - axis_aligned - slanted << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    build_phi();
    solve();

    return 0;
}
