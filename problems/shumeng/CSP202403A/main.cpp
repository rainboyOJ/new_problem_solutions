/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100005;

int n, m;
int article_count[MAXM]; // article_count[word] 表示单词 word 出现在多少篇文章中
int total_count[MAXM];   // total_count[word] 表示单词 word 在所有文章中出现的总次数
int last_article[MAXM];  // last_article[word] 表示单词 word 最近一次统计文章数的文章编号

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int article = 1; article <= n; article++) {
        int length;
        cin >> length;
        for (int j = 0; j < length; j++) {
            int word;
            cin >> word;
            total_count[word]++;
            // 同一个单词在同一篇文章中只统计一次文章数
            if (last_article[word] != article) {
                last_article[word] = article;
                article_count[word]++;
            }
        }
    }

    for (int word = 1; word <= m; word++) {
        cout << article_count[word] << ' ' << total_count[word] << '\n';
    }

    return 0;
}