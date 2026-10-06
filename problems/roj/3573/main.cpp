/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:26
 * update_at: 2026-10-06 14:26
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 5000; // 约数最多 1500 个左右，开 5000 足够

ll a0, a1, b0, b1;     // 每组输入的四个数
ll divs[MAXN];         // divs[i] 存 b1 的第 i 个约数（试除生成）
int cnt;               // b1 的约数个数

// 求最大公约数
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 用试除把 b1 的全部约数存进 divs[]：d <= sqrt(b1) 时同时拿到 d 和 b1/d
void get_divisors(ll x) {
    cnt = 0;
    for (ll d = 1; d * d <= x; ++d) {
        if (x % d == 0) {
            divs[cnt++] = d;
            if (d != x / d) divs[cnt++] = x / d;
        }
    }
}

// 判断候选 d 是否满足 gcd(d,a0)=a1 且 lcm(d,b0)=b1
bool check(ll d) {
    if (d % a1 != 0) return false;      // a1 | d 是必要条件，先廉价筛掉
    if (gcd(d, a0) != a1) return false; // 条件一
    // lcm(d,b0) = d*b0/gcd(d,b0)，避免直接除，改判乘积等式 d*b0 = b1*gcd(d,b0)
    if (d * b0 != b1 * gcd(d, b0)) return false;
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%lld %lld %lld %lld", &a0, &a1, &b0, &b1);
        get_divisors(b1); // x 必须既是 a1 的倍数又整除 b1，所以只需枚举 b1 的约数
        int ans = 0;
        for (int i = 0; i < cnt; ++i)
            if (check(divs[i])) ++ans;
        printf("%d\n", ans);
    }
    return 0;
}
