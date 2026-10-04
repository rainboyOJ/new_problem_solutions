/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-05 00:27
 */

#include <cstdio>

typedef long long ll;

ll n;          // 题目给出的项数，1 <= n <= 1000
double ans;    // 累加得到的表达式值

int main() {
    scanf("%lld", &n);
    // 第 i 项：奇数项为 +1/i，偶数项为 -1/i，逐项累加
    for (ll i = 1; i <= n; i++) {
        if (i & 1)
            ans += 1.0 / (double)i;
        else
            ans -= 1.0 / (double)i;
    }
    printf("%.4f\n", ans);
    return 0;
}
