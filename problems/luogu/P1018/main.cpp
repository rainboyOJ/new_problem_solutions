/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:45
 * update_at: 2026-11-11 00:45
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 紧凑的高精度整数结构体
struct BigInt {
    vector<int> digits; // 低位在前

    BigInt() {}

    BigInt(const string& s) {
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
            digits.push_back(s[i] - '0');
        }
        trim();
    }

    void trim() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    bool operator<(const BigInt& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() < other.digits.size();
        }
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] < other.digits[i];
            }
        }
        return false;
    }

    BigInt operator*(const BigInt& other) const {
        BigInt res;
        res.digits.assign(digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry > 0; ++j) {
                long long cur = res.digits[i + j] + 1LL * digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                res.digits[i + j] = cur % 10;
                carry = cur / 10;
            }
        }
        res.trim();
        return res;
    }

    void print() const {
        if (digits.empty()) {
            cout << 0;
            return;
        }
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
            cout << digits[i];
        }
    }
};

const int MAXN = 45;
const int MAXK = 10;

// dp[i][j] 表示前 i 个数字切分成 j+1 段（插入 j 个乘号）的最大乘积
BigInt dp[MAXN][MAXK];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    string s;
    cin >> s;

    // 辅助 lambda：截取子串并构造高精度数
    auto get_num = [&](int l, int r) {
        return BigInt(s.substr(l - 1, r - l + 1));
    };

    // 初始化 j = 0（无乘号情况）
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = get_num(1, i);
    }

    // 递推插入乘号
    for (int j = 1; j <= k; ++j) {
        for (int i = j + 1; i <= n; ++i) {
            for (int p = j; p < i; ++p) {
                BigInt val = dp[p][j - 1] * get_num(p + 1, i);
                if (dp[i][j] < val) {
                    dp[i][j] = val;
                }
            }
        }
    }

    dp[n][k].print();
    cout << "\n";

    return 0;
}
