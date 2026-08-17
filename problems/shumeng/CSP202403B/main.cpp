/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

// 把单词统一成小写：忽略大小写差异后才能把同一个单词去重
string normalize(const string &word) {
    string result = word;
    for (int i = 0; i < (int)result.size(); i++) {
        if ('A' <= result[i] && result[i] <= 'Z') result[i] += 'a' - 'A';
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 哈希集合保存两篇文章各自去重后的单词，平均 O(1) 插入与查询
    unordered_set<string> set_a, set_b;
    string word;
    for (int i = 0; i < n; i++) {
        cin >> word;
        set_a.insert(normalize(word));
    }
    for (int i = 0; i < m; i++) {
        cin >> word;
        set_b.insert(normalize(word));
    }

    // 交集大小：统计同时在两篇文章集合中出现的单词数
    int intersection = 0;
    for (unordered_set<string>::const_iterator it = set_a.begin(); it != set_a.end(); ++it) {
        if (set_b.count(*it)) intersection++;
    }

    // 并集大小由容斥公式得到：|A ∪ B| = |A| + |B| - |A ∩ B|
    cout << intersection << '\n';
    cout << set_a.size() + set_b.size() - intersection << '\n';

    return 0;
}