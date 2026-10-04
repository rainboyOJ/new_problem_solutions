/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:37
 * update_at: 2026-10-03 10:37
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：把 x = y^2 - z^2 看成 (y-z)(y+z)，令 a = y-z >= 1、b = y+z >= a，
// 则 a*b = x 且 a、b 必须同奇偶。反过来，只要找到同奇偶的因子对
// 就能还原 y = (a+b)/2、z = (b-a)/2，所以逐个 x 枚举 a <= sqrt(x) 即可判断。
// 复杂度 O((R-L+1) * sqrt(R))，只适合小范围数据，不能当作正解。
#include <iostream>
using namespace std;

typedef long long ll;

// 判断 x 能否写成两个整数平方的差（y,z 取非负整数即可覆盖所有情况）。
bool can_represent(ll x) {
    if (x == 0) {
        return true; // 取 y = z 即可
    }
    // 枚举较小的因子 a，b = x / a 一定满足 b >= a。
    for (ll a = 1; a * a <= x; a++) {
        if (x % a != 0) {
            continue;
        }
        ll b = x / a;
        if ((a + b) % 2 == 0) {
            return true; // a、b 同奇偶，可以还原出整数 y、z
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll L, R;
    cin >> L >> R;

    ll ans = 0;
    // 朴素做法：区间里每个数都单独判断一次。
    for (ll x = L; x <= R; x++) {
        if (can_represent(x)) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
