#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN];
int vis[MAXN];

void solve() {
    for (int i = 1; i < n; i++) {
        int d = abs(a[i + 1] - a[i]);
        if (d < 1 || d > n - 1 || vis[d]) {
            cout << "Not jolly\n";
            return;
        }
        vis[d] = 1;
    }

    cout << "Jolly\n";
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
