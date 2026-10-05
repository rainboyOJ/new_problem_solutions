/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:15
 * update_at: 2026-10-05 11:15
 */

// 数位 DP：求区间 [L, R] 内与 7 无关的数的平方和。
// 递归回溯时同时维护合法数字的个数、一次方和、平方和，
// 用完全平方公式 (base + y)^2 = base^2 + 2*base*y + y^2 逐位向上合并。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

struct State {
    ll cnt; // 合法数字个数
    ll sum; // 合法数字之和
    ll sq;  // 合法数字平方和
};

ll pow10[20]; // pow10[i] = 10^i mod MOD

int digit[20]; // digit[i] = 上界 n 从高位起的第 i 位数字
int digit_len;

State memo[20][7][7]; // memo[pos][num_mod][sum_mod]：前缀不贴上限时的合并结果
char vis[20][7][7];   // 记忆化标记，只有 0/1，用 char 省内存

// pos: 当前要填从高位起的第 pos 位
// num_mod: 已填前缀数值模 7 的余数；sum_mod: 已填前缀数位和模 7 的余数
// limit: 已填前缀是否与上界 n 完全相同（贴上限时不能查表）
State dfs(int pos, int num_mod, int sum_mod, bool limit) {
    if (pos == digit_len) {
        // 所有位填完：数值模 7 和数位和模 7 都不为 0 才与 7 无关
        if (num_mod != 0 && sum_mod != 0) {
            State ok = {1, 0, 0};
            return ok;
        }
        State none = {0, 0, 0};
        return none;
    }

    if (!limit && vis[pos][num_mod][sum_mod]) {
        return memo[pos][num_mod][sum_mod];
    }

    int up = limit ? digit[pos] : 9;
    State ans = {0, 0, 0};
    for (int d = 0; d <= up; d++) {
        if (d == 7) {
            continue; // 数中出现了数字 7，整个数一定与 7 有关
        }
        State nxt = dfs(pos + 1, (num_mod * 10 + d) % 7, (sum_mod + d) % 7,
                        limit && (d == up));
        // 这一位实际贡献的权值 base = d * 10^(从低位起的位置)
        ll base = pow10[digit_len - 1 - pos] * d % MOD;
        ll base_sq = base * base % MOD;
        // 当前层拼出的完整数 x = base + y，对每个合法后缀 y 累加
        ans.cnt = (ans.cnt + nxt.cnt) % MOD;
        ans.sum = (ans.sum + nxt.sum + base * nxt.cnt) % MOD;
        ans.sq = (ans.sq + nxt.sq + 2 * base % MOD * nxt.sum + base_sq * nxt.cnt) % MOD;
    }

    if (!limit) {
        memo[pos][num_mod][sum_mod] = ans;
        vis[pos][num_mod][sum_mod] = 1;
    }
    return ans;
}

// 计算 [1, n] 中与 7 无关的数字平方和 mod MOD
ll calc(ll n) {
    if (n <= 0) {
        return 0;
    }
    digit_len = 0;
    ll x = n;
    while (x > 0) {
        digit[digit_len] = x % 10;
        digit_len++;
        x /= 10;
    }
    // 上面的 digit[] 是低位在前，翻转成高位在前
    for (int i = 0; i < digit_len / 2; i++) {
        int t = digit[i];
        digit[i] = digit[digit_len - 1 - i];
        digit[digit_len - 1 - i] = t;
    }
    // 每位权值依赖当前上界的长度，每次查询前清空记忆化表
    memset(vis, 0, sizeof(vis));
    return dfs(0, 0, 0, true).sq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pow10[0] = 1;
    for (int i = 1; i < 20; i++) {
        pow10[i] = pow10[i - 1] * 10 % MOD;
    }

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        ll l, r;
        cin >> l >> r;
        ll ans = (calc(r) - calc(l - 1) + MOD) % MOD;
        cout << ans << "\n";
    }

    return 0;
}
