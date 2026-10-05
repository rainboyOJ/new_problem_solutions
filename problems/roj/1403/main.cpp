/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:02
 * update_at: 2026-10-05 23:02
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 10005;

bool is_prime[MAXN]; // is_prime[i] 表示 i 是否为素数（埃氏筛结果）

int main() {
    ll n;
    scanf("%lld", &n);

    // 埃氏筛：把 0、1 标记为非素数，其余先假设是素数
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) is_prime[i] = true;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i) // 从 i*i 开始筛 i 的倍数
                is_prime[j] = false;

    bool found = false; // 是否找到过素数对
    // 除 2 以外的素数都是奇数，且 (2,4) 不合法，只需枚举奇数 p
    for (ll p = 3; p + 2 <= n; p += 2) {
        if (is_prime[p] && is_prime[p + 2]) {
            printf("%lld %lld\n", p, p + 2);
            found = true;
        }
    }

    if (!found) printf("empty\n");
    return 0;
}
