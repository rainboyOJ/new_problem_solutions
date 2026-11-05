#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 500000 + 5;
int n;
ll pre[maxn];
map<ll, ll> bucket;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        pre[i] = pre[i - 1] + x;
    }

    ll total = pre[n], ans = 0;
    for (int p = n - 1; p >= 1; p--) {
        // 表中只有右侧切点，先查询以保证两刀位置不同。
        // map 中不存在的键默认取值为 0，无需判断是否存在。
        if (3 * pre[p] == total) {
            ans += bucket[2 * pre[p]];
        }
        bucket[pre[p]]++;
    }
    cout << ans << '\n';
    return 0;
}
