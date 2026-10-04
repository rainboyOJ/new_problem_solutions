/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:00
 * update_at: 2026-10-05 01:00
 */

#include <cstdio>
#include <map>
using namespace std;

typedef long long ll;

ll L, R;                         // 区间左右端点
map<ll, ll> memo;                // 记忆化 F(x)：1..x 中数字 2 出现的总次数

// 计算正整数 n 的十进制写法中数字 2 出现的次数
ll count_two(ll n) {
    ll cnt = 0;
    while (n > 0) {
        if (n % 10 == 2) cnt++;
        n /= 10;
    }
    return cnt;
}

// F(x)：统计 1..x 中数字 2 出现的总次数；区间答案用 F(R) - F(L-1)
ll count_upto(ll x) {
    if (x < 2) return 0;
    if (memo.count(x)) return memo[x];

    ll q = x / 10;               // 商：代表高位
    ll r = x % 10;               // 余数：代表个位

    // 一位数直接返回 1（2..9 都只有 1 个 2）
    if (q == 0) return memo[x] = 1;

    // 按个位分块：完整块贡献 10*F(q-1)+q，残块贡献 (r+1)*count_two(q)+[r>=2]
    ll res = 10 * count_upto(q - 1) + q
           + (r + 1) * count_two(q) + (r >= 2 ? 1 : 0);

    return memo[x] = res;
}

int main() {
    scanf("%lld %lld", &L, &R);
    printf("%lld\n", count_upto(R) - count_upto(L - 1));
    return 0;
}
