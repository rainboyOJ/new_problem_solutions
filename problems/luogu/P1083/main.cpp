#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n, m;
long long r[MAXN];
long long diff_arr[MAXN];
long long d[MAXN];
int s[MAXN], t[MAXN];

bool check(int k) {
    for (int i = 1; i <= n + 1; i++) {
        diff_arr[i] = 0;
    }

    for (int i = 1; i <= k; i++) {
        diff_arr[s[i]] += d[i];
        diff_arr[t[i] + 1] -= d[i];
    }

    long long cur = 0;
    for (int i = 1; i <= n; i++) {
        cur += diff_arr[i];
        if (cur > r[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> d[i] >> s[i] >> t[i];
    }

    if (check(m)) {
        cout << 0 << '\n';
        return 0;
    }

    int l = 1;
    int rgt = m;
    while (l < rgt) {
        int mid = (l + rgt) >> 1;
        if (check(mid)) {
            l = mid + 1;
        } else {
            rgt = mid;
        }
    }

    cout << -1 << '\n';
    cout << l << '\n';
    return 0;
}
