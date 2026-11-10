/**
 * Problem: luogu P1066 - [NOIP 2006 提高组] 2^k 进制数
 * Author: rainboy
 * Date: 2026-11-11 00:20
 * Description: 组合数递推 + 高精度大整数求和
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 高精度大整数简单封装
struct BigInt {
    vector<int> digits;

    BigInt() { digits.push_back(0); }
    BigInt(long long v) {
        if (v == 0) digits.push_back(0);
        while (v > 0) {
            digits.push_back(v % 10);
            v /= 10;
        }
    }

    BigInt operator+(const BigInt &o) const {
        BigInt res;
        res.digits.clear();
        int carry = 0;
        int sz = max(digits.size(), o.digits.size());
        for (int i = 0; i < sz || carry; ++i) {
            int cur = carry;
            if (i < static_cast<int>(digits.size())) cur += digits[i];
            if (i < static_cast<int>(o.digits.size())) cur += o.digits[i];
            res.digits.push_back(cur % 10);
            carry = cur / 10;
        }
        return res;
    }

    void print() const {
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
            cout << digits[i];
        }
        cout << "\n";
    }
};

BigInt C[515][515];

void init_comb(int limit) {
    for (int i = 0; i <= limit; ++i) {
        C[i][0] = BigInt(1);
        for (int j = 1; j <= i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, w;
    if (!(cin >> k >> w)) return 0;

    int total_elements = (1 << k) - 1;
    init_comb(total_elements);

    int len = w / k;
    int rem = w % k;

    BigInt ans(0);

    // 1. 位数在 2 到 len 之间（无最高位前缀限制）
    int max_normal_len = min(len, total_elements);
    for (int i = 2; i <= max_normal_len; ++i) {
        ans = ans + C[total_elements][i];
    }

    // 2. 位数等于 len + 1（受最高位 rem 二进制位数限制）
    if (rem > 0 && len + 1 <= total_elements) {
        int max_head = (1 << rem) - 1;
        // 最高位 v 从 1 到 max_head
        for (int v = 1; v <= max_head; ++v) {
            int remaining_choices = total_elements - v;
            if (remaining_choices >= len) {
                ans = ans + C[remaining_choices][len];
            }
        }
    }

    ans.print();

    return 0;
}
