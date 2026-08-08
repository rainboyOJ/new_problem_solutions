#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
long long a[MAXN];

void solve() {
    sort(a + 1, a + n + 1);

    long long cur = a[1];
    int cnt = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] == cur) {
            cnt++;
        }
        else {
            cout << cur << ' ' << cnt << '\n';
            cur = a[i];
            cnt = 1;
        }
    }
    cout << cur << ' ' << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
