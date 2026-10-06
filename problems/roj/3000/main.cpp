/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:43
 * update_at: 2026-10-06 10:43
 */
#include <iostream>
using namespace std;

typedef long long ll;

// 快速幂：把指数 exponent 按二进制拆分，逐位平方底数，只把为 1 的位乘进结果
ll mod_pow(ll base, ll exponent, ll mod) {
    ll result = 1 % mod; // p = 1 时答案恒为 0，这一行一次处理掉该边界
    base %= mod;         // a 可能大于 p，先取模控制后续乘积范围
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % mod;
        }
        base = base * base % mod; // base^(2^k) -> base^(2^(k+1))
        exponent >>= 1;
    }
    return result;
}

int main() {
    ll a, b, p;
    cin >> a >> b >> p;
    cout << mod_pow(a, b, p) << "\n";
    return 0;
}
