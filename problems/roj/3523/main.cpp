/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:02
 * update_at: 2026-10-06 13:02
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int DIGITS = 500;          // 需要保留的十进制位数
const int BASE = 10000;          // 每段 4 位十进制
const int L = 125;               // 500 / 4 = 125 段

// a[i] 表示第 i 段（低位在前），只保留前 L 段（共 500 位十进制）
ll a[L], b[L], tmp[L * 2];

// 高精度乘高精度，结果模 10^500（只保留前 L 段）
// res = x * y，x、y 各 L 段
void mul_mod(ll res[], ll x[], ll y[]) {
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < L; ++i) {
        if (x[i] == 0) continue;
        for (int j = 0; j < L; ++j) {
            if (y[j] == 0) continue;
            tmp[i + j] += x[i] * y[j];
        }
    }
    // 进位，只保留前 L 段
    ll carry = 0;
    for (int i = 0; i < L; ++i) {
        ll cur = tmp[i] + carry;
        res[i] = cur % BASE;
        carry = cur / BASE;
    }
    // 更高位丢弃（模 10^500）
}

// 快速幂：计算 2^p mod 10^DIGITS，结果放在 a[]
void pow_mod(int p) {
    // 初始化 a = 1（结果），b = 2（底数）
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    a[0] = 1;
    b[0] = 2;

    while (p > 0) {
        if (p & 1) {
            mul_mod(a, a, b);
        }
        p >>= 1;
        if (p) {
            mul_mod(b, b, b);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P;
    if (!(cin >> P)) return 0;

    // 子问题一：位数 = floor(P * log10(2)) + 1
    long double ld = (long double)P * log10l(2.0L);
    ll digits = (ll)floor(ld) + 1;
    cout << digits << "\n";

    // 子问题二：末 500 位 = (2^P - 1) mod 10^500
    pow_mod(P);

    // 减 1
    a[0] -= 1;
    if (a[0] < 0) {
        a[0] += BASE;
        for (int i = 1; i < L; ++i) {
            a[i] -= 1;
            if (a[i] >= 0) break;
            a[i] += BASE;
        }
    }

    // 转成字符串（高位在前），不足 500 位前面补 0
    string out;
    for (int i = L - 1; i >= 0; --i) {
        char buf[8];
        if (i == L - 1) {
            snprintf(buf, sizeof(buf), "%lld", a[i]);
        } else {
            snprintf(buf, sizeof(buf), "%04lld", a[i]);
        }
        out += buf;
    }

    if ((int)out.length() < DIGITS) {
        out = string(DIGITS - out.length(), '0') + out;
    } else if ((int)out.length() > DIGITS) {
        out = out.substr(out.length() - DIGITS);
    }

    // 每 50 位一行，共 10 行
    for (int i = 0; i < DIGITS; i += 50) {
        cout << out.substr(i, 50) << "\n";
    }

    return 0;
}
