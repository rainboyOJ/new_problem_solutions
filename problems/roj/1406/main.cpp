/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:02
 * update_at: 2026-10-05 23:02
 */
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

typedef long long ll;

int main() {
    // s 是原始文本，target 是待替换的单词，replacement 是替换成的单词
    string s, target, replacement;
    getline(cin, s);
    getline(cin, target);
    getline(cin, replacement);

    // 按空格逐词切分：只替换与 target 完全相同的独立单词，避免子串误伤
    istringstream in(s);
    string word;
    bool first_word = true;
    while (in >> word) {
        if (!first_word) {
            cout << ' ';
        }
        first_word = false;
        if (word == target) {
            cout << replacement;
        } else {
            cout << word;
        }
    }
    cout << '\n';

    return 0;
}
