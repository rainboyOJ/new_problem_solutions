// main.cpp：把回文 Manacher 的"相等"判据换成"不等"，统计反对称子串个数。
// 反对称串长度必为偶数，按缝隙统计：缝隙 g 的半径 f[g] = 两侧最多配出的
// "不等"对数，每个半径 1..f[g] 对应一个反对称子串，答案为 sum(f[g])。
// 用最靠右反对称区间做"镜像继承 + 右端截断"，总复杂度 O(n)。

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-13 15:42
 * update_at: 2026-10-13 15:42
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 500005;

int n;
char s[MAXN];   // s[i]：第 i 位字符（0..n-1），读入后存成 0/1 的 int 差值
int f[MAXN];    // f[g]：缝隙 g（夹在 s[g] 与 s[g+1] 之间）两侧最多配出的"不等"对数

int main() {
    scanf("%d %s", &n, s);
    for (int i = 0; i < n; ++i) s[i] -= '0'; // 转成数值，便于比较

    ll ans = 0;
    int l = 0, r = -1; // 已知最靠右的反对称区间 [l, r]，初始为空
    for (int i = 0; i < n - 1; ++i) {
        int k = 0;
        if (i < r) {
            // 镜像缝隙 l+r-1-i 必在左半边且已算出：
            // 取反不改变不等关系，故可继承 min(f[mirror], r-i)
            k = f[l + r - 1 - i];
            if (k > r - i) k = r - i; // 右端截断：继承的对必须落在 [l, r] 内
        }
        // 只有区间右端之外或首次失败的比较才真正执行，均摊 O(n)
        while (i - k >= 0 && i + 1 + k < n && s[i - k] != s[i + 1 + k]) k += 1;
        f[i] = k;
        ans += k; // 半径 1..k 各对应一个反对称子串
        if (k > 0 && i + k > r) { // 摸到更靠右的反对称区间才更新
            l = i - k + 1;
            r = i + k;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
