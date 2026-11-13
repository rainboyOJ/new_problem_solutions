/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 15:14
 * update_at: 2026-11-13 15:14
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int maxn = 1000000 + 50;

// dp[i] 记录所有以位置 i 为起点的子串的 f 值之和
long long dp[maxn];

void solve() {
    int n;
    if (!(cin >> n)) return;
    string s;
    cin >> s;

    // 局部清空边界，避免全局 memset 导致多测超时
    for (int i = 0; i <= n + 5; ++i) {
        dp[i] = 0;
    }

    // 后缀贡献动态规划：从后往前倒推
    long long total_ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '0') {
            // '0' 自身是长度为 1 的单点众数，不需要消耗新的 1，完全继承 i + 1 的贡献
            dp[i] = dp[i + 1];
        } else {
            // '1' 必须在此处放置一个覆盖块，贪心放在 i + 1 处覆盖连续 3 格 [i, i+1, i+2]
            // 该覆盖块对后面所有以 i 开头且终点在 i..n-1 的子串均贡献 +1（共有 n - i 个子串）
            // 贪心指针随即跳跃至 i + 3，后续决策直接继承 dp[i + 3]
            dp[i] = dp[i + 3] + (n - i);
        }
        total_ans += dp[i];
    }

    cout << total_ans << "\n";
}

int main() {
    // 提升标准流输入输出性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
