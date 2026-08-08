#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 5;

int n, k;
int a[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int l = 1; l + k - 1 <= n; l++) {
        int mn = a[l];
        for (int i = l; i < l + k; i++) {
            mn = min(mn, a[i]);
        }
        if (l > 1) {
            cout << ' ';
        }
        cout << mn;
    }
    cout << '\n';

    for (int l = 1; l + k - 1 <= n; l++) {
        int mx = a[l];
        for (int i = l; i < l + k; i++) {
            mx = max(mx, a[i]);
        }
        if (l > 1) {
            cout << ' ';
        }
        cout << mx;
    }
    cout << '\n';

    return 0;
}
