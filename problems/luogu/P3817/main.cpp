#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long x;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long ans = 0;

    for (int i = 2; i <= n; i++) {
        long long sum = a[i - 1] + a[i];
        if (sum > x) {
            long long need = sum - x;
            long long eat = min(a[i], need);

            // 优先从当前盒子吃，保证前一个相邻对已经固定后不再被破坏。
            a[i] -= eat;
            ans += eat;
            need -= eat;

            if (need > 0) {
                a[i - 1] -= need;
                ans += need;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
