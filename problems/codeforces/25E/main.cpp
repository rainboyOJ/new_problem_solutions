/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* CF25E Test */
/* 枚举 3! 种拼接顺序，每次把新串尽量重叠地接到当前串后面。
 * 重叠 = 左串后缀与右串前缀的最大公共长度，用 rbook 的前缀函数模板求解：
 * 对 right + '#' + left 求 pi，'#' 保证 border 不跨界，最后一位 pi 值即重叠。 */

#include <bits/stdc++.h>
using namespace std;

// 前缀函数模板（原样取自 rbook 文章《KMP 字符串匹配》）
// pi[i]：pattern[0..i] 的最长相等真前后缀长度，pi[0] = 0
vector<int> build_prefix_function(const string &pattern) {
    int m = (int)pattern.size();
    vector<int> pi(m, 0);

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) j++;
        pi[i] = j;
    }

    return pi;
}

// 返回 left 的后缀与 right 的前缀的最大重叠长度
int overlap(const string &left, const string &right) {
    // '#' 不在小写字母表中，整串 right#left 的 border 不可能跨过它，
    // 所以 border 长度 k 恰好满足：prefix(right, k) = suffix(left, k)
    string t = right + "#" + left;
    vector<int> pi = build_prefix_function(t);
    return pi.back();
}

// 判断 pattern 是否是 text 的子串（KMP 匹配，rbook 模板的匹配循环）
bool contains(const string &text, const string &pattern) {
    int m = (int)pattern.size();
    if (m == 0)
        return true;
    vector<int> pi = build_prefix_function(pattern);
    int j = 0; // 已匹配的模式串前缀长度
    for (char ch : text) {
        while (j > 0 && ch != pattern[j])
            j = pi[j - 1];
        if (ch == pattern[j])
            j++;
        if (j == m)
            return true; // 匹配完整
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s[3];
    cin >> s[0] >> s[1] >> s[2];

    int p[3] = {0, 1, 2};
    int ans = INT_MAX;
    do {
        string cur = s[p[0]];
        for (int i = 1; i < 3; i++) {
            const string &nxt = s[p[i]];
            if (contains(cur, nxt))
                continue;                        // nxt 已被 cur 包含
            if (contains(nxt, cur)) {            // cur 被 nxt 包含，直接替换
                cur = nxt;
                continue;
            }
            cur += nxt.substr(overlap(cur, nxt)); // 只拼上不重叠的部分
        }
        ans = min(ans, (int)cur.size());
    } while (next_permutation(p, p + 3));

    cout << ans << '\n';
    return 0;
}
