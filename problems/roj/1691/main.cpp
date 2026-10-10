/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:37
 * update_at: 2026-10-07 15:37
 */
// main.cpp：文章评分，统计长度 m 的本质不同子串个数。
// 与 main.py 同一算法：双模滚动哈希把每个窗口压成一个 64 位整数，排序去重后计数。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD1 = 1000000007LL; // 第一套哈希的模数
const ll MOD2 = 998244353LL;  // 第二套哈希的模数
const ll BASE1 = 131LL;       // 第一套哈希的进制
const ll BASE2 = 137LL;       // 第二套哈希的进制

const int MAXN = 200005;

// 一个前缀（或一个窗口）在两套模数下的哈希值，打包在一起避免平行数组
struct HashPair {
    ll first;  // 模 MOD1 的哈希
    ll second; // 模 MOD2 的哈希
};

ll n, m;              // 文章长度、需要统计的子串长度
char text[MAXN];      // text[1..n] 存放文章
HashPair power[MAXN]; // power[i] = (BASE1^i mod MOD1, BASE2^i mod MOD2)
HashPair pre[MAXN];   // pre[i] 是 text[1..i] 的两套前缀哈希
ll win_key[MAXN];     // win_key[i] 是第 i 个窗口的双模哈希压成的单个整数

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) return 0;
    scanf("%s", text + 1);

    power[0].first = 1;
    power[0].second = 1;
    for (int i = 1; i <= n; i++) {
        power[i].first = power[i - 1].first * BASE1 % MOD1;
        power[i].second = power[i - 1].second * BASE2 % MOD2;
        ll digit = text[i] - 'a' + 1; // 'a' 记成 1，避免前导零带来的歧义
        pre[i].first = (pre[i - 1].first * BASE1 + digit) % MOD1;
        pre[i].second = (pre[i - 1].second * BASE2 + digit) % MOD2;
    }

    // 窗口 text[i..i+m-1] 的哈希 = pre[i+m-1] - pre[i-1] * BASE^m，
    // 两个模数各约 1e9，打包成 h1 * MOD2 + h2 后不超过 1e18，一个 ll 装得下，
    // 而且打包是单射：键相等当且仅当两套哈希都相等。
    ll window_count = 0;
    for (int i = 1; i + m - 1 <= n; i++) {
        int right_end = i + m - 1;
        ll hash1 = (pre[right_end].first - pre[i - 1].first * power[m].first % MOD1 + MOD1) % MOD1;
        ll hash2 = (pre[right_end].second - pre[i - 1].second * power[m].second % MOD2 + MOD2) % MOD2;
        win_key[++window_count] = hash1 * MOD2 + hash2;
    }

    sort(win_key + 1, win_key + window_count + 1);
    ll ans = 0; // 排序后相邻比较，键第一次出现就说明遇到一个新的子串
    for (ll i = 1; i <= window_count; i++) {
        if (i == 1 || win_key[i] != win_key[i - 1]) ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
