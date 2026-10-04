/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:48
 * update_at: 2026-10-05 00:48
 */

#include <cstdio>

typedef long long ll;

ll n;   // 题目给出的上限
ll f;   // f 当前维护 i! 的值
ll ans; // 答案：1! + 2! + ... + n!

int main() {
    scanf("%lld", &n);
    f = 1;   // 1! = 1，从这里开始递推
    ans = 0;
    for (ll i = 1; i <= n; i++) {
        f = f * i; // 递推：i! = i * (i-1)!
        ans = ans + f;
    }
    printf("%lld\n", ans);
    return 0;
}
