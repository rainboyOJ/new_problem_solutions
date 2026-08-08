#include <bits/stdc++.h>
using namespace std;

int school[1005], stu[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    for (int i = 1; i <= m; i++) cin >> school[i];
    for (int i = 1; i <= n; i++) cin >> stu[i];

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int best = abs(school[1] - stu[i]);
        for (int j = 2; j <= m; j++) {
            best = min(best, abs(school[j] - stu[i]));
        }
        ans += best;
    }

    cout << ans << '\n';
    return 0;
}
