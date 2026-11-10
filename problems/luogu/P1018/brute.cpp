/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:45
 * update_at: 2026-11-11 00:45
 */

// brute.cpp：基于递归枚举乘号插入位置的暴力验证
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct BigInt {
    vector<int> d;
    BigInt() {}
    BigInt(const string& s) {
        for (int i = (int)s.size() - 1; i >= 0; --i) d.push_back(s[i] - '0');
        while (d.size() > 1 && d.back() == 0) d.pop_back();
    }
    bool operator<(const BigInt& o) const {
        if (d.size() != o.d.size()) return d.size() < o.d.size();
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            if (d[i] != o.d[i]) return d[i] < o.d[i];
        }
        return false;
    }
    BigInt operator*(const BigInt& o) const {
        BigInt res;
        res.d.assign(d.size() + o.d.size(), 0);
        for (size_t i = 0; i < d.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < o.d.size() || carry > 0; ++j) {
                long long cur = res.d[i + j] + 1LL * d[i] * (j < o.d.size() ? o.d[j] : 0) + carry;
                res.d[i + j] = cur % 10;
                carry = cur / 10;
            }
        }
        while (res.d.size() > 1 && res.d.back() == 0) res.d.pop_back();
        return res;
    }
    void print() const {
        for (int i = (int)d.size() - 1; i >= 0; --i) cout << d[i];
    }
};

int n, k;
string s;
BigInt max_prod;
bool has_res = false;

// 枚举上一个乘号位置 last_pos，当前已选 cnt 个乘号，累乘值为 cur_prod
void dfs(int last_pos, int cnt, BigInt cur_prod) {
    if (cnt == k) {
        // 最后一段 [last_pos + 1, n]
        BigInt last_seg(s.substr(last_pos, n - last_pos));
        BigInt total = cur_prod * last_seg;
        if (!has_res || max_prod < total) {
            max_prod = total;
            has_res = true;
        }
        return;
    }
    // 枚举下一个乘号位置 next_pos
    for (int next_pos = last_pos + 1; next_pos <= n - (k - cnt); ++next_pos) {
        BigInt seg(s.substr(last_pos, next_pos - last_pos));
        BigInt nxt_prod = (cnt == 0 ? seg : cur_prod * seg);
        dfs(next_pos, cnt + 1, nxt_prod);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k >> s)) return 0;
    dfs(0, 0, BigInt("1"));
    max_prod.print();
    cout << "\n";
    return 0;
}
