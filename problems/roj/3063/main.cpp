/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:13
 * update_at: 2026-10-06 17:14
 */
// 生日蛋糕：自底向上 DFS 枚举每层的 (R, H)，三条下界剪枝，求最小外表面积 S。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 25;

ll n;              // 蛋糕体积为 n*pi
ll m;              // 蛋糕层数
ll min_v[MAXM];    // min_v[left]：再放 left 层所需体积的绝对下界 sum(j^3)
ll min_s[MAXM];    // min_s[left]：再放 left 层侧面积的绝对下界 sum(2*j^2)
ll best;           // 当前最优答案 S；3n+1 当无解哨兵（任何可行方案 S <= 3n）

// 自底向上第 j 层半径、高度至少为 j（严格递减 + 正整数），
// 由此得到剩余 left 层的体积 / 侧面积下界前缀和。
void init_min() {
    min_v[0] = 0;
    min_s[0] = 0;
    for (ll j = 1; j <= m; j++) {
        min_v[j] = min_v[j - 1] + j * j * j;
        min_s[j] = min_s[j - 1] + 2 * j * j;
    }
}

// 已放好 level-1 层，占用体积 vol、侧面积 area（不含底面），
// 下一层的半径上界 r_max、高度上界 h_max。
// left = 含本层在内还要放的层数，rest = 还要填的体积。
void dfs(ll level, ll vol, ll area, ll r_max, ll h_max) {
    ll left = m - level + 1;
    ll rest = n - vol;

    // 剪枝一：剩余层即使全取最小尺寸，侧面积也追不上 best
    if (area + min_s[left] >= best) return;
    // 剪枝二：剩余体积摊成半径 r_max 的柱体侧面积最小，为 2*rest/r_max；
    // 通分成乘法，避免除法与浮点误差
    if (area * r_max + 2 * rest >= best * r_max) return;

    // 最后一层：体积必须整除 r^2，高度由除法唯一确定，不必再递归
    if (left == 1) {
        for (ll r = r_max; r >= 1; r--) {
            ll square = r * r;
            if (rest % square != 0) continue;
            ll h = rest / square;
            if (h > h_max) continue;
            ll area_now = area + 2 * r * h;
            if (level == 1) area_now += square; // 最底层顶面计入 S
            if (area_now < best) best = area_now;
        }
        return;
    }

    // 半径从大到小枚举：大体积分支先试，更快压小 best；本层半径至少 left
    for (ll r = r_max; r >= left; r--) {
        ll square = r * r;
        ll base = area;
        if (level == 1) base += square; // 顶面积只在最底层计入
        // 与剪枝二同理，先在半径维度上砍掉
        if (base * r + 2 * rest >= best * r) continue;

        // 本层高度还要给上面 left-1 层留出 min_v[left-1] 的体积
        ll h_top = min(h_max, (rest - min_v[left - 1]) / square);
        for (ll h = h_top; h >= left; h--) {
            ll area_now = base + 2 * r * h;
            // 本层定下后重新估一次侧面积下界
            if (area_now + min_s[left - 1] >= best) continue;
            dfs(level + 1, vol + square * h, area_now, r - 1, h - 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_min();
    if (min_v[m] > n) { // 连最省体积的 1,2,...,m 层都放不下，直接无解
        cout << 0 << endl;
        return 0;
    }

    // 任何可行方案 S <= 3n（2R_iH_i <= 2R_i^2H_i，R_1^2 <= R_1^2H_1），
    // 取 3n+1 当无解哨兵，同时是剪枝的初始上界
    best = 3 * n + 1;
    // 第 1 层半径至多 sqrt(n)（体积约束），高度至多 n
    dfs(1, 0, 0, (ll)sqrt((double)n), n);

    if (best == 3 * n + 1) cout << 0 << endl;
    else cout << best << endl;

    return 0;
}
