/**
 * P2234 [HNOI2002] 营业额统计
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 33000;
int a[MAXN];  // 存所有营业额
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

    // 第一天波动值就是当天营业额本身
    long long ans = a[1];
    // 对每天 i，在前 i-1 天中找与 a[i] 差值最小的那天
    for (int i = 2; i <= n; ++i) {
        int min_diff = abs(a[i] - a[1]);
        for (int j = 2; j < i; ++j) {
            int diff = abs(a[i] - a[j]);
            if (diff < min_diff) min_diff = diff;
        }
        ans += min_diff;
    }
    printf("%lld\n", ans);
    return 0;
}
