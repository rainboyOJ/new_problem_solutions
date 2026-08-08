#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举分界点并暴力统计左右两边的错误数量。

const int MAXN = 30005;

int n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = n;

    for (int cut = 0; cut <= n; cut++) {
        int cost = 0;

        for (int i = 1; i <= cut; i++) {
            if (a[i] != 1) {
                cost++;
            }
        }

        for (int i = cut + 1; i <= n; i++) {
            if (a[i] != 2) {
                cost++;
            }
        }

        ans = min(ans, cost);
    }

    cout << ans << '\n';
    return 0;
}
