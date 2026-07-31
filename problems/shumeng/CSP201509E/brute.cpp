/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:44
 */
// brute.cpp：枚举所有小文章，并在追加字符时统计以当前位置结尾的单词。
#include <bits/stdc++.h>
using namespace std;

int n, length;
vector<string> words;
vector<char> letters;
string article;
long long answer;

void dfs(int position, long long score) {
    if (position == length) {
        answer = max(answer, score);
        return;
    }
    for (int i = 0; i < (int)letters.size(); i++) {
        article += letters[i];
        long long added = 0;
        for (int j = 0; j < n; j++) {
            int word_length = words[j].size();
            if ((int)article.size() >= word_length &&
                article.substr(article.size() - word_length) == words[j]) added++;
        }
        dfs(position + 1, score + added);
        article.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> length;
    words.resize(n);
    int used[26] = {};
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        for (int j = 0; j < (int)words[i].size(); j++) used[words[i][j] - 'a'] = 1;
    }
    for (int i = 0; i < 26; i++) if (used[i]) letters.push_back('a' + i);
    dfs(0, 0);
    cout << answer << '\n';
    return 0;
}
