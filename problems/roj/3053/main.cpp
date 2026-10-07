/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:43
 * update_at: 2026-10-06 16:43
 */
// 最小覆盖子矩阵：覆盖 <=> 每行以 W 为周期且每列以 H 为周期，两个方向独立。
// 一维上：串有周期 p <=> 有长度 n-p 的 border，最小公共周期 = 串长 - 最长公共 border。
// 用 KMP 前缀函数沿 nxt 链取出每个串的全部 border 长度，多串求交集后取最大即可。

#include <cstdio>

typedef long long ll;

const int MAXR = 10005; // 行数上限（列串的长度上限）
const int MAXC = 80;    // 列数上限（行串的长度上限）

int R, C;
char grid[MAXR][MAXC]; // grid[i][j]：矩阵第 i 行第 j 列的字符（下标从 0 开始）
int nxt[MAXR + MAXC];  // KMP 前缀函数：nxt[i] = 串前 i 个字符的最长 border 长度
int cand[MAXR + MAXC]; // 候选公共 border 长度集合：第一个串的 border 链，之后逐串求交
int cand_n;            // 候选集合大小，cand[0] 恒为当前最长公共 border
bool seen[MAXR + MAXC]; // seen[b]：当前串的 border 链上是否出现过长度 b（求交时用）

// 计算串 s（长度 n）的前缀函数 nxt
void kmp_nxt(const char s[], int n) {
    nxt[0] = 0;
    nxt[1] = 0;
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j && s[i] != s[j]) j = nxt[j];
        if (s[i] == s[j]) j++;
        nxt[i + 1] = j;
    }
}

// 用第一个串初始化候选集合：border 的 border 仍是 border，
// 沿 nxt[n] -> nxt[nxt[n]] -> ... 的链恰好取遍全部 border 长度。
// 额外放入长度 0 的平凡 border，对应"周期 = 整段长度"，保证任何情况都有答案。
void init_cand(const char s[], int n) {
    kmp_nxt(s, n);
    cand_n = 0;
    for (int b = nxt[n]; b; b = nxt[b]) cand[cand_n++] = b;
    cand[cand_n++] = 0;
}

// 把候选集合与串 s 的 border 集合求交：交集里的最长者即当前最长公共 border
void intersect_cand(const char s[], int n) {
    kmp_nxt(s, n);
    for (int i = 0; i < cand_n; i++) seen[cand[i]] = false; // 清空候选标记
    for (int b = nxt[n]; b; b = nxt[b]) seen[b] = true;     // 标记 s 实际拥有的 border
    int m = 0;
    for (int i = 0; i < cand_n; i++)
        if (seen[cand[i]]) cand[m++] = cand[i]; // 保留仍公共的候选，cand[0] 仍是最大
    cand_n = m;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) scanf("%s", grid[i]);

    // 行方向：每行看成长 C 的串，求最小公共周期 W = C - 最长公共 border
    init_cand(grid[0], C);
    for (int i = 1; i < R; i++) intersect_cand(grid[i], C);
    int W = C - cand[0];

    // 列方向：把每一列拼成长 R 的串，同样求最小公共周期 H = R - 最长公共 border
    static char col[MAXR]; // col：当前列拼成的一维串
    for (int i = 0; i < R; i++) col[i] = grid[i][0];
    init_cand(col, R);
    for (int j = 1; j < C; j++) {
        for (int i = 0; i < R; i++) col[i] = grid[i][j];
        intersect_cand(col, R);
    }
    int H = R - cand[0];

    // 高、宽互不影响，最小覆盖子矩阵面积 = H * W
    printf("%d\n", H * W);
    return 0;
}
