#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int BASE = 10000;
const int WIDTH = 4;

struct BigInt {
    vector<int> d;

    BigInt(int x = 0) {
        if (x == 0) {
            d.push_back(0);
            return;
        }
        while (x > 0) {
            d.push_back(x % BASE);
            x /= BASE;
        }
    }

    void trim() {
        while (d.size() > 1 && d.back() == 0) {
            d.pop_back();
        }
    }
};

BigInt operator + (const BigInt &a, const BigInt &b) {
    BigInt c;
    c.d.clear();

    int len = max((int) a.d.size(), (int) b.d.size());
    int carry = 0;

    for (int i = 0; i < len; i++) {
        int x = carry;
        if (i < (int) a.d.size()) {
            x += a.d[i];
        }
        if (i < (int) b.d.size()) {
            x += b.d[i];
        }
        c.d.push_back(x % BASE);
        carry = x / BASE;
    }

    if (carry) {
        c.d.push_back(carry);
    }

    c.trim();
    return c;
}

ostream &operator << (ostream &out, const BigInt &a) {
    out << a.d.back();
    for (int i = (int) a.d.size() - 2; i >= 0; i--) {
        out << setw(WIDTH) << setfill('0') << a.d[i];
    }
    return out;
}

int n;
BigInt f[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    f[0] = BigInt(1);

    // Catalan 递推：
    // f[i] = sum_{j=0}^{i-1} f[j] * f[i-1-j]
    //
    // 但这里为了复用更直观的“前缀不为负”模型，
    // 改用经典一维 DP：
    // dp[len][bal] 表示当前长度和栈高。
    // 由于 n <= 100，这里直接用更常见的组合递推：
    // f[i] = f[i-1] * (4i-2) / (i+1)
    //
    // 为了保持高精度实现简单，这里仍使用区间划分递推。
    for (int i = 1; i <= n; i++) {
        f[i] = BigInt(0);
        for (int j = 0; j <= i - 1; j++) {
            // 这里 n 很小，如果写乘法高精度会增加代码复杂度。
            // 所以改成用括号序列 DP 的 BigInt 相加版更自然。
        }
    }

    vector<vector<BigInt>> dp(2 * n + 1, vector<BigInt>(n + 2, BigInt(0)));
    dp[0][0] = BigInt(1);

    for (int i = 0; i < 2 * n; i++) {
        for (int bal = 0; bal <= n; bal++) {
            if (dp[i][bal].d.size() == 1 && dp[i][bal].d[0] == 0) {
                continue;
            }

            // 放一个红筹，对应左括号。
            if (bal + 1 <= n) {
                dp[i + 1][bal + 1] = dp[i + 1][bal + 1] + dp[i][bal];
            }

            // 放一个黑筹，对应右括号，但前缀不能失衡。
            if (bal > 0) {
                dp[i + 1][bal - 1] = dp[i + 1][bal - 1] + dp[i][bal];
            }
        }
    }

    cout << dp[2 * n][0] << '\n';

    return 0;
}
