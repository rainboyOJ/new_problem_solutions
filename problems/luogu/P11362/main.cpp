#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;
const int MAXM = 100005;

struct Constraint {
    long long pos;
    long long value;
};

int T, m;
long long n, v;
Constraint cons[MAXM];

bool cmp_constraint(Constraint a, Constraint b) {
    if (a.pos != b.pos) {
        return a.pos < b.pos;
    }
    return a.value < b.value;
}

long long power_mod(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1LL) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

long long interval_count(long long len) {
    long long total = power_mod(v * v % MOD, len);
    long long bad = power_mod(v, len - 1) * ((v - 1) % MOD) % MOD;
    return (total - bad + MOD) % MOD;
}

void solve_one() {
    cin >> n >> m >> v;
    for (int i = 1; i <= m; i++) {
        cin >> cons[i].pos >> cons[i].value;
    }

    sort(cons + 1, cons + m + 1, cmp_constraint);

    vector<Constraint> fixed_point;
    bool ok = true;

    for (int i = 1; i <= m; i++) {
        if (!fixed_point.empty() && fixed_point.back().pos == cons[i].pos) {
            if (fixed_point.back().value != cons[i].value) {
                ok = false;
            }
        } else {
            fixed_point.push_back(cons[i]);
        }
    }

    if (!ok) {
        cout << 0 << '\n';
        return;
    }

    long long all_edge = v * v % MOD;
    long long free_edges = 0;
    long long ans = 1;

    if (fixed_point.empty()) {
        free_edges = n - 1;
    } else {
        free_edges += fixed_point[0].pos - 1;
        free_edges += n - fixed_point.back().pos;

        for (int i = 0; i + 1 < (int)fixed_point.size(); i++) {
            long long len = fixed_point[i + 1].pos - fixed_point[i].pos;
            ans = ans * interval_count(len) % MOD;
        }
    }

    ans = ans * power_mod(all_edge, free_edges) % MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
