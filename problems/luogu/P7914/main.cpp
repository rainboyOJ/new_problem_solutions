/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-06 08:46
 * update_at: 2026-10-01 20:57
 */
// main.cpp：区间 DP，atom 表示单个外层括号块，f 表示若干 atom 拼成的合法序列。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 505;
const ll MOD = 1000000007LL;

int n, K;
string s;

// bad_star_prefix[i]：前缀 [1,i] 中不能当 '*' 的位置数（即不是 '*' 也不是 '?' 的位置）
int bad_star_prefix[MAXN];

// atom_dp[l][r]：区间 [l,r] 构成单个外层括号块的方案数
int atom_dp[MAXN][MAXN];

// f[l][r]：区间 [l,r] 构成合法超级括号序列的方案数（可由多个 atom 拼接）
int f[MAXN][MAXN];

// sep_sum[l][r]：从 l 开始的一段合法序列，后面接空串或星串，使下一个 atom 从 r 开始的方案数
int sep_sum[MAXN][MAXN];

// 位置 pos 能否放左括号 '('
bool can_left(int pos) {
    return s[pos] == '(' || s[pos] == '?';
}

// 位置 pos 能否放右括号 ')'
bool can_right(int pos) {
    return s[pos] == ')' || s[pos] == '?';
}

// 位置 pos 能否放星号 '*'
bool can_star_char(int pos) {
    return s[pos] == '*' || s[pos] == '?';
}

// 区间 [l,r] 是否能全部填成星号（长度不超过 K 且每个位置都能放 '*'）
bool is_star_string(int l, int r) {
    if (l > r) {
        return false;
    }
    if (r - l + 1 > K) {
        return false;
    }
    return bad_star_prefix[r] - bad_star_prefix[l - 1] == 0;
}

// 模意义下加法：x = (x + y) % MOD
void add_mod(int &x, ll y) {
    x = (x + y) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K;
    cin >> s;
    s = " " + s;

    for (int i = 1; i <= n; i++) {
        bad_star_prefix[i] = bad_star_prefix[i - 1] + (can_star_char(i) ? 0 : 1);
    }

    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;

            // 计算 sep_sum[l][r]：f[l][..] 后接空串或星串，使下一个 atom 从 r 开始
            if (l < r) {
                sep_sum[l][r] = f[l][r - 1]; // 两个合法块直接相接
                int max_len = min(K, r - l - 1);
                for (int star_len = 1; star_len <= max_len; star_len++) {
                    int star_l = r - star_len;
                    int left_end = star_l - 1;
                    if (left_end >= l && is_star_string(star_l, r - 1)) {
                        add_mod(sep_sum[l][r], f[l][left_end]);
                    }
                }
            }

            // 计算 atom_dp[l][r]：区间 [l,r] 是单个外层括号块
            if (len >= 2 && can_left(l) && can_right(r)) {
                if (l + 1 == r) {
                    add_mod(atom_dp[l][r], 1); // ()
                }
                if (is_star_string(l + 1, r - 1)) {
                    add_mod(atom_dp[l][r], 1); // (S)
                }
                if (l + 1 <= r - 1) {
                    add_mod(atom_dp[l][r], f[l + 1][r - 1]); // (A)
                }

                // (SA)
                for (int p = l + 1; p <= r - 2 && p - (l + 1) + 1 <= K; p++) {
                    if (is_star_string(l + 1, p)) {
                        add_mod(atom_dp[l][r], f[p + 1][r - 1]);
                    }
                }

                // (AS)
                for (int p = l + 1; p <= r - 2; p++) {
                    if (is_star_string(p + 1, r - 1)) {
                        add_mod(atom_dp[l][r], f[l + 1][p]);
                    }
                }
            }

            // 计算 f[l][r]：单个 atom 或多个 atom 拼接
            f[l][r] = atom_dp[l][r];
            for (int start = l + 1; start <= r; start++) {
                add_mod(f[l][r], (ll)sep_sum[l][start] * atom_dp[start][r]);
            }
        }
    }

    cout << f[1][n] << '\n';
    return 0;
}
