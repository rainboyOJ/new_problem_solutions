/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:32
 * update_at: 2026-10-05 05:32
 */
#include <cstdio>

typedef long long ll;

// gcd：辗转相除，反复把 (a, b) 换成 (b, a % b)，b 归零时 a 就是答案
ll gcd(ll a, ll b) {
    while (b != 0) {
        ll r = a % b; // 余数严格变小，循环次数为 O(log min(a, b))
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ll a, b;
    if (scanf("%lld %lld", &a, &b) != 2) return 0;
    printf("%lld\n", gcd(a, b));
    return 0;
}