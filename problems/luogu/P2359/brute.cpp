#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接枚举所有 n 位数，逐个检查每个长度为 3 的连续子串是否都是三位素数。

int n;
const int MOD = 1000000009;

bool check_prime(int x) {
    if (x < 2) {
        return false;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

bool check_number(int x) {
    string s = to_string(x);
    if ((int)s.size() != n) {
        return false;
    }
    for (int i = 0; i + 2 < n; i++) {
        int val = (s[i] - '0') * 100 + (s[i + 1] - '0') * 10 + (s[i + 2] - '0');
        if (val < 100 || !check_prime(val)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    if (n < 3) {
        cout << 0 << '\n';
        return 0;
    }

    int start = 1;
    for (int i = 1; i < n; i++) {
        start *= 10;
    }
    int finish = start * 10 - 1;

    int ans = 0;
    for (int x = start; x <= finish; x++) {
        if (check_number(x)) {
            ans++;
        }
    }

    cout << ans % MOD << '\n';
    return 0;
}
