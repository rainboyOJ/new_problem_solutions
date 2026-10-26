/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:45
 * update_at: 2026-10-26 13:45
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;
const int MAXN = 1005;   // n <= 1000
const int MAXH = 20000;  // 电塔高度上限 v <= 2e4

int n;
int h[MAXN];      // h[i]: 第 i 座塔的高度, 下标从 1 开始
int f[MAXN][MAXN]; // f[i][j] (i > j): 最后两项是第 j 座和第 i 座塔的等差子序列个数, 含长度 2
ll bucket[MAXH + 1]; // bucket[v]: 固定中间项 j 时, 左侧高度恰为 v 的所有 f[j][k] 之和

void read_input() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
}

void solve() {
    ll ans = n; // 只留一座塔的方案(长度 1)一定等差, 先把它们计入答案
    for (int j = 1; j <= n; j++) {
        // 把中间项 j 左侧所有 f[j][k] 按高度 k 所在的高度分桶, 后面按需要的高度直接取
        for (int k = 1; k < j; k++) {
            bucket[h[k]] = (bucket[h[k]] + f[j][k]) % MOD;
        }
        for (int i = j + 1; i <= n; i++) {
            // 公差 d = h[i] - h[j], 所以 j 前面那一项的高度只能是 2*h[j] - h[i]
            int need = 2 * h[j] - h[i];
            ll ways = 1; // 只保留第 j 座和第 i 座塔, 长度 2 也算一种方案
            if (need >= 0 && need <= MAXH) {
                ways += bucket[need];
            }
            ways %= MOD;
            f[i][j] = ways;
            ans = (ans + ways) % MOD;
        }
        for (int k = 1; k < j; k++) { // 清空本轮写过的桶, 交给下一个中间项使用
            bucket[h[k]] = 0;
        }
    }
    printf("%lld\n", ans % MOD);
}

int main() {
    read_input();
    solve();
    return 0;
}
