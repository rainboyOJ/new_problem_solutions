/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:27
 * update_at: 2026-10-05 03:27
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 505;

char line[MAXN];   // 整行原文，空格是内容，必须保留
char ans[MAXN];    // 翻转后的结果串
char word[MAXN];   // 当前单词的缓冲区

int main() {
    // 空格是内容不是分隔符：用 fgets 整行读，保留行内空格
    if (fgets(line, MAXN, stdin) == NULL) {
        return 0;
    }
    // 去掉行末换行
    ll len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
        len--;
    }
    line[len] = '\0';

    // 扫描整行：非空格字符进缓冲区，遇到空格就反转结算，空格原样保留
    ll ans_len = 0;  // ans 的当前长度
    ll word_len = 0; // word 缓冲区当前长度
    for (ll i = 0; i < len; i++) {
        if (line[i] != ' ') {
            word[word_len++] = line[i]; // 累积单词字符
        } else {
            // 结算当前单词：逆序追加到结果
            for (ll j = word_len - 1; j >= 0; j--) {
                ans[ans_len++] = word[j];
            }
            word_len = 0;
            ans[ans_len++] = ' '; // 空格原样保留，连续空格也走这里
        }
    }
    // 行尾兜底：最后一个单词后面没有空格，单独结算
    for (ll j = word_len - 1; j >= 0; j--) {
        ans[ans_len++] = word[j];
    }
    ans[ans_len] = '\0';

    printf("%s\n", ans);
    return 0;
}
