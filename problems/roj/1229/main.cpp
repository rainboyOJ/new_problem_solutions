/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:05
 * update_at: 2026-10-05 06:05
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

ll a[MAXN]; // a[i] 表示第 i 节电池能使用的小时数

int main() {
    int n;
    // 多组数据读到 EOF
    while (scanf("%d", &n) == 1) {
        ll sum = 0;   // 总电量 Sigma
        ll mx = 0;    // 最大单节电量 M
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            sum += a[i];
            mx = max(mx, a[i]);
        }
        // 两个上界取小：总电量给 T <= sum/2，单节速率 1 给 T <= sum - max
        // sum 是整数，min 结果要么是 .0 要么是 .5，直接用整数运算换算成 0.1 位输出
        ll t2 = min(sum, 2 * (sum - mx)); // 相当于 2T，避免浮点
        printf("%lld.%c\n", t2 / 2, (t2 % 2 == 0) ? '0' : '5');
    }
    return 0;
}
