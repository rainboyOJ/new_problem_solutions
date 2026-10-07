/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:32
 * update_at: 2026-10-06 11:32
 */
#include <cstdio>
#include <cstring>

typedef long long ll;

// 字符串哈希模板题：判断两个子串是否完全相同
const ll MOD = (1LL << 61) - 1; // 梅森素数 2^61-1，哈希值分布均匀，冲突概率可忽略
const ll BASE = 131;            // 哈希进制，比字符集大
const int MAXN = 1000005;

char s[MAXN];    // 输入字符串，下标从 1 开始
ll h[MAXN];      // h[i] = 前缀 s[1..i] 的哈希值（看成 BASE 进制数）
ll p[MAXN];      // p[i] = BASE^i mod MOD，用于对齐高位
ll ans[MAXN];    // 暂存每个询问的回答，0 表示 No，1 表示 Yes

// 取出子串 s[l..r] 的哈希值：减掉前缀 [1, l-1] 贡献的高位
ll sub_hash(int l, int r) {
    ll v = h[r] - h[l - 1] * p[r - l + 1] % MOD;
    if (v < 0) v += MOD; // 减法可能出现负数，手工调整到 [0, MOD)
    return v;
}

int main() {
    // 快读：m 可达 1e6，用 getchar 手写读入
    static char buf[MAXN];
    scanf("%s", buf + 1);
    int n = strlen(buf + 1);

    // 预处理前缀哈希和 BASE 的幂
    h[0] = 0;
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = (h[i - 1] * BASE + buf[i]) % MOD;
        p[i] = p[i - 1] * BASE % MOD;
    }

    int m;
    scanf("%d", &m);
    for (int q = 1; q <= m; q++) {
        int l1, r1, l2, r2;
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        // 子串相同等价于指纹相同
        ans[q] = (sub_hash(l1, r1) == sub_hash(l2, r2));
    }

    // 统一输出，避免 1e6 次 printf 拖慢速度
    for (int q = 1; q <= m; q++) {
        if (ans[q]) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
