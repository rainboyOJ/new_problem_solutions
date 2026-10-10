/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 分级：把序列改成非降（或非升）的最小代价，台阶高度只取序列中出现过的值。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

// 把 seq 改成非降序列的最小代价，values 是允许使用的台阶高度（升序去重）
ll level_cost(std::vector<ll>& seq, std::vector<ll>& values) {
    ll m = (ll)values.size();
    std::vector<ll> dp(m, 0); // 未处理任何元素时取任何结尾都不花钱
    std::vector<ll> ndp(m, 0);
    for (size_t t = 0; t < seq.size(); t++) {
        ll a = seq[t];
        ll running = dp[0]; // 结尾不超过 values[j] 的最优前缀
        for (ll j = 0; j < m; j++) {
            if (dp[j] < running) running = dp[j];
            ll d = a - values[j];
            if (d < 0) d = -d;
            ndp[j] = d + running;
        }
        dp = ndp;
    }
    ll best = dp[0];
    for (ll j = 1; j < m; j++) {
        if (dp[j] < best) best = dp[j];
    }
    return best;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    std::vector<ll> seq(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &seq[i]);
    }
    std::vector<ll> values = seq;
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    ll best_nondecreasing = level_cost(seq, values);
    std::vector<ll> rev(seq.rbegin(), seq.rend()); // 倒过来做非降 = 原序列非升
    ll best_nonincreasing = level_cost(rev, values);
    printf("%lld\n", best_nondecreasing < best_nonincreasing ? best_nondecreasing : best_nonincreasing);
    return 0;
}
