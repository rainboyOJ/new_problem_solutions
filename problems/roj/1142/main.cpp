/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:21
 * update_at: 2026-10-05 03:21
 */
// main.cpp：把"未被空格隔开的连续符号串"看作单词，统计每个单词的长度并逗号输出。
// 思路：整行读入后逐字符扫描。维护"是否正在单词内"标志，遇到空格结束当前单词并输出长度。
//       行首/词间的连续空格都自动跳过；行末若停在单词内，最后再补一次输出。

#include <cstdio>

typedef long long ll;

const int MAXL = 1005; // 输入行总长不超过 1000
char buf[MAXL];

int main() {
    // fgets 整行读入，保留行内空格，遇到换行或 EOF 停止
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;

    ll first = 1;        // 标记是否尚未输出过单词，控制逗号不前置
    ll in_word = 0;      // 当前是否处于单词内
    ll cur_len = 0;      // 当前单词已累计的字符数

    for (ll i = 0; buf[i] != '\0'; i++) {
        char c = buf[i];
        if (c == '\n') break; // 行末换行属于读入残留，停止扫描
        if (c == ' ') {
            // 遇到空格：如果正在单词中，先把当前单词长度结算掉
            if (in_word) {
                if (!first) putchar(',');
                printf("%lld", cur_len);
                first = 0;
                in_word = 0;
                cur_len = 0;
            }
            // 连续空格保持 in_word == 0，自动被跳过
        } else {
            // 非空格字符累计到当前单词
            in_word = 1;
            cur_len++;
        }
    }

    // 行末若正好停在单词内部，再补一次输出
    if (in_word) {
        if (!first) putchar(',');
        printf("%lld", cur_len);
    }
    putchar('\n');
    return 0;
}