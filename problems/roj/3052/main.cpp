/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:42
 * update_at: 2026-10-06 16:42
 */
#include <cstdio>
#include <cstring>

const int MAXL = 1000005; // 项链长度上限 10^6，多留一点空间

char a[MAXL]; // 第一条项链的描述
char b[MAXL]; // 第二条项链的描述

// 求循环串 s（长度为 n）的字典序最小旋转的起点下标。
// i、j 是两个候选起点，k 是当前已连续匹配的长度；
// 失配时落败的一方连同它后面的 k 个候选一起被淘汰，跳到 k+1 步之后，
// 每个起点至多被淘汰一次，因此均摊 O(n)。
int min_rotation(char *s, int n) {
    int i = 0;
    int j = 1;
    int k = 0;
    while (k < n && i < n && j < n) {
        char ci = s[(i + k) % n];
        char cj = s[(j + k) % n];
        if (ci == cj) {
            k++;
        } else {
            if (ci > cj) {
                i += k + 1; // 起点 i..i+k 全部落败，整体跳过
            } else {
                j += k + 1; // 起点 j..j+k 全部落败，整体跳过
            }
            if (i == j) {
                j++; // 两指针重合时错开
            }
            k = 0;
        }
    }
    return i < j ? i : j;
}

int main() {
    scanf("%s %s", a, b);
    int n = strlen(a);
    int pa = min_rotation(a, n);
    int pb = min_rotation(b, n);
    // 两条项链相同当且仅当它们的最小表示相同。
    int same = 1;
    for (int t = 0; t < n; t++) {
        if (a[(pa + t) % n] != b[(pb + t) % n]) {
            same = 0;
            break;
        }
    }
    if (same) {
        printf("Yes\n");
        for (int t = 0; t < n; t++) {
            putchar(a[(pa + t) % n]);
        }
        putchar('\n');
    } else {
        printf("No\n");
    }
    return 0;
}
