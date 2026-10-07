/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:29
 * update_at: 2026-10-06 01:29
 */
#include <cstdio>

typedef long long ll;

const ll M = 23 * 28 * 33; // 21252：三个周期的公共周期，答案必在其中
const ll MI[3] = {924, 759, 644};  // B[k] = M / m[k]
const ll TI[3] = {6, 19, 2};       // t[k] = B[k] 的逆元 mod m[k]，即 B[k]*t[k] 只在 mod m[k] 处余 1

// 用中国剩余定理求 x ≡ r[k] (mod m[k]) 的最小非负解，m 分别为 23, 28, 33
ll crt(ll r1, ll r2, ll r3) {
    ll base[3] = {r1, r2, r3};
    ll x = 0;
    for (int k = 0; k < 3; k++)
        x += base[k] % (M / MI[k]) * MI[k] * TI[k];
    return x % M;
}

int main() {
    ll p, e, i, d;
    int cas = 0;
    while (scanf("%lld %lld %lld %lld", &p, &e, &i, &d) == 4) {
        if (p == -1 && e == -1 && i == -1 && d == -1)
            break;

        // 三个高峰同天时刻 x 在 [0, M) 内唯一；下一次严格晚于 d 的距离用
        // (x - d - 1) % M + 1 统一处理：x <= d 时自动跳到下一圈，
        // x == d 时按题意跳过当天、答案为整个周期 M
        ll x = crt(p, e, i);
        // 注意 C++ 负数取模结果可能为负，先 +M 再取模
        ll ans = ((x - d - 1) % M + M) % M + 1;
        printf("Case %d: the next triple peak occurs in %lld days.\n", ++cas, ans);
    }
    return 0;
}
