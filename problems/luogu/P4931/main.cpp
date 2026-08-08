#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

struct Ask {
    int n, k;
};

vector<Ask> asks;
vector<int> factorial_value;
vector<int> inverse_factorial;
vector<int> pow_two;
vector<int> no_harmony; // no_harmony[i] 表示 i 对情侣、i 排座位时没有任何和睦情侣的方案数。

long long fast_power(long long a, long long b) {
    long long result = 1;
    while (b > 0) {
        if (b & 1) {
            result = result * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return result;
}

long long combination(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    return (long long)factorial_value[n] * inverse_factorial[k] % MOD * inverse_factorial[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    asks.resize(t);
    int max_n = 0;
    for (int i = 0; i < t; i++) {
        cin >> asks[i].n >> asks[i].k;
        max_n = max(max_n, asks[i].n);
    }

    factorial_value.assign(max_n + 1, 1);
    inverse_factorial.assign(max_n + 1, 1);
    pow_two.assign(max_n + 1, 1);
    no_harmony.assign(max_n + 1, 0);

    for (int i = 1; i <= max_n; i++) {
        factorial_value[i] = (long long)factorial_value[i - 1] * i % MOD;
        pow_two[i] = (long long)pow_two[i - 1] * 2 % MOD;
    }
    if (max_n >= 0) {
        inverse_factorial[max_n] = fast_power(factorial_value[max_n], MOD - 2);
        for (int i = max_n; i >= 1; i--) {
            inverse_factorial[i - 1] = (long long)inverse_factorial[i] * i % MOD;
        }
    }

    no_harmony[0] = 1;
    if (max_n >= 1) {
        no_harmony[1] = 0;
    }
    for (int i = 2; i <= max_n; i++) {
        // 取一对情侣中的一个人所在行分类，递推出没有任何情侣同排的排座方案数。
        long long part = (no_harmony[i - 1] + 2LL * (i - 1) % MOD * no_harmony[i - 2]) % MOD;
        no_harmony[i] = (int)(4LL * i % MOD * (i - 1) % MOD * part % MOD);
    }

    for (int i = 0; i < t; i++) {
        int n = asks[i].n;
        int k = asks[i].k;
        long long answer = combination(n, k) * combination(n, k) % MOD;
        answer = answer * factorial_value[k] % MOD * pow_two[k] % MOD;
        answer = answer * no_harmony[n - k] % MOD;
        cout << answer << '\n';
    }

    return 0;
}
