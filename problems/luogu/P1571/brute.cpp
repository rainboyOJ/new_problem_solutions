#include <bits/stdc++.h>
using namespace std;

int a[1005], b[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];

    bool first = true;
    for (int i = 1; i <= n; i++) {
        bool ok = false;
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) {
                ok = true;
                break;
            }
        }
        if (ok) {
            if (!first) cout << ' ';
            cout << a[i];
            first = false;
        }
    }
    cout << '\n';

    return 0;
}
