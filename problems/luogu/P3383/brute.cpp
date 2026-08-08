// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n, q;
int k;
vector<int> primes;

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

void build_primes() {
    primes.clear();
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    build_primes();

    while (q--) {
        cin >> k;
        cout << primes[k - 1] << '\n';
    }

    return 0;
}
