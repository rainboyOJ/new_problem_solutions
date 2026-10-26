/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:45
 * update_at: 2026-10-26 16:36
 */
// subtask_ap.cpp：题面「另外 20%：所有电塔高度本身构成等差数列」这一档的闭式解。
// 这一档不属于正解主线，只是利用「高度限制死了一个固定公差」把计数变成数下标等差数列。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;
const int MAXN = 1005; // n <= 1000

ll n;
ll h[MAXN]; // h[i]: 第 i 座塔的高度, 下标从 1 开始

ll pow_mod(ll base, ll exp) {
    ll result = 1 % MOD;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> h[i];
    }
}

void solve() {
    // 公差为 0: 高度全相同, 任意非空子集都等差
    bool all_equal = true;
    for (int i = 2; i <= n; i++) {
        if (h[i] != h[1]) {
            all_equal = false;
        }
    }
    if (all_equal) {
        cout << (pow_mod(2, n) - 1 + MOD) % MOD << '\n';
        return;
    }

    // 公差不为 0: 选出的高度等差 <=> 选出的下标等差, 于是只需数 1..n 里的下标等差数列
    ll ans = n; // 长度 1 的方案
    for (ll q = 1; q <= n - 1; q++) {          // q: 下标公差的绝对值
        for (ll len = 2; (len - 1) * q <= n - 1; len++) { // len: 选出的项数
            // 首项可取 1..n-(len-1)q, 每换一个首项就得到一个新的下标等差数列
            ans = (ans + n - (len - 1) * q) % MOD;
        }
    }
    cout << ans % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();
    return 0;
}
