/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 20:04
 * update_at: 2026-10-08 20:04
 */
// 一本通 1677《软件开发》/ roj 5013：二分答案 + 可行性背包 DP
//
// 题意：n 个技术人员，两个软件各 m 个模块。第 i 人做软件 1 一个模块要 d1[i] 天，
//   做软件 2 一个模块要 d2[i] 天；同一时刻只能做一个模块，模块不可拆分、也不能
//   多人协作，但做完一个模块后可随意转到任一软件的任一模块。求两个软件都交付的
//   最少天数。
//
// 判定模型：给定天数 D，"能完成"的充要条件是存在一组分配——第 i 人分到软件 1
//   的 k_i 个模块、软件 2 的 l_i 个模块，满足 sum(k_i) >= m、sum(l_i) >= m，
//   且每人 k_i*d1[i] + l_i*d2[i] <= D（先做软件 1 后做软件 2 只影响顺序，
//   总耗时就是两天数之和）。同一个人同时只干一个模块，所以按人把时间切成两段即可。
//   多做模块只会更费时，所以最优解里 sum(k_i) = sum(l_i) = m。
//
// 做法：天数单调（D 天能完成则 D+1 天也能），二分答案 D，再用背包判定：
//   dp[j] = 考虑到当前人为止、软件 1 恰好完成 j 个模块时，软件 2 最多完成的模块数；
//   j = m 表示 "> = m"，因为软件 1 多做模块没有意义，统一截断到 m。
//   第 i 人枚举自己做软件 1 的模块数 k（0 <= k <= min(m, D/d1[i])），剩下
//   D - k*d1[i] 天全做软件 2，能做 (D - k*d1[i]) / d2[i] 个。
//   最后 dp[m] >= m 即 D 天可行。
//   复杂度 O(log(2*m*max_d) * n * m^2) <= 15 * 100 * 100 * 100 = 1.5e7。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

struct Tech {
    ll d1; // 完成软件 1 一个模块所需天数
    ll d2; // 完成软件 2 一个模块所需天数
};
Tech tech[MAXN]; // 技术人员，下标 1..n 与题面一致

ll n, m;
ll dp[MAXN];  // dp[j]：软件 1 排满 j 个模块时，软件 2 最多能做的模块数（-1 表示排不出）
ll ndp[MAXN]; // 加入当前人员后的新状态

// 判断能否在 days 天内完成两个软件各 m 个模块。
bool feasible(ll days) {
    for (ll j = 1; j <= m; j++) dp[j] = -1;
    dp[0] = 0;
    for (ll i = 1; i <= n; i++) {
        ll kmax = days / tech[i].d1; // 这个人最多能承担多少个软件 1 的模块
        if (kmax > m) kmax = m;
        for (ll j = 0; j <= m; j++) ndp[j] = -1;
        for (ll j = 0; j <= m; j++) {
            if (dp[j] < 0) continue; // 软件 1 排出 j 个的状态不可达
            for (ll k = 0; k <= kmax; k++) {
                ll j2 = j + k;
                if (j2 > m) j2 = m; // 软件 1 超过 m 个模块没有意义，截断到 m
                // 先做 k 个软件 1 的模块，余下时间全做软件 2
                ll done2 = dp[j] + (days - k * tech[i].d1) / tech[i].d2;
                if (done2 > ndp[j2]) ndp[j2] = done2;
            }
        }
        for (ll j = 0; j <= m; j++) dp[j] = ndp[j];
    }
    return dp[m] >= m;
}

void solve() {
    cin >> n >> m;
    ll max_d = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> tech[i].d1 >> tech[i].d2;
        max_d = max(max_d, max(tech[i].d1, tech[i].d2));
    }
    // 上界：让某一人独自做完两个软件的全部 2m 个模块，需 m*(d1+d2) <= 2*m*max_d 天，
    // 故该值必然可行，可作为二分的右端。
    ll lo = 0, hi = 2 * m * max_d, ans = hi;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (feasible(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
