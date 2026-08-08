// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int a, b;

bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; 1LL * d * d <= x; d++) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

bool is_palindrome(int x) {
    int y = x;
    int rev = 0;
    while (y > 0) {
        rev = rev * 10 + y % 10;
        y /= 10;
    }
    return rev == x;
}

void solve() {
    for (int x = a; x <= b; x++) {
        if (is_palindrome(x) && is_prime(x)) {
            cout << x << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    solve();

    return 0;
}
