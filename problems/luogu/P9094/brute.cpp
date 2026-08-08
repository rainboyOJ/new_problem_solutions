#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<array<int, 4>> paint(n + 1);

    for (int i = 1; i <= m; ++i) {
        int l, r, k;
        cin >> l >> r >> k;

        // 小数据可信解：直接给区间内每一罐油漆打上颜色标记。
        for (int pos = l; pos <= r; ++pos) {
            paint[pos][k] = 1;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (paint[i][1] && paint[i][2] && !paint[i][3]) {
            ++ans;
        }
    }

    cout << ans << '\n';
    return 0;
}
