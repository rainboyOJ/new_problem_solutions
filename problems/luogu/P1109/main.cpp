#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n;
int a[MAXN];
int l, r;

void solve() {
    int sum = 0;
    int need_in = 0;   // 不足下界的组，总共至少需要补进多少人
    int need_out = 0;  // 超过上界的组，总共至少需要挪出多少人

    for (int i = 1; i <= n; i++) {
        sum += a[i];
        if (a[i] < l) {
            need_in += l - a[i];
        }
        else if (a[i] > r) {
            need_out += a[i] - r;
        }
    }

    if (sum < n * l || sum > n * r) {
        cout << -1 << '\n';
        return;
    }

    cout << max(need_in, need_out) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> l >> r;

    solve();

    return 0;
}
