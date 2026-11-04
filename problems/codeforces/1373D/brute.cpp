/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 10:50
 * update_at: 2026-11-04 14:09
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 2005;

ll n;
ll a[MAXN];
ll temp_a[MAXN];

// 暴力求解一个测试用例：枚举所有可能的区间 [l, r] 并反转，统计偶数位之和
void solve() {
    cin >> n;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 计算初始（不反转）时的偶数位和
    ll max_ans = 0;
    for (ll i = 0; i < n; i += 2) {
        max_ans += a[i];
    }

    // 枚举所有可能的反转区间 [l, r]
    for (ll l = 0; l < n; ++l) {
        for (ll r = l; r < n; ++r) {
            // 复制原数组
            for (ll i = 0; i < n; ++i) {
                temp_a[i] = a[i];
            }
            // 反转区间 [l, r]
            reverse(temp_a + l, temp_a + r + 1);

            // 统计当前偶数位元素之和
            ll cur_sum = 0;
            for (ll i = 0; i < n; i += 2) {
                cur_sum += temp_a[i];
            }
            max_ans = max(max_ans, cur_sum);
        }
    }

    cout << max_ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
