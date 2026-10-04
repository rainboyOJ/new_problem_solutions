/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:52
 * update_at: 2026-10-05 02:52
 */

// KMP 求所有前缀的最大周期长度之和：
// 前缀 A(长度 i) 的周期 Q(长度 q) <=> A 有长度 b = i - q 的正 border，
// 所以最大周期 = i - 最短正 border。沿 next 失配链 + 路径压缩 O(n) 求出。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 1000005;

int n;                      // 串长
char s[MAXN];               // 输入串，下标从 1 开始
int nxt[MAXN];              // KMP 失配数组：nxt[i] = 前缀 s[1..i] 的最长非平凡 border 长度
int min_border[MAXN];       // min_border[i] = 前缀 s[1..i] 的最短正 border 长度（0 表示没有）

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);

    // 求 next 数组
    nxt[1] = 0;
    int j = 0;
    for (int i = 2; i <= n; i++) {
        while (j > 0 && s[i] != s[j + 1]) j = nxt[j];
        if (s[i] == s[j + 1]) j++;
        nxt[i] = j;
    }

    // 路径压缩求每个前缀的最短正 border：
    // 若 nxt[i] 自己已有更短的 border 就继承，否则 nxt[i] 就是最短的
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (nxt[i] == 0) {
            min_border[i] = 0; // 没有任何 border，最大周期为空串
        } else {
            if (min_border[nxt[i]] > 0)
                min_border[i] = min_border[nxt[i]];
            else
                min_border[i] = nxt[i];
            ans += i - min_border[i]; // 最大周期长度 = i - 最短正 border
        }
    }

    printf("%lld\n", ans);
    return 0;
}
