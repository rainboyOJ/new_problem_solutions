#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n;
long long m1, m2;
long long s[MAXN];

vector<pair<long long, long long> > target_factors;

void factorize_m1(long long x) {
    for (long long p = 2; p * p <= x; p++) {
        if (x % p != 0) {
            continue;
        }

        long long cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        target_factors.push_back(make_pair(p, cnt * m2));
    }

    if (x > 1) {
        target_factors.push_back(make_pair(x, m2));
    }
}

long long ceil_div(long long a, long long b) {
    return (a + b - 1) / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> m1 >> m2;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    factorize_m1(m1);

    // M = 1 时，初始 1 个细胞已经可以均分，时间就是 0。
    if (target_factors.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    long long ans = (long long)4e18;

    for (int i = 1; i <= n; i++) {
        long long need_time = 0;
        bool ok = true;

        for (int j = 0; j < (int)target_factors.size(); j++) {
            long long p = target_factors[j].first;
            long long need = target_factors[j].second;

            long long cnt = 0;
            long long x = s[i];
            while (x % p == 0) {
                x /= p;
                cnt++;
            }

            // 这个细胞完全不提供某个必须的质因子，那么永远不可能整除 M。
            if (cnt == 0) {
                ok = false;
                break;
            }

            need_time = max(need_time, ceil_div(need, cnt));
        }

        if (ok) {
            ans = min(ans, need_time);
        }
    }

    if (ans == (long long)4e18) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}
