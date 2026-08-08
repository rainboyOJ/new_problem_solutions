#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int h[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    int ans = 1;
    int last_sign = 0; // 0: 还没有方向, 1: 上升, -1: 下降

    for (int i = 2; i <= n; i++) {
        int diff = h[i] - h[i - 1];
        if (diff == 0) {
            continue;
        }

        int cur_sign = (diff > 0 ? 1 : -1);

        // 第一次出现有效方向，或者方向发生变化时，都可以把当前花留下。
        if (last_sign == 0 || cur_sign != last_sign) {
            ans++;
            last_sign = cur_sign;
        }
    }

    cout << ans << '\n';
    return 0;
}
