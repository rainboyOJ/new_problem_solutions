/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:09
 * update_at: 2026-10-05 01:09
 */
// main.cpp：不定方程 ax+by=c 的非负整数解计数（roj 1101）。
// 做法：固定 x 在 [0, c/a] 范围枚举，每个 x 唯一决定 y=(c-a*x)/b，
// 当且仅当 (c-a*x) >= 0 且被 b 整除时贡献一组解。

#include <cstdio>
using namespace std;

typedef long long ll;

ll a, b, c;   // 方程系数 a, b, c
ll ans;       // 非负整数解计数

int main() {
    // 读入 a, b, c
    scanf("%lld %lld %lld", &a, &b, &c);

    // 枚举 x 从 0 到 c/a：超过此范围则 a*x > c，没有合法非负 y
    for (ll x = 0; x <= c / a; ++x) {
        ll rest = c - a * x;
        // 余数 (c - a*x) 必须能被 b 整除才给出整数 y，且 y = rest / b >= 0 自动成立
        if (rest % b == 0) {
            ++ans;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
