/**
 * P2651 添加括号III
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int a[10005];
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        // a1 / a2 / a3 / ... / an → 通过加括号可以使 a2 成为分母
        // 判断 a1 * a3 * ... * an 是否能被 a2 整除
        // 即 a2 / gcd(a1,a2) 继续除以 gcd(..., ai) 最终是否为 1
        int den = a[2];
        den /= __gcd(a[1], den); // a1 可以约分
        for (int i = 3; i <= n; ++i) {
            den /= __gcd(den, a[i]);
            if (den == 1) break;
        }
        puts(den == 1 ? "Yes" : "No");
    }
    return 0;
}
