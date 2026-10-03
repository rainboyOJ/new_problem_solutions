/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:37
 * update_at: 2026-10-03 10:37
 */
// P9231 [蓝桥杯 2023 省 A] 平方差
// 核心结论：x 能写成 x = y^2 - z^2 当且仅当 x 是奇数或者 4 的倍数。
// 于是答案 = [1,R] 中这类数的个数 减去 [1,L-1] 中这类数的个数。
#include <iostream>
using namespace std;

typedef long long ll;

// 统计 [1,n] 中“奇数或 4 的倍数”的个数。
// 一个数不可能同时是奇数和 4 的倍数，所以两类直接相加，不会重复计算。
ll prefix_count(ll n) {
    if (n <= 0) {
        return 0;
    }
    ll odd = (n + 1) / 2; // 1,3,5,... 的个数
    ll mul4 = n / 4;      // 4,8,12,... 的个数
    return odd + mul4;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll L, R;
    cin >> L >> R;

    // 前缀和思想：区间答案 = F(R) - F(L-1)。
    cout << prefix_count(R) - prefix_count(L - 1) << '\n';

    return 0;
}
