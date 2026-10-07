/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:19
 * update_at: 2026-10-06 00:19
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 25; // m <= 20，矩阵是 (m+1) 阶，开 25 足够

ll n, m, mod;
ll a[MAXM];   // a[i]：不吉利数字的第 i 位（下标从 0 开始），取值 0..9
ll fail[MAXM]; // fail[i]：a[0..i-1] 的最长真前后缀长度（KMP 失配数组）
ll trans[MAXM][MAXM]; // trans[q][q2]：已匹配 q 位时读一个数字变成 q2 位的数字个数
ll base_mat[MAXM][MAXM], result_mat[MAXM][MAXM], tmp_mat[MAXM][MAXM]; // 矩阵幂用的三个方阵
ll v[MAXM];   // v[q]：填了若干位后当前匹配长度为 q 且从未出现完整不吉利数字的方案数

// 求 KMP 失配数组：fail[i] 表示前 i 位的最长相等真前后缀长度。
void build_fail() {
    fail[0] = 0;
    fail[1] = 0;
    for (ll i = 1; i < m; i++) {
        ll j = fail[i];
        while (j && a[i] != a[j]) j = fail[j]; // 回退到还能接上 a[i] 的前缀
        if (a[i] == a[j]) j++;
        fail[i + 1] = j;
    }
}

// 建转移矩阵：从匹配长度 q 出发，对 10 个数字分别求 KMP 转移后的新长度。
// 只统计新长度 q2 < m 的转移；q2 == m 意味着不吉利数字出现，这条路径直接排除。
void build_transition() {
    memset(trans, 0, sizeof(trans));
    for (ll q = 0; q < m; q++) { // 吸收态 m 不需要出边
        for (ll d = 0; d <= 9; d++) {
            ll j = q;
            while (j && a[j] != d) j = fail[j]; // 沿失配链回退
            ll q2 = j + 1;
            if (a[j] != d) q2 = 0;
            if (q2 < m) trans[q][q2]++; // 多少个数字能完成 q -> q2 的转移
        }
    }
}

// 矩阵乘法 c = a * b（mod 意义下），size = m+1。
void mat_mul(ll c[][MAXM], ll x[][MAXM], ll y[][MAXM]) {
    memset(tmp_mat, 0, sizeof(tmp_mat));
    for (ll i = 0; i <= m; i++) {
        for (ll t = 0; t <= m; t++) {
            if (x[i][t] == 0) continue; // 零元整行贡献为 0，跳过
            for (ll j = 0; j <= m; j++) {
                tmp_mat[i][j] = (tmp_mat[i][j] + x[i][t] * y[t][j]) % mod;
            }
        }
    }
    // 结果先写进 tmp_mat，再拷回 c，避免 x 或 y 就是 c 时被覆盖出错
    for (ll i = 0; i <= m; i++) {
        for (ll j = 0; j <= m; j++) {
            c[i][j] = tmp_mat[i][j];
        }
    }
}

// 矩阵快速幂：result_mat = trans^n（mod 意义下），二进制分解反复平方。
void mat_pow() {
    for (ll i = 0; i <= m; i++) {
        for (ll j = 0; j <= m; j++) {
            result_mat[i][j] = (i == j); // 单位矩阵
        }
    }
    memcpy(base_mat, trans, sizeof(trans));
    ll e = n;
    while (e) {
        if (e & 1) mat_mul(result_mat, result_mat, base_mat);
        mat_mul(base_mat, base_mat, base_mat);
        e >>= 1;
    }
}

// 求答案：初始向量 v = e_0，右乘 trans^n，再对非吸收态求和。
void solve() {
    build_fail();
    build_transition();
    mat_pow();

    memset(v, 0, sizeof(v));
    v[0] = 1; // 没填任何位时匹配长度必然是 0，方案数 1

    ll ans = 0;
    for (ll q = 0; q < m; q++) { // 状态 m 是吸收态，不参与计数
        ll sum = 0;
        for (ll t = 0; t <= m; t++) {
            sum = (sum + v[t] * result_mat[t][q]) % mod;
        }
        ans = (ans + sum) % mod;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> n >> m >> mod >> s;
    for (ll i = 0; i < m; i++) {
        a[i] = s[i] - '0'; // 不吉利数字的每一位，允许前导 0
    }

    solve();

    return 0;
}
