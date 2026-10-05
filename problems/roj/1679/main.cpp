/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:49
 * update_at: 2026-10-06 01:49
 */

#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXM = 15;
const int MAXN = 15;
const int MOD = 100000000;

int m, n;
int fertile[MAXM];          // 每行肥沃格子的位掩码

ll dp[2][1 << MAXN];        // 滚动数组，dp[cur][s] 表示当前行状态为 s 的方案数

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) {
        int mask = 0;
        for (int j = 0; j < n; j++) {
            int x;
            scanf("%d", &x);
            if (x) mask |= (1 << j);
        }
        fertile[i] = mask;
    }

    // 预处理所有无水平相邻1的掩码，同时是肥沃格子子集
    vector<int> masks[MAXM];
    int total = 1 << n;
    for (int i = 1; i <= m; i++) {
        for (int s = 0; s < total; s++) {
            if ((s & (s << 1)) == 0 && (s & fertile[i]) == s) {
                masks[i].push_back(s);
            }
        }
    }

    // 初始化：第0行之前只有状态0，方案数为1
    int cur = 0;
    dp[cur][0] = 1;

    for (int i = 1; i <= m; i++) {
        int nxt = cur ^ 1;
        // 清空下一行状态
        for (int j = 0; j < total; j++) dp[nxt][j] = 0;
        // 枚举当前行所有合法状态
        for (size_t a = 0; a < masks[i].size(); a++) {
            int s = masks[i][a];
            ll sum = 0;
            // 枚举上一行所有合法状态，要求无垂直相邻
            // 第1行的上一行是虚拟的第0行，只有状态0
            if (i == 1) {
                if ((s & 0) == 0) sum = dp[cur][0];
            } else {
                for (size_t b = 0; b < masks[i - 1].size(); b++) {
                    int t = masks[i - 1][b];
                    if ((s & t) == 0) {
                        sum += dp[cur][t];
                        if (sum >= MOD) sum -= MOD;
                    }
                }
            }
            dp[nxt][s] = sum % MOD;
        }
        cur = nxt;
    }

    ll ans = 0;
    for (int s = 0; s < total; s++) {
        ans += dp[cur][s];
        if (ans >= MOD) ans -= MOD;
    }
    printf("%lld\n", ans % MOD);
    return 0;
}
