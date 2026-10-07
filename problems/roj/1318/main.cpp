/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:17
 * update_at: 2026-10-05 09:17
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1000; // 拆分路径长度上界

ll n;             // 待拆分的自然数
ll path[MAXN];    // 当前拆分方案

// 按非递减顺序搜索 rest 的拆分，start 为下一个加数的最小允许值，len 为已选加数个数
void dfs(ll rest, ll start, int len) {
    if (rest == 0) {
        printf("%lld=%lld", n, path[0]);
        for (int i = 1; i < len; ++i) {
            printf("+%lld", path[i]);
        }
        putchar('\n');
        return;
    }
    for (ll x = start; x <= rest; ++x) {
        if (x < n) {          // 每个加数必须小于 n
            path[len] = x;
            dfs(rest - x, x, len + 1);
        }
    }
}

int main() {
    scanf("%lld", &n);
    dfs(n, 1, 0);
    return 0;
}
