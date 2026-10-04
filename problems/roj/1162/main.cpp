/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:57
 * update_at: 2026-10-05 03:57
 */

// main.cpp：读取以 '!' 结尾的一行字符串，输出 '!' 之前字符的逆序。
// 思路：把整行读到字符数组里，找到 '!' 的位置（或者读到末尾），把前面那段逆序输出。

#include <cstdio>

const int MAXN = 1005;       // 输入长度上限，远超题目实际规模

char buf[MAXN];              // 读入缓冲区

int main() {
    // 用 fgets 读一整行，保留换行符；后面再处理
    if (fgets(buf, sizeof(buf), stdin) == 0) return 0;

    int n = 0;               // '!' 之前的有效字符数
    for (int i = 0; buf[i] != '\0' && buf[i] != '!'; ++i) {
        ++n;
    }

    // 从后往前输出 '!' 之前的 n 个字符
    for (int i = n - 1; i >= 0; --i) {
        putchar(buf[i]);
    }
    putchar('\n');
    return 0;
}