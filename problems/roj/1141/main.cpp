/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:21
 * update_at: 2026-10-05 03:21
 */

#include <bits/stdc++.h>
using namespace std;

char s[40];           // 输入单词，长度不超过 32
const char *suffixes[] = {"er", "ly", "ing"}; // 题面给定的后缀集合

int main() {
    scanf("%s", s);
    int n = strlen(s); // 当前单词长度
    // 依次检查三个后缀，命中则删除并输出
    for (int i = 0; i < 3; i++) {
        int len = strlen(suffixes[i]);
        if (n >= len && strcmp(s + n - len, suffixes[i]) == 0) {
            s[n - len] = '\0';
            break;
        }
    }
    printf("%s\n", s);
    return 0;
}
