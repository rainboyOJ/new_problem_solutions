#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n;
int a[MAXN], b[MAXN], g[MAXN], k[MAXN];
int x, y;

int cover(int id, int px, int py) {
    return a[id] <= px && px <= a[id] + g[id] &&
           b[id] <= py && py <= b[id] + k[id];
}

void solve() {
    for (int i = n; i >= 1; i--) {
        if (cover(i, x, y)) {
            cout << i << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> g[i] >> k[i];
    }
    cin >> x >> y;

    solve();

    return 0;
}
