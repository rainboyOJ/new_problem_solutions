#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        i64 n, m;
        cin >> n >> m;

        bool ok = false;
        for (i64 x = 1; x <= m; x++) {
            for (i64 y = x + 1; y <= m; y++) {
                if (n % x == n % y) {
                    ok = true;
                }
            }
        }

        if (ok) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }

    return 0;
}
