/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:45
 */
// brute.cpp：小数据暴力解，使用有序集合保存统一大小写后的单词。
#include <bits/stdc++.h>
using namespace std;

string normalize(string word) {
    for (int i = 0; i < (int)word.size(); i++) {
        if ('A' <= word[i] && word[i] <= 'Z') word[i] += 'a' - 'A';
    }
    return word;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    set<string> first, second;
    string word;
    for (int i = 0; i < n; i++) {
        cin >> word;
        first.insert(normalize(word));
    }
    for (int i = 0; i < m; i++) {
        cin >> word;
        second.insert(normalize(word));
    }
    int intersection = 0;
    for (set<string>::const_iterator it = first.begin(); it != first.end(); ++it) {
        if (second.count(*it)) intersection++;
    }
    cout << intersection << '\n';
    cout << first.size() + second.size() - intersection << '\n';

    return 0;
}
