/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 01:45
 * update_at: 2026-10-07 01:57
 */
// 这是 STL 写法：把目标词和文章都转成小写，再在两端各补一个空格，
// 然后用 string::find 反复查找 " " + word + " "，用 string::npos 判断是否还要继续。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string target_word;     // 第一行给出的目标单词（转小写后）
string article;         // 第二行给出的文章（转小写后）
string padded_word;     // " " + target_word + " "，两端补空格，把“单词边界”变成普通子串匹配
string padded_article;  // " " + article + " "，让文章开头和结尾的单词也有边界空格

// 大写字母转小写，其他字符原样返回。
char to_lower_char(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return char(ch - 'A' + 'a');
    }
    return ch;
}

// 把字符串 s 里的大写字母全部改成小写。
void to_lower_string(string& s) {
    ll len = s.size();
    for (ll i = 0; i < len; i++) {
        s[i] = to_lower_char(s[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, target_word); // 文章里含空格，两行都必须整行读入
    getline(cin, article);

    to_lower_string(target_word);
    to_lower_string(article);

    padded_word = " " + target_word + " ";
    padded_article = " " + article + " ";

    ll match_count = 0;    // 整词匹配出现的次数
    size_t first_pos = string::npos; // 第一次出现的位置（原文下标）；npos 表示还没出现过

    // 补空格后，padded_word 的第一个字符就是单词左边的那个空格，
    // 所以 find 返回的下标正好是单词首字母在原文里的位置（位置从 0 开始）。
    // 每次从 pos + 1 继续找，这样长度为 1 的单词（如 "a" 在 "a a" 里）也能全部数到。
    size_t pos = padded_article.find(padded_word);
    while (pos != string::npos) {
        match_count++;
        if (first_pos == string::npos) {
            first_pos = pos;
        }
        pos = padded_article.find(padded_word, pos + 1);
    }

    if (first_pos == string::npos) {
        cout << -1 << '\n';
    }
    else {
        cout << match_count << ' ' << first_pos << '\n';
    }

    return 0;
}
