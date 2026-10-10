/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:04
 * update_at: 2026-10-09 00:14
 */
// 一本通 2047《【例5.16】过滤空格》
// 题意：一行字符串（长度 <= 200，句子的头和尾都没有空格），把句中每段连续空格
//       压缩成一个空格后输出。
// 考点：句中含空格 ⇒ 必须整行读入，不能用 cin >> s（会在第 1 个空格处截断）。
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string line;      // 读入的整行句子
bool last_space;  // 上一个输出的字符是不是空格，用来决定当前空格要不要丢弃

// 把 line 中每段连续空格压成一个后输出（边扫描边输出，辅助空间 O(1)）。
// 只有 ASCII 空格 ' ' 算题面所说的「空格」；Tab、\v、\f 不算，原样保留。
void print_compressed() {
    ll len = line.size();
    last_space = false;
    for (ll i = 0; i < len; i++) {
        if (line[i] == ' ') {
            if (last_space) {
                continue;   // 这一段空格已经输出过一个了，多余的丢掉
            }
            last_space = true;
        } else {
            last_space = false;
        }
        cout << line[i];
    }
}

// 整行读入。Windows 的 CRLF 数据在 Linux 评测时行尾会残留一个 '\r'，必须剔除。
// 返回 false 表示连一行都没有（无输入，也就不输出任何内容）。
bool read_input() {
    if (!getline(cin, line)) {
        return false;
    }
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    return true;
}

int main() {
    if (!read_input()) {
        return 0;
    }
    print_compressed();
    cout << "\n";
    return 0;
}
