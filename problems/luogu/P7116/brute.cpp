/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:15
 * update_at: 2026-11-10 23:15
 */

// brute.cpp：小数据全过程暴力模拟
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

int n, k;
ll w[15];
int c[10005], d[10005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;

    ll total = 1;
    for (int i = 1; i <= k; ++i) {
        cin >> w[i];
        total = total * (w[i] % MOD) % MOD;
    }

    for (int i = 1; i <= n; ++i) {
        cin >> c[i] >> d[i];
    }

    // 纯单步模拟各维度的有效区间
    vector<ll> mn(k + 1, 0), mx(k + 1, 0), pos(k + 1, 0);
    vector<ll> cur_w(k + 1);
    for (int i = 1; i <= k; ++i) cur_w[i] = w[i];

    ll ans = total;
    ll step_limit = 2000000; // 防死循环步数限制
    ll steps = 0;

    while (steps < step_limit) {
        for (int i = 1; i <= n; ++i) {
            steps++;
            int dim = c[i];
            pos[dim] += d[i];
            if (pos[dim] < mn[dim]) mn[dim] = pos[dim];
            if (pos[dim] > mx[dim]) mx[dim] = pos[dim];

            ll prod = 1;
            for (int j = 1; j <= k; ++j) {
                ll len = w[j] - (mx[j] - mn[j]);
                if (len <= 0) {
                    cout << ans << "\n";
                    return 0;
                }
                prod = prod * (len % MOD) % MOD;
            }
            ans = (ans + prod) % MOD;
        }

        // 检查一轮后是否完全没有缩减
        bool has_change = false;
        for (int j = 1; j <= k; ++j) {
            if (w[j] - (mx[j] - mn[j]) < cur_w[j]) {
                has_change = true;
                cur_w[j] = w[j] - (mx[j] - mn[j]);
            }
        }
        if (!has_change) {
            cout << -1 << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
