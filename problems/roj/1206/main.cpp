/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:32
 * update_at: 2026-10-05 05:33
 */
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXM = 10;
const int MAXN = 10;

// memo[m][n]：m 个苹果放进 n 个相同盘子（可空）的分法数，-1 表示未计算
ll memo[MAXM + 1][MAXN + 1];

// m 个苹果放进 n 个相同盘子（可空）的分法数
ll ways(int m, int n) {
    if (m == 0) return 1;          // 苹果放完，所有盘子空着，只有一种分法
    if (n == 0) return 0;          // 苹果没放完却没盘子了，无解
    ll &res = memo[m][n];
    if (res != -1) return res;
    if (n > m) return res = ways(m, m); // 多余盘子必空，等价于只用 m 个盘子
    // 有空盘：不用第 n 个盘子；无空盘：每盘先放一个，再递归
    return res = ways(m, n - 1) + ways(m - n, n);
}

int main() {
    memset(memo, -1, sizeof(memo)); // 初始化记忆化表
    int t;
    scanf("%d", &t);
    while (t--) {
        int m, n;
        scanf("%d %d", &m, &n);
        printf("%lld\n", ways(m, n));
    }
    return 0;
}
