// 第K小数（一本通 1779 / JZOJ P3458《密码》同源）
// ---------------------------------------------------------------------------
// 题意：给一个长度 n ≤ 17、由 '0'~'9' 组成且无前导零的字符串 S，把 S 中所有数字
//       重排，得到「无前导零且能被 17 整除」的所有不同整数，求其中第 K 小的那个。
//
// 建模：把「一个数的后缀」抽象成「一个数字多重集」。设
//         H(MS)[t] = 用多重集 MS 里的数字拼出的所有不同字符串中，数值 ≡ t (mod 17) 的个数。
//       按最低位递推：X = 10 * X' + d（d 为最低位，X' 由 MS \ {d} 排列而成），
//         X ≡ t  ⟺  10 * X' ≡ t - d  ⟺  X' ≡ (t - d) * 10^{-1} (mod 17)，
//       而 10 在模 17 下的逆元是 12（10 * 12 = 120 ≡ 1），故
//         H(MS)[t] = Σ_{d ∈ MS} H(MS \ {d})[ ((t - d) mod 17) * 12 mod 17 ],
//         H(∅)[0] = 1。
//       分支只按**数字取值**枚举（相同数字只走一条分支），因此统计到的天然是
//       「不同字符串」的个数，不需要再除以重数阶乘去重。
//
// 状态压缩：状态就是一个多重集，用混进制编号 idx = Σ c[d] * base[d]（base[d] = ∏_{e<d}(cnt[e]+1)）
//       表示，编号范围 0 .. ∏(cnt[d]+1) - 1。n ≤ 17、10 个数字时该乘积的最大值
//       = 3^3 * 2^7 = 17496（重数分布为 (1,1,1,2,2,2,2,2,2,2) 时取到），所以状态表非常小。
//
// 求解：从高位到低位逐位试填。设当前已定前缀模 17 的值为 p、剩余数字个数为 m，
//       试填 d 后前缀变成 np = (p * 10 + d) mod 17，之后还剩 m-1 位要填；
//       设剩余后缀拼成的数为 X，则整个数 ≡ np * 10^{m-1} + X (mod 17)，要求 ≡ 0，
//       即 X ≡ (-np) * 10^{m-1} (mod 17)，于是该分支的方案数就是
//         cnt = H(MS \ {d})[ ((-np) mod 17) * 10^{m-1} mod 17 ]。
//       若 K > cnt 则 K -= cnt 继续试更大的 d，否则这一位就定为 d。
//       首位（第 1 位）跳过 d = 0，其余位允许 0。
//
// 复杂度：时间 O(状态数 × 17 × 10) ≈ 3e6 次加法，空间 O(状态数 × 17) ≈ 2.4 MB（静态表）。
// ---------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static const int MOD = 17;    // 整除模数
static const int INV10 = 12;  // 10 在模 17 下的逆元：10 * 12 = 120 ≡ 1 (mod 17)

static int base10[10];                  // 混进制权重 base[d] = ∏_{e<d} (cnt[e] + 1)
static int radixr[10];                  // radixr[d] = cnt[d] + 1
static const int MAXS = 17500;          // 多重集编号上界：∏(cnt[d]+1) ≤ 17496
static array<ll, MOD> dp[MAXS];         // dp[idx][t]：该多重集的字符串里 ≡ t (mod 17) 的个数
static bool vis[MAXS];                  // 记忆化标记

// 取编号 idx 所代表的多重集中数字 d 的重数
static inline int getCnt(int idx, int d) { return (idx / base10[d]) % radixr[d]; }

// 记忆化：算出编号 idx 对应多重集的 dp[idx][0..16]
static void dfs(int idx) {
    if (vis[idx]) return;
    vis[idx] = true;
    if (idx == 0) {                     // 空多重集：空串数值为 0
        dp[0][0] = 1;
        return;
    }
    for (int d = 0; d < 10; d++) {
        if (getCnt(idx, d) == 0) continue;   // 该数字已用完
        int sub = idx - base10[d];           // 去掉一个 d 后的多重集编号
        dfs(sub);
        for (int t = 0; t < MOD; t++) {
            int src = ((t - d) % MOD + MOD) % MOD * INV10 % MOD;  // X' 需要的余数
            dp[idx][t] += dp[sub][src];
        }
    }
}

int main() {
    string s;
    ll K;
    if (!(cin >> s >> K)) return 0;

    int n = (int)s.size();
    int cnt[10] = {0};
    for (int i = 0; i < n; i++) cnt[s[i] - '0']++;

    // 混进制编号：idx = Σ cntUsed[d] * base10[d]
    int weight = 1;
    for (int d = 0; d < 10; d++) {
        base10[d] = weight;
        radixr[d] = cnt[d] + 1;
        weight *= radixr[d];
    }
    int full = 0;                                  // 初始（完整）多重集的编号
    for (int d = 0; d < 10; d++) full += cnt[d] * base10[d];

    // 10 的幂（模 17），10^k mod 17
    ll pow10mod[20];
    pow10mod[0] = 1;
    for (int i = 1; i <= n; i++) pow10mod[i] = pow10mod[i - 1] * 10 % MOD;

    dfs(full);                                     // 预处理所有子多重集的方案数

    int idx = full;                                // 当前剩余多重集的编号
    int p = 0;                                     // 已定前缀模 17 的值
    string ans;
    for (int i = 0; i < n; i++) {
        int m = n - i;                             // 当前还剩多少位要确定
        for (int d = 0; d < 10; d++) {
            if (getCnt(idx, d) == 0) continue;     // 剩余数字里没有 d
            if (i == 0 && d == 0) continue;        // 无前导零
            int np = (p * 10 + d) % MOD;
            int need = (int)((ll)((MOD - np) % MOD) * pow10mod[m - 1] % MOD);
            int sub = idx - base10[d];
            ll cur = dp[sub][need];                // 该分支能凑出的方案数
            if (K > cur) {
                K -= cur;                          // 这一支全部太小，跳过
            } else {
                ans.push_back(char('0' + d));
                p = np;
                idx = sub;
                break;
            }
        }
    }
    printf("%s\n", ans.c_str());
    return 0;
}
