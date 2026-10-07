/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:05
 * update_at: 2026-10-06 02:07
 */
// main.cpp：对数闭式解求病毒首次占满 4096MB 的分钟数。
#include <cmath>
#include <iostream>
using namespace std;

typedef long long ll;

long double x; // 病毒第 1 分钟占用的内存，单位 MB
long double y; // 每分钟占用量增长为上一分钟的 y 倍

// 判断第 n 分钟的占用量 x·y^(n-1) 是否已达到 4096MB。
bool reached(ll n) {
    return x * powl(y, n - 1) >= 4096.0L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> y;

    // 由 x·y^(n-1) >= 4096 取对数，估计 m = n-1 的上取整；减 1e-9 吸收浮点超调
    ll m = ceill(logl(4096.0L / x) / logl(y) - 1e-9L);
    if (m < 0) {
        m = 0;
    }

    // 在估计值附近用高精度乘法复核，保证“恰好等于 4096 即占满”的临界判对
    while (m > 0 && reached(m)) { // 第 m 分钟就已占满，说明估计偏大
        m--;
    }
    while (!reached(m + 1)) { // 第 m+1 分钟还没占满，继续后移
        m++;
    }

    cout << m + 1 << endl; // 第 1 分钟占用 x，占满发生在第 m+1 分钟
    return 0;
}
