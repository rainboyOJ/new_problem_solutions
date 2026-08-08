#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using u128 = __uint128_t;

const int MAXN = 10005;

int n;
ull x_arr[MAXN];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ull mul_mod(ull a, ull b, ull mod) {
    return (u128) a * b % mod;
}

ull pow_mod(ull a, ull b, ull mod) {
    ull res = 1;
    while (b > 0) {
        if (b & 1ULL) {
            res = mul_mod(res, a, mod);
        }
        a = mul_mod(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool miller_rabin(ull n) {
    if (n < 2) {
        return false;
    }

    ull test_prime[] = {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL};
    for (int i = 0; i < 12; i++) {
        ull p = test_prime[i];
        if (n % p == 0) {
            return n == p;
        }
    }

    ull d = n - 1;
    int s = 0;
    while ((d & 1ULL) == 0) {
        d >>= 1;
        s++;
    }

    // 这组底数对 unsigned long long 范围内的数是确定正确的。
    ull base_arr[] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
    for (int i = 0; i < 7; i++) {
        ull a = base_arr[i] % n;
        if (a == 0) {
            continue;
        }

        ull x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }

        bool ok = false;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }

        if (!ok) {
            return false;
        }
    }

    return true;
}

ull pollard_rho(ull n) {
    if ((n & 1ULL) == 0) {
        return 2;
    }

    while (true) {
        ull c = uniform_int_distribution<ull>(1, n - 1)(rng);
        ull x = uniform_int_distribution<ull>(0, n - 1)(rng);
        ull y = x;
        ull d = 1;

        while (d == 1) {
            x = (mul_mod(x, x, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;

            ull diff = x > y ? x - y : y - x;
            d = gcd(diff, n);
        }

        if (d != n) {
            return d;
        }
    }
}

void factorize(ull n, vector<ull> &fac) {
    if (n == 1) {
        return;
    }
    if (miller_rabin(n)) {
        fac.push_back(n);
        return;
    }

    ull d = pollard_rho(n);
    factorize(d, fac);
    factorize(n / d, fac);
}

ull int_pow(ull a, int e) {
    ull res = 1;
    for (int i = 1; i <= e; i++) {
        res *= a;
    }
    return res;
}

ull solve_one(ull x) {
    if (x == 1) {
        return 1;
    }

    vector<ull> fac;
    factorize(x, fac);
    sort(fac.begin(), fac.end());

    ull ans = 1;
    for (int i = 0, j; i < (int)fac.size(); i = j) {
        j = i;
        while (j < (int)fac.size() && fac[j] == fac[i]) {
            j++;
        }
        int cnt = j - i;
        ans *= int_pow(fac[i], cnt / 3);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x_arr[i];
    }

    for (int i = 1; i <= n; i++) {
        cout << solve_one(x_arr[i]) << '\n';
    }

    return 0;
}
