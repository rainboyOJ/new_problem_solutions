#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using u128 = __uint128_t;

const int MAXN = 2005;

int n, m;
ull a[MAXN][MAXN];
int target_x, target_y;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ull mul_mod(ull a, ull b, ull mod) {
    return (u128) a * b % mod;
}

ull pow_mod(ull a, ull b, ull mod) {
    ull res = 1;
    while (b) {
        if (b & 1) {
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
    for (ull p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) {
            return n == p;
        }
    }

    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) {
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
    if (n % 2 == 0) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    cin >> target_x >> target_y;

    ull start = a[target_x][target_y];
    if (start == 1) {
        cout << 0 << '\n';
        return 0;
    }

    vector<ull> fac;
    factorize(start, fac);
    sort(fac.begin(), fac.end());
    fac.erase(unique(fac.begin(), fac.end()), fac.end());

    int ans = 0;
    for (int idx = 0; idx < (int) fac.size(); idx++) {
        ull p = fac[idx];
        int best = INT_MAX;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i][j] % p != 0) {
                    int d = abs(i - target_x) + abs(j - target_y);
                    if (d < best) {
                        best = d;
                    }
                }
            }
        }

        if (best == INT_MAX) {
            cout << -1 << '\n';
            return 0;
        }
        ans = max(ans, best);
    }

    cout << ans << '\n';
    return 0;
}
