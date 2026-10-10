/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 15:08
 * update_at: 2026-10-08 15:08
 */
// 一本通 1676《手机游戏》/ roj 5012：二分答案 + 从右向左贪心 + 滑动窗口三项和
//
// 题意：n 个怪物排成一行，第 i 个血量为 m_i。射出 k 个伤害均为 p 的火球，
//   火球打在位置 i 时对该位置造成 p 点伤害，并对左侧第 j 个怪物（j <= i）
//   造成 max(0, p - (i-j)^2) 点溅射伤害。血液变负即死亡（即累计伤害 >= m_i + 1），
//   求能消灭全部怪物的最小 p。
//
// 做法：p 越大越容易成功，故对答案二分，check(p) 求清场所需的最少火球数：
//   火球只向左溅射，从右往左处理。轮位置 i 时，右侧已放置的火球对 i 的溅射伤害
//   记为 S；若 S < m_i + 1，缺少的伤害只能在 i 或更左补，而砸在 i 自身
//   （伤害最高、向左溅射也最远）严格不劣，故在 i 处补 ceil((m_i+1-S)/p) 个火球。
//   S 用滑动窗口 + 三项和 O(1) 维护：设 cnt[j] 为位置 j 的火球数，
//   R = floor(sqrt(p-1)) 是溅射严格大于 0 的最远距离，则 j 落在 [i+1, i+R] 时
//     S = sum cnt[j]*(p - (j-i)^2)
//       = (p - i^2)*sumCnt + 2*i*sumJ - sumJ2
//   其中 sumCnt/sumJ/sumJ2 是窗口内 cnt[j]、cnt[j]*j、cnt[j]*j*j 的和。
//   总复杂度 O(n log(max(m) + n^2))。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 50000 + 5;

ll n;            // 怪物个数
ll k;            // 火球数量上限
ll m[MAXN];      // m[i]：第 i 个怪物的血量（0 下标）
ll cnt[MAXN];    // cnt[i]：check 中贪心决定砸在位置 i 的火球数

// 整数开方：返回 floor(sqrt(x))，x >= 0。sqrtl 只做初值估计，再用循环夹逼到精确值。
ll isqrt(ll x) {
    if (x <= 0) return 0;
    long double approx = sqrtl((long double)x);
    ll r = approx; // 浮点估计可能有 1 的误差，下面两个循环修正
    while ((r + 1) * (r + 1) <= x) r++;
    while (r * r > x) r--;
    return r;
}

// 判断伤害 p 能否用不超过 k 个火球消灭所有怪物。
// 返回 false 时只保证"所需火球数 > k"，不需要给出具体数量。
bool check(ll p) {
    ll R = isqrt(p - 1); // 溅射伤害 > 0 的最远距离；p = 1 时 R = 0
    ll sumCnt = 0;       // 窗口内 cnt[j] 之和
    ll sumJ = 0;         // 窗口内 cnt[j] * j 之和
    ll sumJ2 = 0;        // 窗口内 cnt[j] * j * j 之和
    ll total = 0;        // 已用火球总数

    for (ll i = n - 1; i >= 0; i--) {
        // 当前窗口是右侧距离 <= R 的火球来源，即 [i+1, i+R]
        ll splash = (p - i * i) * sumCnt + 2 * i * sumJ - sumJ2;

        ll need = m[i] + 1 - splash; // 还差多少伤害（血量必须 < 0）
        ll c = 0;
        if (need > 0) {
            c = (need + p - 1) / p; // ceil(need / p)
            total += c;
            if (total > k) return false;
        }
        cnt[i] = c;

        // R == 0 时溅射半径为 0（p = 1），左侧怪物吃不到任何伤害，窗口恒为空：
        // 此时既不能弹出也不能加入，否则 p = 1 会被误判成不可行。
        if (R >= 1) {
            // 窗口从 [i+1, i+R] 移到下一位置的 [i, i-1+R]：先去掉距离恰为 R+1 的 i+R
            ll creep = i + R;
            if (creep < n) {
                sumCnt -= cnt[creep];
                sumJ -= cnt[creep] * creep;
                sumJ2 -= cnt[creep] * creep * creep;
            }
            // 再加入位置 i 的火球来源
            sumCnt += c;
            sumJ += c * i;
            sumJ2 += c * i * i;
        }
    }
    return total <= k;
}

void read_input() {
    if (!(cin >> n >> k)) return;
    for (ll i = 0; i < n; i++) {
        cin >> m[i];
    }
}

void solve() {
    ll top = 0; // 最大血量，用来定二分上界
    for (ll i = 0; i < n; i++) {
        if (m[i] > top) top = m[i];
    }

    // 上界：只在最右位置放 1 个火球，p = top+1+(n-1)^2 时它到最左怪物的溅射
    // 也有 p-(n-1)^2 = top+1 >= m_i+1，故 check(hi) 必为真。
    ll lo = 1;
    ll hi = top + 1 + (n - 1) * (n - 1);
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
