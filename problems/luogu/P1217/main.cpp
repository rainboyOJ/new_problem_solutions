#include <bits/stdc++.h>
using namespace std;

int a, b;

bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    if (x == 2) {
        return true;
    }
    if (x % 2 == 0) {
        return false;
    }
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

// 由种子 x 构造一个奇数位回文数。
int make_odd_palindrome(int x) {
    int res = x;
    x /= 10;
    while (x > 0) {
        res = res * 10 + x % 10;
        x /= 10;
    }
    return res;
}

void output_if_ok(int x) {
    if (x < a || x > b) {
        return;
    }
    if (is_prime(x)) {
        cout << x << '\n';
    }
}

void solve() {
    for (int x = 1; x <= 9; x++) {
        output_if_ok(x);
    }

    // 唯一可能成为质数的偶数位回文数是 11。
    output_if_ok(11);

    for (int seed = 10; seed <= 9999; seed++) {
        int pal = make_odd_palindrome(seed);
        if (pal > b) {
            break;
        }
        output_if_ok(pal);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    solve();

    return 0;
}
