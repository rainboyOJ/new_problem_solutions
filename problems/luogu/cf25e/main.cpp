/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* CF25E Test */
/* 枚举 3! 种拼接顺序，每次把新串尽量重叠地接到当前串后面。 */
/* 重叠长度 = 对 right + '#' + left 求前缀函数，最后一位 pi 值。 */

#include <bits/stdc++.h>
using namespace std;

// 返回 left 的后缀与 right 的前缀的最大重叠长度
int overlap(const string &left, const string &right) {
    // '#' 不会出现在小写字母中，保证 border 不会跨过分隔符：
    // 整串 right#left 的 border 长度 k 满足 prefix(right,k) = suffix(left,k)
    string t = right + "#" + left;
    int m = (int)t.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j])
            j = pi[j - 1];
        if (t[i] == t[j])
            j++;
        pi[i] = j;
    }
    return pi[m - 1];
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
            if (cur.find(nxt) != string::npos)
                continue;                        // nxt 已被 cur 包含
            if (nxt.find(cur) != string::npos) { // cur 被 nxt 包含，直接替换
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
