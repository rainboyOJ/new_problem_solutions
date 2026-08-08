#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 205;

int n, m;
long long a[MAXN];   // 当前维护的数组，初始读入的是最终结果 b
int op[MAXM], x[MAXM], y[MAXM];

// 还原平方操作时，求一个整数平方根。
long long isqrt_ll(long long v) {
    long long r = (long long) sqrtl((long double) v);
    while ((r + 1) * (r + 1) <= v) {
        r++;
    }
    while (r * r > v) {
        r--;
    }
    return r;
}

void solve() {
    for (int i = m; i >= 1; i--) {
        if (op[i] == 1) {
            if (x[i] == y[i]) {
                a[x[i]] /= 2;
            }
            else {
                a[x[i]] -= a[y[i]];
            }
        }
        else {
            if (x[i] == y[i]) {
                a[x[i]] = isqrt_ll(a[x[i]]);
            }
            else {
                a[x[i]] /= a[y[i]];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> op[i] >> x[i] >> y[i];
    }

    solve();

    return 0;
}
