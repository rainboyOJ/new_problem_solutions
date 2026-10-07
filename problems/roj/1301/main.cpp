/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:33
 * update_at: 2026-10-05 08:33
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100000 + 5; // 每组数据最多 N 家店铺

ll a[MAXN]; // 每家店铺的现金

// 滚动 DP：prev2 表示 f[i-2]，prev1 表示 f[i-1]
ll solve_case(int n) {
    ll prev2 = 0;       // f[0] = 0
    ll prev1 = a[1];    // f[1] = a[1]
    for (int i = 2; i <= n; i++) {
        ll cur = max(prev1, prev2 + a[i]); // 不选第 i 家 或 选第 i 家
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        if (n == 0) {
            printf("0\n");
            continue;
        }
        printf("%lld\n", solve_case(n));
    }
    return 0;
}
