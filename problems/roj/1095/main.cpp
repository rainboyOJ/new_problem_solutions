/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:59
 * update_at: 2026-10-05 01:00
 */
#include <cstdio>

typedef long long ll;

ll n;   // 题目给出的上界
ll ans; // 1..n 中数字 "1" 的总个数

int main() {
    scanf("%lld", &n);
    // 枚举 1..n 的每个整数，逐位统计数字 "1"
    for (ll i = 1; i <= n; ++i) {
        ll x = i;
        while (x > 0) {
            if (x % 10 == 1) // 当前个位是 1
                ++ans;
            x /= 10;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
