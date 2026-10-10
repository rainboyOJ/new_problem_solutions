/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:58
 * update_at: 2026-10-07 18:58
 */
// 一本通 1727《魔棒》：二分答案 cd + O(n^2) 可行性 DP
//
// 状态：处理完第 i 秒的伤害后，记 (是否释放过魔杖, 当前能量点数) -> 最大生命值。
//   · 从未释放：能量点数恒等于 i，只有一条确定的状态链，用一个变量 never 记录；
//   · 释放过一次及以上：能量点数 j 就是"距上次释放的秒数"，用 dp[j] 记录。
//     首次释放不受间隔限制，此后每次释放都要求 j >= cd，所以两种"释放过"的状态
//     对未来的约束完全相同，可以合并成一个。
// 转移前必须判断 受伤后 hp>0：题面说任何时刻 hp<=0 即死亡，来不及释放回血。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

static const ll NEG = -(1LL << 60);   // 不可达状态：比任何合法生命值都小

static const int MAXN = 505;

static int n;
static ll hp;
static ll a[MAXN];

static ll dp[MAXN];    // 上一秒：释放过，dp[j] = 能量点数为 j 时的最大生命值
static ll nxt[MAXN];   // 本秒
static ll never;       // 从未释放过时的生命值（此链上能量点数恰为当前秒数）

// 判断施法间隔放宽到 cd 时英雄能否活过第 n 秒
static bool can_survive(ll cd) {
    never = hp;
    for (int j = 0; j <= n; j++) dp[j] = NEG;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) nxt[j] = NEG;

        // 来源一：从未释放过。能量点数恰为 i，本秒可选择"第一次释放"（无 cd 限制）
        if (never > a[i]) {
            ll rest = never - a[i];          // 受伤后仍活着，才谈得上释放
            never = rest;                    // 不释放：能量继续累积
            nxt[0] = rest + 15LL * i;        // 释放：回 15*i 点，能量清零
        } else {
            never = NEG;                     // 这条链已经死亡，之后再无来源
        }

        // 来源二：此前已经释放过，上一秒能量点数 j（本秒变为 j+1）
        for (int j = 0; j <= i - 1; j++) {
            if (dp[j] <= a[i]) continue;     // 受伤瞬间 hp<=0，直接死亡
            ll rest = dp[j] - a[i];
            ll energy = j + 1;               // 本秒又攒了一点能量
            if (rest > nxt[energy]) nxt[energy] = rest;              // 不释放
            if (energy >= cd) {              // 距上次释放至少 cd 秒才允许再释放
                ll heal = rest + 15LL * energy;
                if (heal > nxt[0]) nxt[0] = heal;
            }
        }

        for (int j = 0; j <= n; j++) dp[j] = nxt[j];
    }

    if (never > 0) return true;
    for (int j = 0; j <= n; j++)
        if (dp[j] > 0) return true;
    return false;
}

int main() {
    if (scanf("%d %lld", &n, &hp) != 2) return 0;
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);

    // cd 越大越难存活，可行区间是前缀 [1, best]；cd > n 时至多释放一次，与 cd 无关
    if (!can_survive(1)) { printf("-1\n"); return 0; }
    if (can_survive(n + 1)) { printf("No upper bound.\n"); return 0; }

    ll lo = 1, hi = n, best = 1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (can_survive(mid)) { best = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    printf("%lld\n", best);
    return 0;
}
