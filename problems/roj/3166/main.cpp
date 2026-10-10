/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 09:30
 * update_at: 2026-10-09 13:30
 */
// 3166 旅行：求两个字符串的【全部不同】最长公共子序列，按字典序升序输出。
// 做法：后缀型 LCS DP + 每个位置「不小于 i 的第一个字符 c」表，
// 在最优路径上按 a~z 枚举跳转 ⇒ 每个不同的 LCS 恰好生成一次（不重不漏）。

#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

const int MAX_LEN = 85;   // 题面单串长度不超过 80
const int ALPHA = 26;

int dp[MAX_LEN][MAX_LEN];   // dp[i][j] = s1[i..n] 与 s2[j..m] 的 LCS 长度，值 <= 80，int 够
ll nxt1[MAX_LEN][ALPHA];    // nxt1[i][c] = 下标 >= i 的第一个字符 c，没有则 n + 1
ll nxt2[MAX_LEN][ALPHA];    // 下标统一用 ll，和 n、m、dfs 的参数保持一致，不做强制转换
char route[MAX_LEN];        // 当前正在拼装的路线
const char LETTER[ALPHA + 1] = "abcdefghijklmnopqrstuvwxyz";
string s1, s2;
ll n, m, lcs_len;

// i、j 是两侧下一个可用下标（1 基），len 是「还要选」的字符数
void dfs(ll i, ll j, ll len) {
    if (len == 0) {
        cout << route << "\n";
        return;
    }
    ll pos = lcs_len - len;    // 本次要填 route 的第 pos 位
    for (int c = 0; c < ALPHA; ++c) {
        ll ni = nxt1[i][c];
        ll nj = nxt2[j][c];
        // 取字符 c 后仍在最优路径上：跳过 c 之后剩下的部分必须正好还能凑出 len - 1 个
        if (ni <= n && nj <= m && dp[ni + 1][nj + 1] == len - 1) {
            route[pos] = LETTER[c];
            dfs(ni + 1, nj + 1, len - 1);
        }
    }
}

void solve() {
    n = s1.length();
    m = s2.length();
    s1 = " " + s1;
    s2 = " " + s2;

    // 后缀型 LCS：s1[i] == s2[j] 时这条匹配必须用上，否则取两侧较大值
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= m + 1; ++j) {
            dp[i][j] = 0;
        }
    }
    for (ll i = n; i >= 1; --i) {
        for (ll j = m; j >= 1; --j) {
            if (s1[i] == s2[j]) {
                dp[i][j] = dp[i + 1][j + 1] + 1;
            } else if (dp[i + 1][j] >= dp[i][j + 1]) {
                dp[i][j] = dp[i + 1][j];
            } else {
                dp[i][j] = dp[i][j + 1];
            }
        }
    }

    lcs_len = dp[1][1];

    // 每个位置往后（含自身）第一个出现的字符，用于 O(1) 跳到下一个候选
    for (int c = 0; c < ALPHA; ++c) {
        nxt1[n + 1][c] = n + 1;
        nxt2[m + 1][c] = m + 1;
    }
    for (ll i = n; i >= 1; --i) {
        for (int c = 0; c < ALPHA; ++c) {
            if (s1[i] - 'a' == c) {
                nxt1[i][c] = i;
            } else {
                nxt1[i][c] = nxt1[i + 1][c];
            }
        }
    }
    for (ll j = m; j >= 1; --j) {
        for (int c = 0; c < ALPHA; ++c) {
            if (s2[j] - 'a' == c) {
                nxt2[j][c] = j;
            } else {
                nxt2[j][c] = nxt2[j + 1][c];
            }
        }
    }

    route[lcs_len] = '\0';
    dfs(1, 1, lcs_len);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> s1 >> s2) {
        solve();
    }
    return 0;
}
