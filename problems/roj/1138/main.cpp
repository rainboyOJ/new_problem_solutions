/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:07
 * update_at: 2026-10-05 03:07
 */
#include <cstdio>
#include <cctype>

// 题目：将字符串中的小写字母转换成大写字母（行内空格与非字母字符原样保留）。
// 思路：整行读入后逐字符扫描，小写字母减 32 转大写，其余字符原样输出。

const int MAXN = 105; // 串长不超过 100，预留一位放 '\0'
char buf[MAXN];

int main() {
    // fgets 读整行，遇到换行停止，行内空格完整保留
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;

    for (int i = 0; buf[i] != '\0'; ++i) {
        // 跳过 fgets 读到的行末换行，避免污染输出
        if (buf[i] == '\n') break;
        if (buf[i] >= 'a' && buf[i] <= 'z') buf[i] = buf[i] - 32; // 小写 -> 大写
        putchar(buf[i]);
    }
    putchar('\n');
    return 0;
}
