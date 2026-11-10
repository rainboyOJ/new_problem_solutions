/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:06
 * update_at: 2026-11-11 00:06
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int p, k_parts;
int word_cnt;
string total_str;
vector<string> dict;

// sum_val[l][r] 表示子串 total_str[l..r] 内最多能选出的首字母不重叠的单词数
int sum_val[205][205];

// dp[i][j] 表示前 i 个字符分成 j 份的最大单词数
int dp[205][45];

// 检查是否存在以 l 开头、且完全落在 [l, r] 内的单词
bool check(int l, int r) {
    for (const string& w : dict) {
        int len = w.size();
        if (l + len - 1 <= r) {
            if (total_str.substr(l, len) == w) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> p >> k_parts)) return 0;

    total_str = " "; // 下标从 1 开始
    for (int i = 0; i < p; ++i) {
        string line;
        cin >> line;
        total_str += line;
    }

    cin >> word_cnt;
    dict.resize(word_cnt);
    for (int i = 0; i < word_cnt; ++i) {
        cin >> dict[i];
    }

    int n = total_str.size() - 1;

    // 预处理区间单词数：从右向左递推
    for (int r = 1; r <= n; ++r) {
        for (int l = r; l >= 1; --l) {
            sum_val[l][r] = sum_val[l + 1][r] + (check(l, r) ? 1 : 0);
        }
    }

    // 初始化 DP
    // dp[i][j] = -1 表示不可达
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k_parts; ++j) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;

    // 序列划分型 DP
    // 每部分至少 1 个字符，故前 i 个字符至少分 1 份，至多分 i 份
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, k_parts); ++j) {
            for (int prev = j - 1; prev < i; ++prev) {
                if (dp[prev][j - 1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[prev][j - 1] + sum_val[prev + 1][i]);
                }
            }
        }
    }

    cout << dp[n][k_parts] << "\n";

    return 0;
}
