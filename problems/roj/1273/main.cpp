/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:44
 * update_at: 2026-10-05 07:44
 */

#include <iostream>
using namespace std;

const int MAXM = 10005;
const int MAXN = 105;

typedef long long ll;

ll n, m;
ll a[MAXN];     // 面值数组
ll f[MAXM];     // f[j] 表示凑出面值 j 的方案数

void read_input() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    f[0] = 1;                       // 什么都不选是一种方案
    for (ll i = 1; i <= n; i++) {   // 外层按面值分层，保证组合去重
        ll c = a[i];
        for (ll j = c; j <= m; j++) { // 金额正序枚举，面值可无限使用
            f[j] += f[j - c];
        }
    }
    cout << f[m] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
