/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:11
 * update_at: 2026-10-06 02:11
 */
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ll n, p, k, now;
    cin >> n >> p >> k >> now;

    // 环上行走就是模 n 加法：第 i 次行走落在第 (i-1)/k 个方向块，
    // 偶数块顺时针记 +a_i、奇数块逆时针记 -a_i，累加得到带符号总位移。
    ll drift = 0; // 带符号总位移
    for (ll i = 1; i <= p; i++) {
        ll a;
        cin >> a;
        ll block = (i - 1) / k; // 方向块编号，从 0 开始
        if (block % 2 == 0) {
            drift += a; // 顺时针
        } else {
            drift -= a; // 逆时针
        }
    }

    // 总位移可能为负，先加 n 再取模归一到 [0, n)。
    ll ans = ((now + drift) % n + n) % n;
    cout << ans << endl;
    return 0;
}
