#include <bits/stdc++.h>
using namespace std;

// brute.cpp：O(n^2) DP，枚举最后一朵保留的花。

const int MAXN = 1005;

int n;
int h[MAXN];
int up[MAXN];
int down[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    int ans = 1;

    for (int i = 1; i <= n; i++) {
        up[i] = 1;   // 以 i 结尾，最后一段是上升
        down[i] = 1; // 以 i 结尾，最后一段是下降

        for (int j = 1; j < i; j++) {
            if (h[i] > h[j]) {
                up[i] = max(up[i], down[j] + 1);
            } else if (h[i] < h[j]) {
                down[i] = max(down[i], up[j] + 1);
            }
        }

        ans = max(ans, max(up[i], down[i]));
    }

    cout << ans << '\n';
    return 0;
}
