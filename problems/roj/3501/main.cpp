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

// 十进制大整数（little-endian），只做本题需要的加法/乘法/比较
struct BigInt {
    vector<int> d;
    BigInt() { d.push_back(0); }
    BigInt(ll x) { d.clear(); if (x == 0) d.push_back(0); else while (x) { d.push_back(x % 10); x /= 10; } }
    BigInt(const string& s) { d.clear(); for (int i = (int)s.size() - 1; i >= 0; i--) d.push_back(s[i] - '0'); if (d.empty()) d.push_back(0); trim(); }
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

    BigInt operator*(const BigInt& o) const {
        BigInt r; r.d.assign(d.size() + o.d.size(), 0);
        for (size_t i = 0; i < d.size(); i++)
            for (size_t j = 0; j < o.d.size(); j++)
                r.d[i + j] += d[i] * o.d[j];
        for (size_t i = 0; i + 1 < r.d.size(); i++) { r.d[i + 1] += r.d[i] / 10; r.d[i] %= 10; }
        r.trim(); return r;
    }
};

int n, k;
string s;
BigInt dp[8][45];   // dp[j][i]：前 i 个数字插 j 个乘号的最大乘积

BigInt substr_num(int l, int r) {   // s[l..r) 的数字（0 基，r 不含）
    return BigInt(s.substr(l, r - l));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> s;
    for (int i = 1; i <= n; i++)
        dp[0][i] = substr_num(0, i);
    for (int j = 1; j <= k; j++) {
        for (int i = j + 1; i <= n; i++) {
            BigInt best(0);
            for (int t = j; t < i; t++) {
                BigInt cand = dp[j - 1][t] * substr_num(t, i);
                if (best < cand) best = cand;
            }
            dp[j][i] = best;
        }
    }
    cout << dp[k][n].str() << "\n";
    return 0;
}
