/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，用集合记录单篇文章出现过的单词，避免同一篇文章重复统计。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100005;

int n, m;
int article_count[MAXM]; // article_count[word] 表示单词 word 出现在多少篇文章中
int total_count[MAXM];   // total_count[word] 表示单词 word 在所有文章中出现的总次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int article = 1; article <= n; article++) {
        int length;
        cin >> length;
        set<int> appeared; // 当前这篇文章出现过的单词，set 保证同一单词只记录一次
        for (int j = 0; j < length; j++) {
            int word;
            cin >> word;
            total_count[word]++;
            appeared.insert(word);
        }
        // 文章读完后再把每个出现过的单词文章数加一
        for (set<int>::iterator it = appeared.begin(); it != appeared.end(); ++it) {
            article_count[*it]++;
        }
    }

    for (int word = 1; word <= m; word++) {
        cout << article_count[word] << ' ' << total_count[word] << '\n';
    }

    return 0;
}