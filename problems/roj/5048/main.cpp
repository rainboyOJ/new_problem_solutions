/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 23:31
 * update_at: 2026-10-08 23:31
 */
// 一本通 2046《【例5.15】替换字母》
// 题意：第 1 行是原文（可含空格，长度 <= 200），第 2 行是以空格分隔的两个字符
//       A 和 B；把原文中所有等于 A 的字符改成 B（区分大小写），输出一行结果。
// 考点：原文含空格 ⇒ 必须整行读入，不能用 cin >> s（会在第 1 个空格处截断）。
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string text;         // 第 1 行原文（整行读入，空格原样保留）
char old_ch = '\0';  // 要被替换掉的字符 A
char new_ch = '\0';  // 替换后的目标字符 B
bool has_ab = false; // 第 2 行是否成功读到 A、B（题面保证有，这里防御性判断）

// 读入两行：第 1 行整行读（保留空格），第 2 行取头两个非空白字符。
// 返回 false 表示连第 1 行都没有（无输入，也就无内容可输出）。
bool read_input() {
    if (!getline(cin, text)) {
        return false;
    }
    // Windows CRLF 数据在 Linux 评测时会在行尾残留 '\r'，必须剔除
    while (!text.empty() && text.back() == '\r') {
        text.pop_back();
    }
    // >> 会自动跳过空白（含换行），且每个变量只取 1 个字符，
    // 所以 `A B`、`A  B`、`AB` 三种写法都解析出同一对字符；
    // 缺第 2 行时 cin 置 fail 位，此时不改动原文，原样输出
    cin >> old_ch >> new_ch;
    has_ab = !cin.fail();
    return true;
}

// 把 text 中所有等于 old_ch 的字符原地换成 new_ch（区分大小写）
void replace_char() {
    ll len = text.size();
    for (ll i = 0; i < len; i++) {
        if (text[i] == old_ch) {
            text[i] = new_ch;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!read_input()) {
        return 0;
    }
    if (has_ab) {
        replace_char();
    }
    cout << text << "\n";
    return 0;
}
