/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:30
 * update_at: 2026-10-05 23:30
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 100000 + 5;

int n;              // 数列长度
ll m;               // 每段和的上限
ll a[MAXN];         // a[i]：数列第 i 个数（非负整数）

// 贪心：从左到右扫描，当前段能装就装，装不下就另起一段。
// 因为所有数非负，让每一段尽可能向右延伸一定不劣，段数最少。
int main() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }

    int ans = 1;    // 至少分成 1 段
    ll sum = 0;     // 当前段的和

    for (int i = 1; i <= n; ++i) {
        if (sum + a[i] <= m) {
            // 当前数还能放进这一段
            sum += a[i];
        } else {
            // 放不下，另起一段，当前数成为新段第一个数
            ++ans;
            sum = a[i];
        }
    }

    printf("%d\n", ans);
    return 0;
}
