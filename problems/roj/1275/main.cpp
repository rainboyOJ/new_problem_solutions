/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 14:30
 * update_at: 2026-10-05 07:45
 */
// main.cpp：把长度为 N 的数字串插入 K 个乘号切成 K+1 段，使各段整数乘积最大。
// DP：dp[i] 表示前 i 位用当前刀数能得到的最大乘积，逐层滚动枚举最后一刀位置 t。

#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 15;

int n, k;
char s[MAXN];
ll dp[MAXN]; // dp[i]：前 i 位用掉当前层刀数后的最大乘积

// 子串 [l, r) 的十进制值（l 从 0 起，半开区间），允许前导 0。
ll val(int l, int r) {
    ll v = 0;
    for (int i = l; i < r; i++) {
        v = v * 10 + (s[i] - '0');
    }
    return v;
}

void solve() {
    // 0 刀时整段就是一个因子
    for (int i = 1; i <= n; i++) {
        dp[i] = val(0, i);
    }
    dp[0] = 0;

    // 逐层加入第 j 把刀，第 j 层只依赖第 j-1 层的 dp
    for (int j = 1; j <= k; j++) {
        ll pre[MAXN];
        for (int i = 0; i <= n; i++) pre[i] = dp[i]; // 暂存上一层结果

        for (int i = 1; i <= n; i++) {
            ll best = 0;
            // 最后一刀落在第 t 位之后，左半段长 j 位是下限
            for (int t = j; t <= i - 1; t++) {
                ll cur = pre[t] * val(t, i);
                if (cur > best) best = cur;
            }
            dp[i] = best;
        }
    }

    printf("%lld\n", dp[n]);
}

int main() {
    // 输入：第一行 N K，第二行是长度为 N 的数字串
    scanf("%d %d", &n, &k);
    scanf("%s", s);
    solve();
    return 0;
}