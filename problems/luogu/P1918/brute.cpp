#include <bits/stdc++.h>
using namespace std;

int a[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int q;
    cin >> q;
    while (q--) {
        int need;
        cin >> need;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] == need) {
                ans = i;
                break;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
