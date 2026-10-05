/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:25
 * update_at: 2026-10-05 08:25
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 205; // 字符串长度上限 200

char x[MAXN], y[MAXN];
int prev_dp[MAXN];    // 上一行 DP 值
int cur_dp[MAXN];     // 当前行 DP 值

// 计算两个字符串的最长公共子序列长度，用滚动数组优化空间。
int lcs_len(char *a, char *b) {
    int n = strlen(a + 1); // a[1..n] 为有效字符
    int m = strlen(b + 1);
    // 让 a 是较短串，内层循环长度取 min(n, m)。
    if (n > m) {
        swap(a, b);
        swap(n, m);
    }
    memset(prev_dp, 0, sizeof(int) * (n + 1));
    for (int i = 1; i <= m; i++) {
        cur_dp[0] = 0; // 第 0 列恒为 0
        for (int j = 1; j <= n; j++) {
            if (b[i] == a[j]) {
                cur_dp[j] = prev_dp[j - 1] + 1; // 配对成功，继承左上角 +1
            } else if (prev_dp[j] > cur_dp[j - 1]) {
                cur_dp[j] = prev_dp[j];         // 丢掉 b[i]
            } else {
                cur_dp[j] = cur_dp[j - 1];      // 丢掉 a[j]
            }
        }
        memcpy(prev_dp, cur_dp, sizeof(int) * (n + 1));
    }
    return prev_dp[n];
}

int main() {
    while (scanf("%s %s", x + 1, y + 1) == 2) {
        printf("%d\n", lcs_len(x, y));
    }
    return 0;
}
