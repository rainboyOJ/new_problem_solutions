/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:19
 * update_at: 2026-10-06 09:19
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 5005;   // 字典中单词数量的上限
const int MAXL = 32;     // 单个单词与数字串的最大长度

string words[MAXN];      // 字典中的单词，输入时按字典序给出
char words_len[MAXN];    // 每个单词的长度，避免反复调用 size()
char digit_of[128];      // digit_of[ch] = 字母 ch 对应的按键数字字符

// 把单词的每个字母翻译成按键数字，结果写入 buf 并返回长度。
int word_to_digits(const string &w, char *buf) {
    int len = w.size();
    for (int i = 0; i < len; i++) {
        buf[i] = digit_of[(int)w[i]];
    }
    return len;
}

int main() {
    // 建立字母到按键数字的映射（Q 与 Z 不在键盘上）
    const char *letters = "ABCDEFGHIJKLMNOPRSTUVWXY";
    const char *digits = "222333444555666777888999";
    for (int i = 0; letters[i] != '\0'; i++) {
        digit_of[(int)letters[i]] = digits[i];
    }

    // 输入前部是字典单词，最后一个串是目标数字串
    int word_cnt = 0;
    string target;
    string token;
    if (!(cin >> target)) {
        return 0;   // 空输入不输出
    }
    while (cin >> token) {
        words[word_cnt] = target;
        words_len[word_cnt] = target.size();
        word_cnt++;
        target = token;
    }

    int target_len = target.size();
    char buf[MAXL];
    bool found = false;

    // 字典本身按字典序排列，顺序扫描得到的答案天然有序
    for (int i = 0; i < word_cnt; i++) {
        if (words_len[i] != target_len) {
            continue;
        }
        int len = word_to_digits(words[i], buf);
        bool same = true;
        for (int j = 0; j < len; j++) {
            if (buf[j] != target[j]) {
                same = false;
                break;
            }
        }
        if (same) {
            cout << words[i] << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "NONE" << "\n";
    }

    return 0;
}
