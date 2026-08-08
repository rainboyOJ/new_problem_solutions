/**
 * P1403 [AHOI2005] 约数研究
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    long long ans = 0;
    // 1~n 中，约数 d 出现 ⌊n/d⌋ 次
    // 对 ⌊n/d⌋ 相等的 d 合并计算
    for (int l = 1, r; l <= n; l = r + 1) {
        int q = n / l;
        r = n / q;
        ans += 1LL * q * (r - l + 1);
    }
    printf("%lld\n", ans);
    return 0;
}
