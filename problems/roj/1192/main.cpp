/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:11
 * update_at: 2026-10-05 05:11
 */

#include <cstdio>

typedef long long ll;

ll memo[15][15]; // memo[m][n] = m 个苹果放进 n 个盘子的分法数，-1 表示还没算过

// 求把 m 个同样的苹果放进 n 个同样的盘子（允许空盘）的分法数
ll count_ways(ll m, ll n) {
    if (memo[m][n] != -1) return memo[m][n]; // 记忆化：每个状态只算一次
    ll res;
    if (m == 0 || n == 1) {
        res = 1; // 没有苹果（全空）或只剩一个盘子，都只有一种放法
    } else if (m < n) {
        res = count_ways(m, m); // 盘子比苹果多，多出的盘子必然空着，与 m 个盘子等价
    } else {
        // 按第 n 个盘子是否为空分类，两类互斥且不漏：
        // 空   -> 少一个盘子：count_ways(m, n-1)
        // 非空 -> 非降序下所有盘子都非空，每盘先垫 1 个苹果：count_ways(m-n, n)
        res = count_ways(m, n - 1) + count_ways(m - n, n);
    }
    memo[m][n] = res;
    return res;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        ll m, n;
        scanf("%lld %lld", &m, &n);
        // 多组数据共用一张记忆化表：先把会用到的范围清成 -1
        for (ll i = 0; i <= m; ++i)
            for (ll j = 1; j <= n; ++j)
                memo[i][j] = -1;
        printf("%lld\n", count_ways(m, n));
    }
    return 0;
}
