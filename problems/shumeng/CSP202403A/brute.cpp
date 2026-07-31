/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:40
 */
// brute.cpp：小数据暴力解，使用集合记录单篇文章出现过的单词。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> article_count(m + 1, 0);
    vector<int> total_count(m + 1, 0);
    for (int article = 1; article <= n; article++) {
        int length;
        cin >> length;
        set<int> appeared;
        for (int j = 0; j < length; j++) {
            int word;
            cin >> word;
            total_count[word]++;
            appeared.insert(word);
        }
        for (set<int>::iterator it = appeared.begin(); it != appeared.end(); ++it) {
            article_count[*it]++;
        }
    }
    for (int word = 1; word <= m; word++) {
        cout << article_count[word] << ' ' << total_count[word] << '\n';
    }

    return 0;
}
