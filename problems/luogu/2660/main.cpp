/**
 * P2660 zzc 种田
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    scanf("%lld%lld", &a, &b);
    long long ans = 0;
    while (a && b) {
        if (a < b) swap(a, b); // 保证 a >= b
        ans += 4 * b * (a / b); // 切出 a/b 个 b×b 的正方形
        a %= b;
    }
    printf("%lld\n", ans);
    return 0;
}
