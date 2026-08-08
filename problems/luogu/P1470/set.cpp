/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-01 23:57
 * update_at: 2026-08-01 23:57
 */

// ============ set 解法 ============
// 与 hash.cpp 完全相同的 DP 思路，区别只在于"后缀是否在词集中"的查找方式：
//   hash.cpp：unordered_set，哈希查询，平均 O(1)
//   本文件：  set<string>，有序集合，查询 O(log |P|) 次字符串比较
// 词集只有最多 200 个词、词长 <= 10，红黑树查询的开销可以忽略。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入词集 P：以单独一行 "." 结束
    set<string> words;
    string word;
    while (cin >> word && word != ".") {
        words.insert(word);
    }

    // 读入 S：每 76 个字符一行，必须拼成完整串
    string S, line;
    while (cin >> line) S += line;

    int n = (int)S.size();
    vector<char> dp(n + 1, false);
    dp[0] = true;               // 空前缀可拆
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        // 枚举最后一个词的长度 len（词长 <= 10）
        for (int len = 1; len <= 10 && i - len >= 0; len++) {
            // 两个条件同时满足：后缀是词，且前缀 S[0..i-len) 能拆开
            if (dp[i - len] && words.count(S.substr(i - len, len))) {
                dp[i] = true;
                break;          // 找到一个拆法即可
            }
        }
        if (dp[i]) ans = i;     // dp 不单调，取所有可达位置的最大值
    }

    cout << ans << '\n';
    return 0;
}
