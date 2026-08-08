/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 12:00
 * update_at: 2026-08-05 12:00
 */

/* P3435 [POI 2006] OKR-Periods of Words */
/* 核心观察：
 *   1. 前缀的所有 border 按长度严格嵌套成一条链（沿 pi 链递减）。
 *   2. 前缀 i 的最长真周期长度 = 长度 - 最短非空 border。
 *   3. mini[i] 沿 pi 链跳到底即可：mini[i] = mini[pi[i]-1]；无 border 时贡献 0。
 * 下标约定与 rbook 文章《KMP 字符串匹配》一致：从 0 开始。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
char s[MAXN];
int pi[MAXN];    // pi[i]：s[0..i] 的最长相等真前后缀长度，pi[0] = 0
int mini[MAXN];  // mini[i]：s[0..i] 的最短非空 border 长度；无 border 时为 i+1

// 前缀函数模板（与 rbook 文章《KMP 字符串匹配》一致，0-indexed）
void build_prefix_function() {
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];   // 失配：回退到上一个可能成立的长度
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    build_prefix_function();

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int len = i + 1;
        if (pi[i] == 0) {
            mini[i] = len;               // 没有非空 border：不存在真周期
        } else {
            mini[i] = mini[pi[i] - 1];   // 沿 pi 链跳到底：最短非空 border
        }
        ans += len - mini[i];            // 最长真周期长度 = len - 最短 border
    }

    cout << ans << '\n';

    return 0;
}
