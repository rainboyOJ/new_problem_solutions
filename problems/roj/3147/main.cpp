/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 金字塔：区间 DP，s[i..j] 单独作为一棵子树的方案数。
#include <cstdio>
#include <cstring>

typedef long long ll;

const ll MOD = 1000000000LL;
const ll MAXN = 305;

char text[MAXN];
ll dp[MAXN][MAXN];

int main() {
    if (scanf("%s", text) != 1) {
        printf("0\n");
        return 0;
    }
    ll n = (ll)strlen(text);

    // dp[i][j]：s[i..j] 单独作为一棵子树（连同它的遍历序列）的方案数
    for (ll i = 0; i < n; i++) dp[i][i] = 1; // 单个房间，进出各记一次

    for (ll span = 3; span <= n; span += 2) {
        for (ll i = 0; i + span - 1 < n; i++) {
            ll j = i + span - 1;
            if (text[i] != text[j]) continue; // 进入与退出记录的颜色必须都是根色
            char root = text[i];
            ll total = 0;
            // 切分点 k：第一棵子树占 s[i+1..k-1]，剩下的 s[k..j] 是同一层的其它子树
            for (ll k = i + 2; k <= j; k++) {
                if (text[k] == root) {
                    total = (total + (dp[i + 1][k - 1] % MOD) * (dp[k][j] % MOD)) % MOD;
                }
            }
            dp[i][j] = total % MOD;
        }
    }

    printf("%lld\n", n ? dp[0][n - 1] : 0);
    return 0;
}
