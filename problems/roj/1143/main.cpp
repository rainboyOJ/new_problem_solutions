/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:20
 * update_at: 2026-10-05 03:20
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string line;          // 整行句子，包含字母、空格和逗号
string longest_word;  // 第一个最长的单词
string shortest_word; // 第一个最短的单词

// 判断一个字符是否为英文字母
bool is_letter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int main() {
    getline(cin, line);

    // 扫描整行，把连续字母段看成一个单词；只有严格更长/更短才更新，
    // 这样留下的自然是第一个最长、第一个最短的单词。
    ll i = 0;
    ll len = line.size();
    while (i < len) {
        if (!is_letter(line[i])) {
            i++;
            continue;
        }
        string word = "";
        while (i < len && is_letter(line[i])) {
            word += line[i];
            i++;
        }
        if (word.size() > longest_word.size()) {
            longest_word = word;
        }
        if (shortest_word == "" || word.size() < shortest_word.size()) {
            shortest_word = word;
        }
    }

    cout << longest_word << "\n";
    cout << shortest_word << "\n";
    return 0;
}
