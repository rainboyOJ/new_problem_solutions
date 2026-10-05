/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:29
 * update_at: 2026-10-06 01:29
 */

#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll n, m;

// 2×2 矩阵乘法，边乘边对 m 取模
void mat_mul(ll a[2][2], ll b[2][2], ll res[2][2]) {
    ll tmp[2][2];
    tmp[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % m;
    tmp[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % m;
    tmp[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % m;
    tmp[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % m;
    res[0][0] = tmp[0][0];
    res[0][1] = tmp[0][1];
    res[1][0] = tmp[1][0];
    res[1][1] = tmp[1][1];
}

// 矩阵快速幂：返回 base^p mod m
void mat_pow(ll base[2][2], ll p, ll ans[2][2]) {
    // ans 初始化为单位矩阵
    ans[0][0] = 1; ans[0][1] = 0;
    ans[1][0] = 0; ans[1][1] = 1;
    ll cur[2][2];
    cur[0][0] = base[0][0]; cur[0][1] = base[0][1];
    cur[1][0] = base[1][0]; cur[1][1] = base[1][1];
    while (p) {
        if (p & 1) {
            ll t[2][2];
            mat_mul(ans, cur, t);
            ans[0][0] = t[0][0]; ans[0][1] = t[0][1];
            ans[1][0] = t[1][0]; ans[1][1] = t[1][1];
        }
        ll t[2][2];
        mat_mul(cur, cur, t);
        cur[0][0] = t[0][0]; cur[0][1] = t[0][1];
        cur[1][0] = t[1][0]; cur[1][1] = t[1][1];
        p >>= 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    if (m == 1) {
        cout << 0 << "\n";
        return 0;
    }
    // 转移矩阵 T = [[1,1],[1,0]]
    ll T[2][2] = {{1, 1}, {1, 0}};
    // 恒等式 S_n = f_{n+2} - 1，T^(n+1) 的左上角即为 f_{n+2}
    ll P[2][2];
    mat_pow(T, n + 1, P);
    ll ans = (P[0][0] - 1) % m;
    if (ans < 0) ans += m;
    cout << ans << "\n";
    return 0;
}
