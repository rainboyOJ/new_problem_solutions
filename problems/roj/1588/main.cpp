/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:46
 * update_at: 2026-10-05 10:46
 */

// 数位 DP：统计 [a, b] 中各位数字之和 mod N 为 0 的数的个数。
// 前缀相减：ans = f(b) - f(a-1)，其中 f(x) 统计 [0, x] 的合法数个数。
// 状态 (pos, rem, tight)：从高位往低位填数，rem 是已填前缀的数字和 mod N，
// tight 表示前缀是否贴着上界 x。前导零不需要特判：高位填 0 不影响数字和。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXL = 12;   // 2^31-1 最多 10 位，留点余量
const int MAXN = 105;  // N < 100

ll digit[MAXL];        // digit[pos] = 上界 x 从高到低第 pos 位的数字
ll digits_tmp[MAXL];   // 拆位时的临时数组（低位在前）
ll len;                // 上界 x 的位数
ll memo[MAXL][MAXN];   // memo[pos][rem] = 松绑状态下 (pos, rem) 的答案，-1 表示未算过
ll n;                  // 本组询问的模数 N

// 从第 pos 位开始填数：前缀数字和 mod N 余 rem，tight 表示是否贴上界。
// 填完全部位数后 rem == 0 即为合法数。
ll dfs(ll pos, ll rem, bool tight) {
    if (pos == len) { // 位数全部填完，只看数字和是否为 N 的倍数
        if (rem == 0) return 1;
        return 0;
    }
    if (!tight && memo[pos][rem] != -1) return memo[pos][rem]; // 松绑状态可记忆化

    ll limit = 9; // 自由填 0..9
    if (tight) limit = digit[pos]; // 贴上界时本位最多填到上界的这一位

    ll res = 0;
    for (ll d = 0; d <= limit; d++) {
        res += dfs(pos + 1, (rem + d) % n, tight && d == limit);
    }
    if (!tight) memo[pos][rem] = res; // tight 路径每棵搜索树只有一条，不用记
    return res;
}

// 统计 [0, x] 中数字和 mod N 为 0 的个数（0 本身也算，S(0)=0）。
ll count_mod_sum(ll x) {
    if (x < 0) return 0;
    len = 0;
    while (x > 0) { // 拆位：digit[0] 是最高位
        digits_tmp[len] = x % 10;
        x /= 10;
        len++;
    }
    for (ll i = 0; i < len; i++) digit[i] = digits_tmp[len - 1 - i];
    // 只清空本组会用到的 memo 范围（N 变了必须重算）
    for (ll i = 0; i < len; i++)
        for (ll j = 0; j < n; j++)
            memo[i][j] = -1;
    return dfs(0, 0, true);
}

ll a, b;

void solve() {
    if (a > b) { ll t = a; a = b; b = t; } // 题面没保证 a 在前，保险起见交换
    // 前缀相减：0 在两份计数里各算一次正好抵消
    cout << count_mod_sum(b) - count_mod_sum(a - 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> a >> b >> n) { // 多组测试数据，读到 EOF
        solve();
    }

    return 0;
}
