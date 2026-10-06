/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:16
 * update_at: 2026-10-06 14:16
 */
#include <cstdio>

typedef long long ll;

// 数字 0~9 各需要的火柴棍根数
const int DIGIT_COST[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

ll n;      // 火柴棍总数
ll ans;    // 能拼出的等式数目

// 计算 x 逐位需要的火柴棍根数，特别地 cost(0) = 6
ll cost(ll x) {
    if (x == 0) return 6;
    ll sum = 0;
    while (x > 0) {
        sum += DIGIT_COST[x % 10];
        x /= 10;
    }
    return sum;
}

int main() {
    scanf("%lld", &n);
    ll k = n - 4; // 扣掉加号和等号共 4 根后，A、B、C 能用的火柴根数
    ans = 0;
    // C = A + B 被唯一确定，只需枚举 A、B，再 O(1) 核对 C 的根数
    // n <= 24 时 k <= 20，每位至少 2 根且 C 位数不小于 A、B，可证 A、B 均不超过 4 位
    for (ll a = 0; a <= 9999; ++a) {
        for (ll b = 0; b <= 9999; ++b) {
            if (cost(a) + cost(b) + cost(a + b) == k)
                ++ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
