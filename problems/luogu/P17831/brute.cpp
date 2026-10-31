#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 25;
ll a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    if (!(cin >> n >> m)) return 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 1;
    // 枚举所有非空子集
    for (int mask = 1; mask < (1 << n); mask++) {
        ll max_val = -4e18;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                cnt++;
                if (a[i] > max_val) max_val = a[i];
            }
        }
        ll cost = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                cost += (max_val - a[i]);
                if (cost > m) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok && cnt > ans) {
            ans = cnt;
        }
    }

    cout << ans << "\n";
    return 0;
}
