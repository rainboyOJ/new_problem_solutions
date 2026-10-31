#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 500005;
ll a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    ll ans = 1;
    int l = 1;
    __int128 cur_cost = 0;

    for (int r = 1; r <= n; r++) {
        if (r > 1) {
            cur_cost += (__int128)(r - l) * (a[r] - a[r - 1]);
        }
        while (cur_cost > m) {
            cur_cost -= (a[r] - a[l]);
            l++;
        }
        if (r - l + 1 > ans) {
            ans = r - l + 1;
        }
    }

    cout << ans << "\n";
    return 0;
}
