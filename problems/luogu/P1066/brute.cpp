/**
 * Problem: luogu P1066 - [NOIP 2006 提高组] 2^k 进制数 (Brute Force DP)
 * Author: rainboy
 * Date: 2026-11-11 00:20
 * Description: 动态规划逐位扩展基准实现
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 同样使用简单 BigInt
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

BigInt dp[515][515]; // dp[len][last_digit]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, w;
    if (!(cin >> k >> w)) return 0;

    int total_elements = (1 << k) - 1;
    int len = w / k;
    int rem = w % k;

    // dp[i][j]: 长度为 i，以数字 j 开头的方案数（从左到右递增）
    // 为了与排列等价，从后向前倒推
    // 长度为 1，最后一个数可为 1..total_elements
    for (int j = 1; j <= total_elements; ++j) {
        dp[1][j] = BigInt(1);
    }

    int max_len = min(len + (rem > 0 ? 1 : 0), total_elements);

    for (int l = 2; l <= max_len; ++l) {
        // dp[l][j] = sum_{nxt = j + 1}^{total_elements} dp[l-1][nxt]
        BigInt sum(0);
        for (int j = total_elements; j >= 1; --j) {
            dp[l][j] = sum;
            sum = sum + dp[l - 1][j];
        }
    }

    BigInt total_ans(0);

    // 位数 2 到 len
    for (int l = 2; l <= min(len, total_elements); ++l) {
        for (int j = 1; j <= total_elements; ++j) {
            total_ans = total_ans + dp[l][j];
        }
    }

    // 位数 len + 1
    if (rem > 0 && len + 1 <= total_elements) {
        int max_head = (1 << rem) - 1;
        for (int j = 1; j <= min(max_head, total_elements); ++j) {
            total_ans = total_ans + dp[len + 1][j];
        }
    }

    total_ans.print();

    return 0;
}
