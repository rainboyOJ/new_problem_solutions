/**
 * P1246 编码
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

unsigned long long C[30][30]; // 组合数

int main() {
    // 组合数 DP
    for (int i = 0; i <= 26; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    char s[10];
    scanf("%s", s);
    int len = strlen(s);
    // 检查是否严格递增
    for (int i = 1; i < len; ++i)
        if (s[i] <= s[i - 1]) { puts("0"); return 0; }
    // 编码 = 所有更短单词数 + 同长度字典序排名
    unsigned long long rank = 0;
    // 累加长度 < len 的所有合法单词
    for (int l = 1; l < len; ++l) rank += C[26][l];
    // 同长度中，逐位确定
    int prev = 0; // 前一个字母的编号（0-based）
    for (int i = 0; i < len; ++i) {
        int cur = s[i] - 'a' + 1; // 当前字母编号（1-based）
        int remain = len - i - 1;
        // 在 prev+1 到 cur-1 中选 remain 个字母
        for (int c = prev + 1; c < cur; ++c)
            rank += C[26 - c][remain];
        prev = cur;
    }
    printf("%llu\n", rank + 1); // 排名从 1 开始
    return 0;
}
