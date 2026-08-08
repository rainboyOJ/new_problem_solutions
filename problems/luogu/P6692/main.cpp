#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct BigInt {
    static const int BASE = 1000000000;
    vector<int> d; // 小端存储

    BigInt(i64 x = 0) {
        if (x == 0) {
            d.push_back(0);
            return;
        }
        while (x > 0) {
            d.push_back((int) (x % BASE));
            x /= BASE;
        }
    }

    void trim() {
        while (d.size() > 1 && d.back() == 0) {
            d.pop_back();
        }
    }

    BigInt &operator += (const BigInt &other) {
        int n = max(d.size(), other.d.size());
        d.resize(n, 0);

        i64 carry = 0;
        for (int i = 0; i < n; i++) {
            i64 cur = carry + d[i];
            if (i < (int) other.d.size()) {
                cur += other.d[i];
            }
            d[i] = (int) (cur % BASE);
            carry = cur / BASE;
        }

        if (carry) {
            d.push_back((int) carry);
        }
        return *this;
    }

    BigInt &operator -= (const BigInt &other) {
        i64 borrow = 0;
        for (int i = 0; i < (int) d.size(); i++) {
            i64 cur = (i64) d[i] - borrow;
            if (i < (int) other.d.size()) {
                cur -= other.d[i];
            }

            if (cur < 0) {
                cur += BASE;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            d[i] = (int) cur;
        }

        trim();
        return *this;
    }

    BigInt mul_small(i64 x) const {
        if (x == 0) {
            return BigInt(0);
        }

        BigInt res;
        res.d.assign(d.size(), 0);

        i64 carry = 0;
        for (int i = 0; i < (int) d.size(); i++) {
            i64 cur = (i64) d[i] * x + carry;
            res.d[i] = (int) (cur % BASE);
            carry = cur / BASE;
        }

        while (carry > 0) {
            res.d.push_back((int) (carry % BASE));
            carry /= BASE;
        }
        res.trim();
        return res;
    }

    BigInt div_small(int x) const {
        BigInt res;
        res.d.assign(d.size(), 0);

        i64 rem = 0;
        for (int i = (int) d.size() - 1; i >= 0; i--) {
            i64 cur = rem * BASE + d[i];
            res.d[i] = (int) (cur / x);
            rem = cur % x;
        }

        res.trim();
        return res;
    }

    string to_string() const {
        string s = std::to_string(d.back());
        char buf[16];
        for (int i = (int) d.size() - 2; i >= 0; i--) {
            snprintf(buf, sizeof(buf), "%09d", d[i]);
            s += buf;
        }
        return s;
    }
};

BigInt operator + (BigInt a, const BigInt &b) {
    a += b;
    return a;
}

BigInt operator - (BigInt a, const BigInt &b) {
    a -= b;
    return a;
}

int k;
i64 n, m;
vector<i64> xs, ys;

// 计算 pos 到 1..len 所有点的距离和。
BigInt sum_to_all(i64 len, i64 pos) {
    BigInt left = BigInt(pos - 1).mul_small(pos).div_small(2);
    i64 right_cnt = len - pos;
    BigInt right = BigInt(right_cnt).mul_small(right_cnt + 1).div_small(2);
    return left + right;
}

// 计算一个有序数组中，两两差值和。
BigInt pair_diff_sum(vector<i64> a) {
    sort(a.begin(), a.end());

    BigInt ans(0);
    BigInt prefix(0);
    for (int i = 0; i < (int) a.size(); i++) {
        BigInt cur((i64) a[i] * i);
        cur -= prefix;
        ans += cur;
        prefix += BigInt(a[i]);
    }
    return ans;
}

BigInt line_pair_sum(i64 len) {
    // sum_{1<=i<j<=len} (j-i) = len*(len-1)*(len+1)/6
    BigInt res(len);
    res = res.mul_small(len - 1);
    res = res.mul_small(len + 1);
    res = res.div_small(6);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    xs.resize(k);
    ys.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> xs[i] >> ys[i];
    }

    // 完整 n*m 网格中，所有无序点对的曼哈顿距离总和。
    BigInt total_full = line_pair_sum(n).mul_small(m).mul_small(m)
                      + line_pair_sum(m).mul_small(n).mul_small(n);

    // 障碍点到整张网格所有点的距离和（每个障碍点只算一次）。
    BigInt remove_sum(0);
    for (int i = 0; i < k; i++) {
        remove_sum += sum_to_all(n, xs[i]).mul_small(m);
        remove_sum += sum_to_all(m, ys[i]).mul_small(n);
    }

    // 障碍点之间的无序距离和。前面 remove_sum 把这些对减了两次，这里补回一次。
    BigInt blocked_pair_sum = pair_diff_sum(xs) + pair_diff_sum(ys);

    BigInt answer = total_full + blocked_pair_sum;
    answer -= remove_sum;
    cout << answer.to_string() << '\n';
    return 0;
}
