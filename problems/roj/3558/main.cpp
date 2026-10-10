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

// 十进制大整数（little-endian），支持加法/乘法/比较
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
    bool operator<(const BigInt& o) const { return cmp(o) < 0; }
    string str() const { string r; for (int i = (int)d.size() - 1; i >= 0; i--) r += char('0' + d[i]); return r; }
    BigInt operator+(const BigInt& o) const {
        BigInt r; r.d.assign(max(d.size(), o.d.size()) + 1, 0);
        for (size_t i = 0; i < d.size(); i++) r.d[i] += d[i];
        for (size_t i = 0; i < o.d.size(); i++) r.d[i] += o.d[i];
        for (size_t i = 0; i + 1 < r.d.size(); i++) { r.d[i + 1] += r.d[i] / 10; r.d[i] %= 10; }
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
};

int n, m;
ll row[85];
BigInt pow2[85];   // pow2[i] = 2^i

BigInt row_score() {
    // dp[l][r]：还剩 [l,r] 未取时已拿到的最高分
    static BigInt dp[85][85];
    for (int l = m - 1; l >= 0; l--) {
        dp[l][l] = pow2[m] * row[l];
        for (int r = l + 1; r < m; r++) {
            int shift = m - r + l;
            BigInt take_left = pow2[shift] * row[l] + dp[l + 1][r];
            BigInt take_right = pow2[shift] * row[r] + dp[l][r - 1];
            dp[l][r] = take_left < take_right ? take_right : take_left;
        }
    }
    return dp[0][m - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    pow2[0] = BigInt(1);
    for (int i = 1; i <= m; i++) pow2[i] = pow2[i - 1] * BigInt(2);

    BigInt total(0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> row[j];
        total = total + row_score();
    }
    cout << total.str() << "\n";
    return 0;
}
