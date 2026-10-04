/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:20
 * update_at: 2026-10-05 00:20
 */
// main.cpp：统计满足 个位 - 千位 - 百位 - 十位 > 0 的四位数的个数。
// 等价改写为 个位 > 千位 + 百位 + 十位；对每个四位数拆位判定后累加。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll n;
ll x[MAXN]; // 读入的四位数，n ≤ 100，留一点余量

ll ans; // 满足条件的数的个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> x[i];
    }

    // 对每个四位数逐位拆开：千位 a、百位 b、十位 c、个位 d
    for (ll i = 1; i <= n; i++) {
        ll a = x[i] / 1000;
        ll b = (x[i] / 100) % 10;
        ll c = (x[i] / 10) % 10;
        ll d = x[i] % 10;
        if (d - a - b - c > 0) {
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}