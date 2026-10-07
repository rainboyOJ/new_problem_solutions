/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:11
 * update_at: 2026-10-05 09:11
 */

// 求 N 位数中含偶数个数字 3 的个数，对 12345 取模。
// 逐位转移：这一位取 9 种非 3 数字时奇偶不变，取数字 3 时奇偶翻转。
// 设 e_k、o_k 为允许前导零时长度 k 的串中 3 的个数为偶/奇的个数，
// 递推解耦得 答案 = 8*e[N-1] + o[N-1] = (9*10^(N-1) + 7*8^(N-1)) / 2，
// 用快速幂按闭式直接计算，O(log N)。
#include <cstdio>
using namespace std;
typedef long long ll;

const ll MOD = 12345;
const ll HALF = 2 * MOD; // 分子恒为偶数，在模 2*MOD 下计算后真正整除 2，避免除法丢信息

ll n; // 位数 N

ll read_input() {
    if (scanf("%lld", &n) != 1) return 0;
    return n;
}

// 快速幂：a^e mod p
ll mod_pow(ll a, ll e, ll p) {
    ll result = 1 % p; // p 可能为 1 时结果应为 0
    a %= p;
    while (e > 0) {
        if (e & 1) result = result * a % p;
        a = a * a % p;
        e >>= 1;
    }
    return result;
}

void solve() {
    // 分别在模 HALF 下求 10^(N-1)、8^(N-1)，中间乘 9/7 后仍在 ll 范围内
    ll pow10 = mod_pow(10, n - 1, HALF);
    ll pow8 = mod_pow(8, n - 1, HALF);
    ll doubled = (9 * pow10 % HALF + 7 * pow8 % HALF) % HALF; // 分子 9*10^(N-1)+7*8^(N-1)
    ll ans = doubled / 2 % MOD; // 分子恒为偶数，先整除 2 再取模
    printf("%lld\n", ans);
}

int main() {
    if (read_input() == 0) return 0;
    solve();
    return 0;
}
