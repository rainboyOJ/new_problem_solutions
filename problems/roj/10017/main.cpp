#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<long long> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    vector<long long> fact(n + 1, 1), inv(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    
    auto power = [](long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = res * base % MOD;
            base = base * base % MOD;
            exp /= 2;
        }
        return res;
    };
    
    inv[n] = power(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
    
    auto comb = [&](int n, int k) -> long long {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
    };
    
    long long ans = 0;
    if (n % 2 == 1) {
        int k = n / 2;
        for (int j = 0; j < n; j++) {
            if (j % 2 != 0) continue;
            int p = j / 2;
            long long c = comb(k, p);
            if (p % 2 == 1) {
                c = (MOD - c) % MOD;
            }
            ans = (ans + A[j] % MOD * c % MOD) % MOD;
        }
    } else {
        int k = n / 2;
        for (int j = 0; j < n; j++) {
            int p = j / 2;
            long long c = comb(k - 1, p);
            if (p % 2 == 1) {
                c = (MOD - c) % MOD;
            }
            ans = (ans + A[j] % MOD * c % MOD) % MOD;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
