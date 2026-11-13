/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 09:10
 * update_at: 2026-11-13 09:10
 */
// main2.cpp：解法 2 前缀和 + 二分查找
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 200000 + 50;
const long long INF = 1e18;

long long a[maxn];
int b[maxn];

long long one[maxn];
long long two[maxn];
long long sum_one[maxn];
long long sum_two[maxn];

void solve() {
    int n;
    long long m;
    if (!(cin >> n >> m)) return;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[i] == 1) {
            one[++cnt1] = a[i];
        } else {
            two[++cnt2] = a[i];
        }
    }

    sort(one + 1, one + cnt1 + 1, greater<long long>());
    sort(two + 1, two + cnt2 + 1, greater<long long>());

    sum_one[0] = 0;
    for (int i = 1; i <= cnt1; ++i) {
        sum_one[i] = sum_one[i - 1] + one[i];
    }

    sum_two[0] = 0;
    for (int i = 1; i <= cnt2; ++i) {
        sum_two[i] = sum_two[i - 1] + two[i];
    }

    if (sum_one[cnt1] + sum_two[cnt2] < m) {
        cout << -1 << "\n";
        return;
    }

    // 解法 2：枚举 x，二分查找最小的 y
    long long ans = INF;

    for (int x = 0; x <= cnt1; ++x) {
        long long need = m - sum_one[x];
        if (need <= 0) {
            ans = min(ans, (long long)x);
            continue;
        }

        // 在单调递增的前缀和 sum_two[1...cnt2] 中二分找到首个 >= need 的位置
        int y = lower_bound(sum_two + 1, sum_two + cnt2 + 1, need) - sum_two;
        if (y <= cnt2) {
            ans = min(ans, (long long)x + 2LL * y);
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
