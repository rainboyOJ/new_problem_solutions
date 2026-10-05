/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-05 10:38
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<string> words; // 存所有单词，读入后整体排序

// 求 a、b 的最长公共前缀长度
size_t lcp(const string &a, const string &b) {
    size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) i++;
    return i;
}

int main() {
    string s;
    while (cin >> s) {
        words.push_back(s);
    }

    // 字典序排序后，与前一单词的 LCP 就是与前面所有单词 LCP 的最大值，
    // 所以第 i 个单词新贡献的结点（前缀）数 = 长度 - 相邻 LCP；重复单词贡献 0。
    sort(words.begin(), words.end());

    ll ans = 1; // 1 是根结点
    ans += words[0].size(); // 第一个单词贡献全部前缀
    for (size_t i = 1; i < words.size(); i++) {
        ans += words[i].size() - lcp(words[i], words[i - 1]);
    }
    cout << ans << endl;
    return 0;
}
