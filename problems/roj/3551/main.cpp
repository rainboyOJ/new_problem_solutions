/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 十进制大整数（little-endian），只做 3551 需要的加法/减法/乘法/整除小整数
struct BigInt {
    vector<int> d;
    BigInt() { d.push_back(0); }
    BigInt(ll x) { d.clear(); if (x == 0) d.push_back(0); else while (x) { d.push_back((int)(x % 10)); x /= 10; } }
    void trim() { while (d.size() > 1 && d.back() == 0) d.pop_back(); }
    bool is_zero() const { return d.size() == 1 && d[0] == 0; }
    int cmp(const BigInt& o) const {
        if (d.size() != o.d.size()) return d.size() < o.d.size() ? -1 : 1;
        for (int i = (int)d.size() - 1; i >= 0; i--)
            if (d[i] != o.d[i]) return d[i] < o.d[i] ? -1 : 1;
        return 0;
    }
    string str() const { string r; for (int i = (int)d.size() - 1; i >= 0; i--) r += char('0' + d[i]); return r; }
    BigInt operator+(const BigInt& o) const {
        BigInt r; r.d.assign(max(d.size(), o.d.size()) + 1, 0);
        for (size_t i = 0; i < d.size(); i++) r.d[i] += d[i];
        for (size_t i = 0; i < o.d.size(); i++) r.d[i] += o.d[i];
        for (size_t i = 0; i + 1 < r.d.size(); i++) { r.d[i + 1] += r.d[i] / 10; r.d[i] %= 10; }
        r.trim(); return r;
    }
    BigInt operator-(const BigInt& o) const {   // 假设 *this >= o
        BigInt r; r.d = d;
        for (size_t i = 0; i < o.d.size(); i++) {
            r.d[i] -= o.d[i];
            if (r.d[i] < 0) { r.d[i] += 10; r.d[i + 1]--; }
        }
        for (size_t i = 0; i + 1 < r.d.size(); i++)
            if (r.d[i] < 0) { r.d[i] += 10; r.d[i + 1]--; }
        r.trim(); return r;
    }
    BigInt operator*(const BigInt& o) const {
        BigInt r; r.d.assign(d.size() + o.d.size(), 0);
        for (size_t i = 0; i < d.size(); i++)
            for (size_t j = 0; j < o.d.size(); j++)
                r.d[i + j] += d[i] * o.d[j];
        for (size_t i = 0; i + 1 < r.d.size(); i++) { r.d[i + 1] += r.d[i] / 10; r.d[i] %= 10; }
        r.trim(); return r;
    }
    BigInt div_small(ll x) const {
        BigInt r; r.d.assign(d.size(), 0);
        ll rem = 0;
        for (int i = (int)d.size() - 1; i >= 0; i--) {
            ll cur = rem * 10 + d[i];
            r.d[i] = (int)(cur / x); rem = cur % x;
        }
        r.trim(); return r;
    }
};

// 组合数 C(n, k)，结果用 BigInt
BigInt C[520][520];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, w;
    cin >> k >> w;
    int B = 1 << k;

    // 组合数打表
    for (int i = 0; i <= B; i++) {
        C[i][0] = BigInt(1);
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }

    // 位数 m 的上界
    int m_max = min(B - 1, (w - 1) / k + 1);
    BigInt ans(0);
    for (int m = 2; m <= m_max; m++) {
        for (int j = 1; j <= min(k, w - k * (m - 1)); j++) {
            // C(B - 2^(j-1), m) - C(B - 2^j, m)
            BigInt a = C[B - (1 << (j - 1))][m];
            BigInt b = C[B - (1 << j)][m];
            ans = ans + (a - b);
        }
    }
    cout << ans.str() << "\n";
    return 0;
}
