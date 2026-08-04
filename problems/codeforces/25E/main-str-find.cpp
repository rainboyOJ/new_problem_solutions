/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* CF25E Test —— 教学对照版：只用 string::find 与 substr 比较，不用 KMP */
/* 与 main.cpp（KMP 版）对比可以看出：
 *   包含判断用 find 很直接；但重叠只能从大到小暴力试 k 再比较子串，
 *   最坏 O(L^2)（例如三个全是相同字符的串）。 */

#include <bits/stdc++.h>
using namespace std;

// 返回 left 的后缀与 right 的前缀的最大重叠长度（暴力试 k）
int overlap(const string &left, const string &right) {
    int lim = min((int)left.size(), (int)right.size());
    for (int k = lim; k >= 1; k--)
        if (left.substr((int)left.size() - k) == right.substr(0, k))
            return k; // 从大到小第一个成功的 k 就是最大重叠
    return 0;
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
