/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:55
 * update_at: 2026-10-06 14:55
 */

#include <cstdio>
using namespace std;

typedef long long ll;

const int MOD = 1000007; // 题面指定的模数

int n, m;
int a[105];       // 每种花最多摆的盆数
int dp[105];      // dp[j] = 当前阶段恰好摆 j 盆的方案数
int pre[105];     // pre[j] = dp[0..j] 的前缀和

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] > m) a[i] = m; // 超过 m 的上限永远用不到
    }

    dp[0] = 1; // 一种花都不摆，只有摆 0 盆一种方案

    for (int i = 1; i <= n; i++) {
        int cap = a[i];
        // 先对旧 dp 做前缀和
        pre[0] = dp[0];
        for (int j = 1; j <= m; j++) {
            pre[j] = pre[j - 1] + dp[j];
            if (pre[j] >= MOD) pre[j] -= MOD;
        }
        // 用前缀和差分求滑动窗口和，得到新 dp
        for (int j = 0; j <= m; j++) {
            int left = j - cap - 1;
            int val = pre[j];
            if (left >= 0) {
                val -= pre[left];
                if (val < 0) val += MOD;
            }
            dp[j] = val;
        }
    }

    printf("%d\n", dp[m]);
    return 0;
}
