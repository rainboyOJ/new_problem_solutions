#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 5;

int n, k;
int a[maxn]; // 输入序列，使用 1-based 下标。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 枚举长度为 k 的每个连续窗口，l 表示窗口左端点。
    for (int l = 1; l + k - 1 <= n; l++) {
        int mn = a[l]; // 先用窗口第一个元素初始化最小值。

        // 逐个检查当前窗口中的元素，暴力求出最小值。
        for (int i = l; i < l + k; i++) {
            mn = min(mn, a[i]);
        }

        // 第一个答案前不输出空格，其余答案前输出一个空格。
        if (l > 1) {
            cout << ' ';
        }
        cout << mn;
    }
    cout << '\n';

    // 再次枚举所有窗口，暴力求出每个窗口的最大值。
    for (int l = 1; l + k - 1 <= n; l++) {
        int mx = a[l]; // 先用窗口第一个元素初始化最大值。

        for (int i = l; i < l + k; i++) {
            mx = max(mx, a[i]);
        }

        if (l > 1) {
            cout << ' ';
        }
        cout << mx;
    }
    cout << '\n';

    return 0;
}
