/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:32
 * update_at: 2026-10-05 03:32
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string s;            // 读入的整行句子
string best_word;    // 当前找到的最长单词
ll best_len;         // 当前最长单词的长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入整行，句末 '.' 是标点不是单词的一部分，先去掉
    getline(cin, s);
    if (!s.empty() && s.back() == '.') s.pop_back();

    string word;     // 当前正在拼的单词
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            if (!word.empty()) {
                // 严格更长才替换，相等时保留先到者
                if ((ll) word.size() > best_len) {
                    best_len = (ll) word.size();
                    best_word = word;
                }
                word.clear();
            }
        } else {
            word.push_back(s[i]);
        }
    }
    // 句尾最后一个单词（如果输入不是以空格结尾）
    if (!word.empty()) {
        if ((ll) word.size() > best_len) {
            best_len = (ll) word.size();
            best_word = word;
        }
    }

    cout << best_word << "\n";
    return 0;
}
