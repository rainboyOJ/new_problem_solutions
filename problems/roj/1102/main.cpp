/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:08
 * update_at: 2026-10-05 01:08
 */
// main.cpp：统计整数序列中与指定数字 m 相同的数的个数。
#include <iostream>

typedef long long ll;

const int MAXN = 105;
ll a[MAXN]; // a[i] 表示序列中第 i 个数

int main() {
    ll n; // 序列长度
    std::cin >> n;
    for (ll i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    ll m; // 指定的数字
    std::cin >> m;

    ll cnt = 0; // 序列中与 m 相等的数的个数
    for (ll i = 1; i <= n; i++) {
        if (a[i] == m) {
            cnt++;
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}
