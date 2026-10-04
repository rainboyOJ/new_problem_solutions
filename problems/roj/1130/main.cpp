/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:53
 * update_at: 2026-10-05 02:53
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

// freq[c] 记录字符 c 的出现次数；字符集仅含小写字母，共 26 个。
int freq[26];
char s[MAXN];

void solve() {
    // 读入整行字符串（可能含空格，但题目限定只含小写字母，单词读入即可）。
    // 注意：cin >> s 会在空白处停下，需要先吃掉前导空白再读。
    int n = 0;
    char ch;
    while (cin.get(ch)) {
        if (ch == '\n' || ch == '\r') break;
        if (ch >= 'a' && ch <= 'z') {
            s[n++] = ch;
        }
    }
    // 第一遍：统计每个小写字母的频次。
    for (int i = 0; i < n; i++) {
        freq[s[i] - 'a']++;
    }
    // 第二遍：按原串位置序回扫，第一个频次为 1 的字符就是答案。
    for (int i = 0; i < n; i++) {
        if (freq[s[i] - 'a'] == 1) {
            cout << s[i] << "\n";
            return;
        }
    }
    cout << "no\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
