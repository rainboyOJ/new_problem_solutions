/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:56
 * update_at: 2026-10-08 22:56
 */
// main.cpp：用筛法（埃拉托色尼筛）求出 n 以内的全部质数，由小到大每行一个。
#include <iostream>

typedef long long ll;

const int MAXN = 1000000;   // 数组余量（题面上限仅 1000，留足空间防数据越界）

bool is_prime[MAXN + 5];    // is_prime[i]：筛完后 i 是否仍为质数

void solve() {
    ll n;
    if (!(std::cin >> n)) return;               // 无输入时安静退出
    if (n < 2 || n > MAXN) return;              // 题面保证 2 <= n <= 1000

    for (ll i = 0; i <= n; ++i) is_prime[i] = true;
    is_prime[0] = false;                        // 0 和 1 不是质数
    is_prime[1] = false;

    // 外层只需枚举到 sqrt(n)：n 以内的合数必有不超过 sqrt(n) 的质因数，
    // 它的全部倍数在该质因数处已经被标记过。
    for (ll i = 2; i * i <= n; ++i) {
        if (!is_prime[i]) continue;             // 已被更小的质数筛掉
        // 从 i*i 起标记：i 的倍数 i*2 .. i*(i-1) 都含更小的质因数，早已被筛掉。
        for (ll j = i * i; j <= n; j += i) is_prime[j] = false;
    }

    for (ll i = 2; i <= n; ++i) {
        if (is_prime[i]) std::cout << i << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}
