#include <bits/stdc++.h>
using namespace std;

// ============ 哈希解法 ============
// 与 trie.cpp 完全相同的 DP 思路，区别只在于"后缀是否在词集中"的查找方式：
//   trie.cpp：倒序 Trie，从位置 i 往回走，边走边判断，可提前剪枝
//   本文件：  unordered_set，直接构造子串 S.substr(i-len, len) 后查集合
// 词长 <= 10，两种方式每个位置都只需 O(10)，复杂度同为 O(10*|S|)。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入词集 P：以单独一行 "." 结束
    unordered_set<string> words;
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
