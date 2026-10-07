/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:32
 * update_at: 2026-10-06 15:32
 */
#include <cstdio>
#include <cstring>

// 后缀数组（倍增 + 计数排序），n <= 3e5。
// 下标、排名都小于 2^31，统一用 int，数组更省内存、访问更快。

typedef long long ll;

const int MAXN = 300005;

char s[MAXN];           // 输入字符串，下标 0 ~ n-1
int n;                  // 串长
int sa[MAXN];           // sa[i] = 字典序排名第 i 的后缀的起始下标
int rk[MAXN * 2];       // rk[i] = 后缀 i 的排名；后半段预留为 0，充当“越界最小哨兵”
int old_rk[MAXN * 2];   // 上一轮排名，用来比较两关键字是否相同
int id[MAXN];           // 按第二关键字排好序的后缀下标
int cnt[MAXN + 1];      // 计数排序的桶
int height[MAXN];       // height[i] = sa[i] 与 sa[i-1] 的最长公共前缀，height[0] = 0

// 倍增构造 sa：每轮把「长度 w 的排名」升级成「长度 2w 的排名」。
void build_sa() {
    // 第一轮：按单个字符排序，排名从 1 开始，于是 0 天然是比任何真实排名都小的哨兵。
    int m = 256;
    for (int i = 0; i <= m; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) {
        rk[i] = (unsigned char)s[i] + 1;
        cnt[rk[i]]++;
    }
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[i]]] = i;

    for (int w = 1;; w <<= 1) {
        // 按第二关键字 rk[i+w] 排序：越界者第二关键字为 0，排最前；其余按上一轮 sa 顺序取出。
        int p = 0;
        for (int i = n - w; i < n; i++) {
            if (i >= 0) id[p++] = i;
        }
        for (int i = 0; i < n; i++) {
            if (sa[i] >= w) id[p++] = sa[i] - w;
        }
        // 按第一关键字 rk 对 id 做稳定计数排序，得到新的 sa。
        for (int i = 0; i <= m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[rk[id[i]]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[id[i]]]] = id[i];

        // 两个关键字都相同的后缀合并成同一个新排名。
        for (int i = 0; i < n; i++) old_rk[i] = rk[i];
        int classes = 1;
        rk[sa[0]] = 1;
        for (int i = 1; i < n; i++) {
            if (old_rk[sa[i]] != old_rk[sa[i - 1]] ||
                old_rk[sa[i] + w] != old_rk[sa[i - 1] + w]) {
                classes++;
            }
            rk[sa[i]] = classes;
        }
        if (classes == n) break;  // n 个排名两两不同，后缀顺序已经唯一确定
        m = classes;
    }

    // 统一转成 0 基排名，方便后面 Height 的下标运算。
    for (int i = 0; i < n; i++) rk[i]--;
}

// Kasai 算法求 height：利用 height[rk[i]] >= height[rk[i-1]] - 1 的性质线性扫描。
void build_height() {
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rk[i] == 0) {
            h = 0;
            continue;  // 排名第 0 的后缀没有前一个后缀
        }
        int j = sa[rk[i] - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        height[rk[i]] = h;
        if (h > 0) h--;
    }
}

int main() {
    if (scanf("%s", s) != 1) return 0;
    n = strlen(s);

    build_sa();
    build_height();

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", sa[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", height[i]);
    }
    printf("\n");
    return 0;
}
