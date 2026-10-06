/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:31
 * update_at: 2026-10-06 15:31
 */
// main.cpp：KMP 前缀函数求每个前缀的最短周期。
// 长度为 i 的前缀，最短周期 period = i - nxt[i]（nxt[i] 是最长 border 长度）；
// 当 nxt[i] > 0（保证 K > 1）且 period 整除 i 时，前缀恰好由 K = i / period 个循环节拼成。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 1000005;

int n;              // 当前测试数据的字符串长度
char s[MAXN];       // 字符串，下标从 1 开始
int nxt[MAXN];      // nxt[i]：s[1..i] 的最长「真前缀 = 真后缀」长度（border）

// 一趟线性求出整个 nxt 数组：从 nxt[i-1] 沿失配链回跳，看能否接上 s[i]。
void get_next() {
    nxt[1] = 0;
    int j = 0; // j 是当前尝试的 border 长度，也是失配链游标
    for (int i = 2; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = nxt[j]; // 失配就回跳到更短的 border
        if (s[i] == s[j + 1]) j++;
        nxt[i] = j;
    }
}

int main() {
    int case_id = 0;
    while (scanf("%d", &n) == 1 && n != 0) {
        scanf("%s", s + 1);
        get_next();

        printf("Test case #%d\n", ++case_id);
        for (int i = 2; i <= n; i++) {
            int period = i - nxt[i]; // 最短周期 = 长度 - 最长 border 长度
            // nxt[i] > 0 保证 K > 1；period 整除 i 保证前缀能被循环节整分
            if (nxt[i] > 0 && i % period == 0)
                printf("%d %d\n", i, i / period);
        }
        printf("\n"); // 每组数据末尾输出一个空行
    }
    return 0;
}
