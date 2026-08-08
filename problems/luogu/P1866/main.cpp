/**
 * P1866 编号
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int MOD = 1000000007;

int a[MAXN], n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    long long ans = 1;
    for (int i = 1; i <= n; ++i) {
        // 第 i 小上限：还剩 a[i] - (i-1) 个数可选
        ans = ans * max(0, a[i] - (i - 1)) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
