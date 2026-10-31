#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 5005;
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
    // 枚举区间右端点作为目标值
    for (int r = 1; r <= n; r++) {
        __int128 cost = 0;
        for (int l = r; l >= 1; l--) {
            cost += (a[r] - a[l]);
            if (cost <= m) {
                if (r - l + 1 > ans) {
                    ans = r - l + 1;
                }
            } else {
                break;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
