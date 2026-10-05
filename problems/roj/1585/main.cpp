/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-05 10:38
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 45; // B=2 时 2^31-1 只有 31 位，组合数参数留出余量

ll comb_table[MAXN][MAXN]; // comb_table[n][k] = C(n, k)
ll digits[MAXN];           // n 的 B 进制数字，高位在前，下标从 0 开始
int digit_cnt;             // digits 中有效位数的个数

// 预处理帕斯卡三角，供数位扫描时查组合数。
void build_comb() {
    for (int n = 0; n < MAXN; n++) {
        comb_table[n][0] = 1;
        for (int k = 1; k <= n; k++) {
            comb_table[n][k] = comb_table[n - 1][k - 1] + comb_table[n - 1][k];
        }
    }
}

// 返回 C(n, k)；k < 0 或 k > n 时按 0 处理（凑不够 1 的方案不存在）。
ll comb(ll n, ll k) {
    if (k < 0 || k > n) {
        return 0;
    }
    return comb_table[n][k];
}

// 把 n 写成 b 进制，高位在前存入 digits[]；n = 0 时存入单个 0。
void to_base(ll n, ll b) {
    digit_cnt = 0;
    if (n == 0) {
        digits[digit_cnt] = 0;
        digit_cnt++;
        return;
    }
    ll low[MAXN];
    int low_cnt = 0;
    while (n > 0) {
        low[low_cnt] = n % b;
        low_cnt++;
        n /= b;
    }
    for (int i = low_cnt - 1; i >= 0; i--) {
        digits[digit_cnt] = low[i];
        digit_cnt++;
    }
}

// 统计 [0, n] 中 B 进制表示只含 0/1 且恰有 k 个 1 的数的个数。
// 从高位到低位卡上界：某一位一旦严格小于 n，剩余位可自由选 0/1，用组合数一次收账。
ll count_prefix(ll n, ll k, ll b) {
    to_base(n, b);
    ll ans = 0;
    ll ones = 0; // 已确定的高位中 1 的个数，还差 k - ones 个
    for (int i = 0; i < digit_cnt; i++) {
        ll d = digits[i];
        ll rest = digit_cnt - i - 1; // 当前位之后还剩多少个低位
        if (d > 1) {
            // 本位放 0 或 1 都严格小于 n，本位加低位共 rest+1 位自由挑 k-ones 个 1
            return ans + comb(rest + 1, k - ones);
        }
        if (d == 1) {
            ans += comb(rest, k - ones); // 本位放 0，rest 个低位自由选
            ones++;                      // 本位放 1，继续卡上界
        }
        // d == 0：放 1 会超过 n，只能放 0 继续卡上界，不入账
    }
    if (ones == k) {
        ans++; // n 本身每位都是 0/1，看它是否恰好 k 个 1
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x, y, k, b;
    cin >> x >> y;
    cin >> k >> b;

    build_comb();
    cout << count_prefix(y, k, b) - count_prefix(x - 1, k, b) << "\n";

    return 0;
}
