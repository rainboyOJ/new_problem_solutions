#include <bits/stdc++.h>
using namespace std;

const int MAXM = 405;

int n, m;
int x[MAXM], y[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x[i] >> y[i];
        x[i]--;
        y[i]--;
    }

    int ans = 0;
    int total = 1 << n;
    for (int mask = 0; mask < total; mask++) {
        bool ok = true;
        for (int i = 1; i <= m; i++) {
            if ((mask & (1 << x[i])) && (mask & (1 << y[i]))) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
