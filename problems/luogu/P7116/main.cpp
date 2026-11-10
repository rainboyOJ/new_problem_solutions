/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:15
 * update_at: 2026-11-10 23:25
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int MAXN = 500005;
const int MAXK = 15;

int n, k;
ll w[MAXK];
int c[MAXN], d[MAXN];

// 各维度在每一步的极值变化
ll pos[MAXK], mn[MAXK], mx[MAXK];
// 每一整轮各维度的有效缩减量
ll e[MAXK];
// 记录各维度的当前剩余区间长度
ll cur_len[MAXK];

// 拉格朗日插值求自然数幂前缀和 sum_{r=0}^{m} r^p
ll power_sum[MAXK];

ll qpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 连续自然数幂求和：sum_{i=0}^{m} i^p
ll calc_sum(ll m, int p) {
    if (m < 0) return 0;
    if (m == 0) return (p == 0 ? 1 : 0);
    int num_points = p + 2;
    if (m < num_points) {
        ll s = 0;
        for (ll i = 0; i <= m; ++i) {
            s = (s + qpow(i, p)) % MOD;
        }
        return s;
    }

    vector<ll> y(num_points);
    ll cur_s = 0;
    for (int i = 0; i < num_points; ++i) {
        cur_s = (cur_s + qpow(i, p)) % MOD;
        y[i] = cur_s;
    }

    vector<ll> pre(num_points), suf(num_points);
    pre[0] = (m - 0) % MOD;
    for (int i = 1; i < num_points; ++i) {
        pre[i] = pre[i - 1] * ((m - i) % MOD) % MOD;
    }
    suf[num_points - 1] = (m - (num_points - 1)) % MOD;
    for (int i = num_points - 2; i >= 0; --i) {
        suf[i] = suf[i + 1] * ((m - i) % MOD) % MOD;
    }

    vector<ll> fact(num_points);
    fact[0] = 1;
    for (int i = 1; i < num_points; ++i) fact[i] = fact[i - 1] * i % MOD;

    ll ans = 0;
    for (int i = 0; i < num_points; ++i) {
        ll num = 1;
        if (i > 0) num = num * pre[i - 1] % MOD;
        if (i + 1 < num_points) num = num * suf[i + 1] % MOD;

        ll den = fact[i] * fact[num_points - 1 - i] % MOD;
        if ((num_points - 1 - i) % 2 == 1) {
            den = (MOD - den) % MOD;
        }
        ll term = y[i] * num % MOD * qpow(den, MOD - 2) % MOD;
        ans = (ans + term) % MOD;
    }
    return (ans % MOD + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;

    ll total_points = 1;
    for (int i = 1; i <= k; ++i) {
        cin >> w[i];
        total_points = total_points * (w[i] % MOD) % MOD;
        cur_len[i] = w[i];
    }

    for (int i = 1; i <= n; ++i) {
        cin >> c[i] >> d[i];
    }

    ll ans = total_points; // 0 步时贡献

    // 第一轮模拟
    for (int i = 1; i <= n; ++i) {
        int dim = c[i];
        pos[dim] += d[i];
        if (pos[dim] < mn[dim]) mn[dim] = pos[dim];
        if (pos[dim] > mx[dim]) mx[dim] = pos[dim];

        cur_len[dim] = w[dim] - (mx[dim] - mn[dim]);
        if (cur_len[dim] <= 0) {
            cout << ans << "\n";
            return 0;
        }

        ll prod = 1;
        for (int j = 1; j <= k; ++j) {
            prod = prod * (cur_len[j] % MOD) % MOD;
        }
        ans = (ans + prod) % MOD;
    }

    // 第二轮模拟以获取每一维一整轮的净缩减量 e[j]
    for (int i = 1; i <= n; ++i) {
        int dim = c[i];
        pos[dim] += d[i];
        if (pos[dim] < mn[dim]) {
            mn[dim] = pos[dim];
            e[dim]++;
        }
        if (pos[dim] > mx[dim]) {
            mx[dim] = pos[dim];
            e[dim]++;
        }
    }

    // 检查是否无限循环（所有 e[dim] == 0）
    bool all_zero = true;
    for (int i = 1; i <= k; ++i) {
        if (e[i] > 0) all_zero = false;
    }
    if (all_zero) {
        cout << -1 << "\n";
        return 0;
    }

    // 计算安全的最大整轮数 R
    // 注意：在进入第 2 轮之前，当前第 1 轮末各维度剩余长度为 w[j] - (mx[j] - mn[j] - e[j])
    ll base_len[MAXK];
    for (int i = 1; i <= k; ++i) {
        base_len[i] = w[i] - (mx[i] - mn[i] - e[i]);
    }

    // 每一维在完整走一轮中的最大内部缩减可能等于 e[i]，为保安全 R 留出至少 2 轮余量
    ll R = 1e18;
    for (int i = 1; i <= k; ++i) {
        if (e[i] > 0) {
            ll can_rounds = base_len[i] / e[i];
            if (can_rounds >= 2) {
                R = min(R, can_rounds - 2);
            } else {
                R = 0;
            }
        }
    }

    // 恢复状态到第 1 轮末尾
    for (int i = 1; i <= k; ++i) {
        mx[i] -= e[i]; // 简化的回退（用重置更稳）
    }
    // 重新从第 1 轮末尾的精确位置和极值重跑第 2 轮的相对变化
    // 为了万无一失，直接重算第 1 轮状态：
    for (int i = 1; i <= k; ++i) {
        pos[i] = 0;
        mn[i] = 0;
        mx[i] = 0;
        cur_len[i] = w[i];
    }
    for (int i = 1; i <= n; ++i) {
        int dim = c[i];
        pos[dim] += d[i];
        if (pos[dim] < mn[dim]) mn[dim] = pos[dim];
        if (pos[dim] > mx[dim]) mx[dim] = pos[dim];
        cur_len[dim] = w[dim] - (mx[dim] - mn[dim]);
    }

    if (R > 0) {
        for (int p = 0; p <= k; ++p) {
            power_sum[p] = calc_sum(R - 1, p);
        }

        // 扫描第 2 轮的每一步，基准函数为在第 r 轮（r 从 0 到 R-1，对应第 2 轮到第 R+1 轮）
        for (int i = 1; i <= n; ++i) {
            int dim = c[i];
            pos[dim] += d[i];
            if (pos[dim] < mn[dim]) {
                mn[dim] = pos[dim];
                cur_len[dim]--;
            }
            if (pos[dim] > mx[dim]) {
                mx[dim] = pos[dim];
                cur_len[dim]--;
            }

            // 多项式展开 prod_{j=1}^k (cur_len[j] - r * e[j])
            vector<ll> poly(k + 1, 0);
            poly[0] = 1;
            int cur_deg = 0;
            for (int j = 1; j <= k; ++j) {
                ll c0 = cur_len[j] % MOD;
                ll c1 = (MOD - (e[j] % MOD)) % MOD;
                vector<ll> next_poly(k + 1, 0);
                for (int d = 0; d <= cur_deg; ++d) {
                    if (poly[d] == 0) continue;
                    next_poly[d] = (next_poly[d] + poly[d] * c0) % MOD;
                    if (d + 1 <= k) {
                        next_poly[d + 1] = (next_poly[d + 1] + poly[d] * c1) % MOD;
                    }
                }
                cur_deg = min(k, cur_deg + 1);
                poly = next_poly;
            }

            ll step_sum = 0;
            for (int p = 0; p <= k; ++p) {
                step_sum = (step_sum + poly[p] * power_sum[p]) % MOD;
            }
            ans = (ans + step_sum) % MOD;
        }

        // 将状态快进 R 轮
        for (int i = 1; i <= k; ++i) {
            cur_len[i] -= (R - 1) * e[i];
        }
    }

    // 剩余轮单步模拟直至全部出界
    while (true) {
        bool finished = false;
        for (int i = 1; i <= n; ++i) {
            int dim = c[i];
            pos[dim] += d[i];
            if (pos[dim] < mn[dim]) {
                mn[dim] = pos[dim];
                cur_len[dim]--;
            }
            if (pos[dim] > mx[dim]) {
                mx[dim] = pos[dim];
                cur_len[dim]--;
            }
            if (cur_len[dim] <= 0) {
                finished = true;
                break;
            }
            ll prod = 1;
            for (int j = 1; j <= k; ++j) {
                prod = prod * (cur_len[j] % MOD) % MOD;
            }
            ans = (ans + prod) % MOD;
        }
        if (finished) break;
    }

    cout << (ans % MOD + MOD) % MOD << "\n";
    return 0;
}
