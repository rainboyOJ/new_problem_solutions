/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:11
 * update_at: 2026-11-11 00:15
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 高精度大整数类（固定保留后 k 位，或者用于存储答案 L）
struct BigInt {
    vector<int> d; // 低位在前

    BigInt() {}
    BigInt(long long v) {
        if (v == 0) d.push_back(0);
        while (v > 0) {
            d.push_back(v % 10);
            v /= 10;
        }
    }

    // 模 10^k 下的乘法
    static BigInt mul_mod(const BigInt& a, const BigInt& b, int k) {
        BigInt res;
        res.d.assign(k + 5, 0);
        int lim_a = min((int)a.d.size(), k);
        int lim_b = min((int)b.d.size(), k);

        for (int i = 0; i < lim_a; ++i) {
            for (int j = 0; j < lim_b && i + j < k; ++j) {
                res.d[i + j] += a.d[i] * b.d[j];
            }
        }
        for (int i = 0; i < k; ++i) {
            if (res.d[i] >= 10) {
                res.d[i + 1] += res.d[i] / 10;
                res.d[i] %= 10;
            }
        }
        res.d.resize(k);
        return res;
    }

    // 高精度乘低精度整数
    void mul_int(int x) {
        int carry = 0;
        for (size_t i = 0; i < d.size() || carry; ++i) {
            if (i == d.size()) d.push_back(0);
            long long cur = 1LL * d[i] * x + carry;
            d[i] = cur % 10;
            carry = cur / 10;
        }
        while (d.size() > 1 && d.back() == 0) {
            d.pop_back();
        }
    }

    void print() const {
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            cout << d[i];
        }
        cout << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int k;
    if (!(cin >> s >> k)) return 0;

    // 截取后 k 位
    BigInt n_mod;
    n_mod.d.assign(k, 0);
    int len = s.size();
    for (int i = 0; i < k; ++i) {
        if (len - 1 - i >= 0) {
            n_mod.d[i] = s[len - 1 - i] - '0';
        } else {
            n_mod.d[i] = 0;
        }
    }

    // L 为最终答案
    BigInt ans(1);

    // P 为使得后 i 位保持不变的变换乘子，初始为 n mod 10^k
    BigInt P = n_mod;

    // 逐位确定循环节
    for (int i = 0; i < k; ++i) {
        // base_val 为基准比较值（即 n * 某幂 在模 10^k 下的结果）
        // 我们需要找到正整数 t in [1, 10]，使得 (n * P^t) 的第 i 位与 n 的第 i 位相同
        BigInt temp = n_mod;
        int t = 0;

        // 维护 P 的累乘
        BigInt p_pow = P;

        for (int step = 1; step <= 10; ++step) {
            temp = BigInt::mul_mod(temp, P, k);
            if (temp.d[i] == n_mod.d[i]) {
                t = step;
                break;
            }
        }

        if (t == 0) {
            cout << -1 << "\n";
            return 0;
        }

        // 累乘答案
        ans.mul_int(t);

        // 新的步长算子为 P^t
        BigInt next_P = P;
        BigInt base = P;
        for (int step = 1; step < t; ++step) {
            next_P = BigInt::mul_mod(next_P, base, k);
        }
        P = next_P;
    }

    ans.print();

    return 0;
}
