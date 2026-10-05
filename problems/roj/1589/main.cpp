/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:55
 * update_at: 2026-10-06 00:55
 */

// 不要 62：数位 DP，统计区间内不含数字 4 且不含子串 62 的数的个数。

#include <cstdio>

typedef long long ll;

const int LEN = 12; // 上界 x 最多约 10 位，开 12 位够用

ll digits[LEN]; // digits[1..len] 保存上界 x 从高到低的每一位
ll len;         // 上界 x 的位数
ll memo[LEN][2][2]; // memo[pos][tight][prev6]：已算过的状态直接返回，-1 表示没算过

// 从第 pos 位开始填（pos 从 1 到 len），返回合法后缀的个数。
// tight   = 1 表示前面每位都贴着 x 的上界，当前位最多取 x 的对应位；
// prev6   = 1 表示上一位填的是 6，当前位再填 2 就会拼出 62。
// 前导零不用特判：0 不是 4，也不会让 prev6 变成 1。
ll dfs(ll pos, ll tight, ll prev6) {
    if (pos > len)
        return 1; // 整数构造完成（0 本身也算一个，前缀相减时会消去）
    if (memo[pos][tight][prev6] != -1)
        return memo[pos][tight][prev6];
    ll up = 9; // 不贴上界时当前位可以随便取 0~9
    if (tight)
        up = digits[pos]; // 贴上界时最多取 x 的对应位
    ll res = 0;
    for (ll d = 0; d <= up; d++) {
        if (d == 4)                 // 含数字 4，直接剪掉
            continue;
        if (prev6 == 1 && d == 2)   // 上一位是 6，这一位填 2 会拼出 62
            continue;
        // 只有每一位都贴着上界才保持 tight；本位填 6 才把 prev6 置 1
        res += dfs(pos + 1, tight && (d == up), (d == 6) ? 1 : 0);
    }
    memo[pos][tight][prev6] = res;
    return res;
}

// [0, x] 里吉利数（不含 4、不含 62）的个数；x < 0 时为 0。
ll count_upto(ll x) {
    if (x < 0)
        return 0;
    // 把 x 拆成十进制位，digits[1] 是最高位
    ll t = x;
    len = 0;
    while (t > 0) {
        len++;
        digits[len] = t % 10;
        t /= 10;
    }
    for (ll i = 1; i * 2 <= len; i++) { // 反转成从高到低
        ll swap_tmp = digits[i];
        digits[i] = digits[len + 1 - i];
        digits[len + 1 - i] = swap_tmp;
    }
    // 记忆化数组只清会用到的范围
    for (ll i = 1; i <= len + 1; i++)
        for (ll j = 0; j < 2; j++)
            for (ll k = 0; k < 2; k++)
                memo[i][j][k] = -1;
    return dfs(1, 1, 0);
}

int main() {
    ll n, m;
    while (scanf("%lld %lld", &n, &m) == 2) {
        if (n == 0 && m == 0)
            break; // 0 0 结束输入
        // 区间 [n, m] 的答案 = 前缀相减 f(m) - f(n-1)
        printf("%lld\n", count_upto(m) - count_upto(n - 1));
    }
    return 0;
}
