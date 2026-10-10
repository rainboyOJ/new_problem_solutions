#include <iostream>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    if (!(cin >> n >> m)) return 0;

    if (n > m) swap(n, m);

    if (n == 1) {
        cout << power(2, m) << "\n";
        return 0;
    }

    ll A[] = {0, 0, 12, 112, 912, 7136, 56768, 453504, 3626752};
    ll B[] = {0, 0, 36, 336, 2688, 21312, 170112, 1360128, 10879488};

    if (n <= 8) {
        if (n == m) {
            cout << A[n] << "\n";
        } else {
            cout << (B[n] * power(3, m - n - 1)) % MOD << "\n";
        }
    } else {
        cout << 0 << "\n";
    }

    return 0;
}
