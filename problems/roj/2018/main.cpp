/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:41
 * update_at: 2026-10-06 09:41
 */
// main.cpp：在 [a,b] 内找回文质数。
// 关键性质：除 11 外，偶数位回文数的奇偶位交错和为 0，必是 11 的倍数，
// 所以 10^8 以内只需枚举 1 位、2 位(仅 11)和 3/5/7 位回文数，再试除判素。
#include <cstdio>
#include <cstdlib>

typedef long long ll;

ll a, b; // 题目给出的区间 [a,b]，b 最大 10^8

// 试除法判定 n 是否为质数
bool is_prime(ll n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (ll i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

// 把数字反转（比如 123 -> 321），用于拼回文数的后半段
ll reverse_num(ll x) {
    ll rev = 0;
    while (x > 0) {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return rev;
}

// 判断 x 是不是回文数
bool is_pal(ll x) {
    return x == reverse_num(x);
}

int main() {
    scanf("%lld %lld", &a, &b);

    // 1 位数和 11 单独处理
    for (ll x = a; x <= b && x < 100; ++x)
        if (is_pal(x) && is_prime(x))
            printf("%lld\n", x);

    // 枚举前半段 root，拼出 root + rev(root) 的 4/6/8 位回文数？
    // 不行：偶数位回文数除 11 外都是 11 的倍数，不可能是质数。
    // 所以只拼 3/5/7 位：root + 中间位 mid + rev(root)
    for (ll half = 1; half <= 1000; half *= 10) { // half = 1,10,100，对应 3/5/7 位
        for (ll root = half; root < half * 10; ++root) {
            ll rev = reverse_num(root);
            for (ll mid = 0; mid <= 9; ++mid) {
                // 拼法：root 后接 mid，再接反转的 root，得奇数位回文数
                ll x = (root * 10 + mid) * half * 10 + rev;
                if (x > b)
                    break; // mid 增大只会更大，直接退出
                if (x >= a && is_prime(x))
                    printf("%lld\n", x);
            }
        }
    }

    return 0;
}
