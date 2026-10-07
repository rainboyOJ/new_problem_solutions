/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:47
 * update_at: 2026-10-07 15:47
 */

// 一本通 1697《深意》：单词 t 有原意与"深意"两种含义，串 s 中每一处出现的 t
// 都可以选择取哪种含义，问 s 一共有多少种含义。
//
// 模型：一种含义 = 一组两两不重叠的匹配位置（这组匹配取"深意"，其余取原意）。
// 做法：KMP 求出 t 在 s 中的全部匹配的结束位置，再线性 DP 统计不重叠匹配组数。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;
const ll MAXN = 100005;  // |s| 上限 1e5，见数据规模 len(t) <= len(s) <= 100000

char buf_s[MAXN];  // 当前这组的 s
char buf_t[MAXN];  // 当前这组的 t
int fail[MAXN];    // fail[i]：t 的前 i 个字符的最长"真前缀 = 后缀"长度
char occ[MAXN];    // occ[i]：s 的前 i 个字符恰好以 t 结尾；取值只有 0/1，用 char 省内存
ll dp[MAXN];       // dp[i]：s 的前 i 个字符能表示出的含义种数

// 求 t 的失配数组 fail（模式串自匹配）。
void build_fail(ll m) {
    fail[0] = 0;
    fail[1] = 0;
    ll j = 0;  // j：已经匹配上的 t 的前缀长度
    for (ll i = 1; i < m; i++) {
        while (j > 0 && buf_t[i] != buf_t[j]) j = fail[j];
        if (buf_t[i] == buf_t[j]) j++;
        fail[i + 1] = j;
    }
}

// 标记 t 在 s 中的每一次出现：occ[i] = 1 表示子串 s[i-m .. i-1] 等于 t。
// 末尾出现过 t 的前缀才可能把最后一段取深意，所以只需记录结束位置。
void mark_occurrence(ll a, ll m) {
    for (ll i = 0; i <= a; i++) occ[i] = 0;  // 只清实际用到的范围 [0, a]
    ll j = 0;
    for (ll i = 0; i < a; i++) {
        while (j > 0 && buf_s[i] != buf_t[j]) j = fail[j];
        if (buf_s[i] == buf_t[j]) j++;
        if (j == m) {          // s[i-m+1 .. i] 匹配成功（此处按 1 起下标即结束位置 i+1）
            occ[i + 1] = 1;
            j = fail[j];       // 允许匹配区间重叠，继续往后找
        }
    }
}

// 统计 s 的含义种数：按"最后一个取深意的匹配的结束位置"对方案分类。
ll count_meanings(ll a, ll m) {
    build_fail(m);
    mark_occurrence(a, m);

    dp[0] = 1;  // 空前缀只有一种含义
    for (ll i = 1; i <= a; i++) {
        dp[i] = dp[i - 1];                             // 没有匹配恰好结束在 i：末段取原意
        if (occ[i]) dp[i] = (dp[i] + dp[i - m]) % MOD;  // 末尾这段 t 取深意，前面部分随意
    }
    return dp[a];
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0;

    for (ll k = 1; k <= n; k++) {
        scanf("%s", buf_s);
        scanf("%s", buf_t);
        ll a = strlen(buf_s);
        ll m = strlen(buf_t);

        // 题面保证 m <= a；真出现更长的 t 则 occ 全为 0，答案自然是 1。
        printf("%lld\n", count_meanings(a, m));
    }
    return 0;
}
