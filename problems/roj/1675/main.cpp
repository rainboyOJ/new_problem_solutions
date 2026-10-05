/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:38
 * update_at: 2026-10-06 01:38
 */
// main.cpp：数的划分，按题解主算法做二维 DP。
// f(n, k) 表示把 n 拆成 k 份正整数的无序方案数：
// 按拆分中最小项是否为 1 分类，可得 f(n, k) = f(n-1, k-1) + f(n-k, k)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 205;
const int MAXK = 10;

ll f[MAXN][MAXK]; // f[n][k]：把 n 拆成 k 份正整数的方案数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    // 边界：k = 1 时只有一种拆法（n 本身）；其余从 2 份开始递推。
    for (ll i = 1; i <= n; i++) f[i][1] = 1;

    // 递推：f[i][j] = f[i-1][j-1]（最小项为 1）+ f[i-j][j]（每份减 1 后仍为 j 份正整数）。
    for (ll i = 2; i <= n; i++) {
        for (ll j = 2; j <= k; j++) {
            if (i < j) continue; // 份数比和还大，无法拆分
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
        }
    }

    cout << f[n][k] << endl;

    return 0;
}
