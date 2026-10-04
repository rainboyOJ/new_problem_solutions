/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 21:45
 * update_at: 2026-10-05 04:05
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll n, x;

// 记忆化数组：memo[i] 表示 h_i(x) 的值，0 表示尚未计算。
// 本题 n <= 10，用 ll 足够。
ll memo[15];

// 按题面二阶递推式递归求 Hermite 多项式 h_n(x)
ll hermite(ll k) {
    if (memo[k] != 0) return memo[k];
    if (k == 0) return memo[k] = 1;
    if (k == 1) return memo[k] = 2 * x;
    return memo[k] = 2 * x * hermite(k - 1) - 2 * (k - 1) * hermite(k - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> x;
    ll ans = hermite(n);
    // 结果必为整数，按要求补两位小数输出，避免浮点精度问题。
    cout << ans << ".00" << endl;
    return 0;
}
