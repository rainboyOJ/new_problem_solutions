/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:33
 * update_at: 2026-10-06 14:33
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string word, article;

// 把 c 转成小写
inline char lower(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c;
}

// 判断 c 是否为字母
inline bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, word);
    getline(cin, article);

    // 统一转小写
    for (size_t i = 0; i < word.size(); ++i) word[i] = lower(word[i]);
    for (size_t i = 0; i < article.size(); ++i) article[i] = lower(article[i]);

    ll m = word.size();
    ll n = article.size();
    ll cnt = 0;
    ll first = -1;

    // 在 article 中逐位检查是否匹配 word 且左右为单词边界
    for (ll i = 0; i + m <= n; ++i) {
        // 检查 article[i..i+m-1] 是否等于 word
        bool match = true;
        for (ll j = 0; j < m; ++j) {
            if (article[i + j] != word[j]) {
                match = false;
                break;
            }
        }
        if (!match) continue;

        // 左边界：i == 0 或 article[i-1] 不是字母
        if (i > 0 && is_alpha(article[i - 1])) continue;
        // 右边界：i + m == n 或 article[i+m] 不是字母
        if (i + m < n && is_alpha(article[i + m])) continue;

        ++cnt;
        if (first == -1) first = i;
    }

    if (cnt == 0) {
        cout << -1 << '\n';
    } else {
        cout << cnt << ' ' << first << '\n';
    }
    return 0;
}
