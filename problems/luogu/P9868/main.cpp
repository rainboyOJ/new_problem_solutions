/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:10
 * update_at: 2026-11-10 23:10
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 特殊情况：n = 1 时自然成立
    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    vector<string> min_s(n);
    vector<string> max_s(n);

    // 读入并分别构造升序串与降序串
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        // 桶计数排序
        int cnt[26] = {0};
        for (char c : s) {
            cnt[c - 'a']++;
        }

        min_s[i].reserve(m);
        for (int c = 0; c < 26; ++c) {
            min_s[i].append(cnt[c], static_cast<char>('a' + c));
        }

        max_s[i].reserve(m);
        for (int c = 25; c >= 0; --c) {
            max_s[i].append(cnt[c], static_cast<char>('a' + c));
        }
    }

    // 找出所有降序串中的最小值下标 p1 和次小值下标 p2
    int p1 = -1, p2 = -1;
    for (int i = 0; i < n; ++i) {
        if (p1 == -1 || max_s[i] < max_s[p1]) {
            p2 = p1;
            p1 = i;
        } else if (p2 == -1 || max_s[i] < max_s[p2]) {
            p2 = i;
        }
    }

    // 判断每个单词是否能成为最小
    string ans = "";
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
        int opponent = (i == p1 ? p2 : p1);
        if (min_s[i] < max_s[opponent]) {
            ans.push_back('1');
        } else {
            ans.push_back('0');
        }
    }

    cout << ans << "\n";

    return 0;
}
