#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, d;
int v[MAXN];
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n - 1; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    long long dist_sum = 0;      // 到当前站点之后累计走了多少公里
    long long bought = 0;        // 到当前为止一共已经买了多少升油
    int min_price = a[1];

    for (int i = 1; i <= n - 1; i++) {
        min_price = min(min_price, a[i]);
        dist_sum += v[i];

        // 走完前 i 段路后，至少需要 ceil(dist_sum / d) 升油。
        long long need = (dist_sum + d - 1) / d;
        if (need > bought) {
            ans += (need - bought) * 1LL * min_price;
            bought = need;
        }
    }

    cout << ans << '\n';

    return 0;
}
