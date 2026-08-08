// brute.cpp：小数据朴素解，用 O(n^2) DP 分别求最长不上升和最长上升子序列。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n;
int a[MAXN];
int dp1[MAXN], dp2[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> a[n + 1]) {
        n++;
    }

    int ans1 = 0;
    for (int i = 1; i <= n; i++) {
        dp1[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] >= a[i]) {
                dp1[i] = max(dp1[i], dp1[j] + 1);
            }
        }
        ans1 = max(ans1, dp1[i]);
    }

    int ans2 = 0;
    for (int i = 1; i <= n; i++) {
        dp2[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i]) {
                dp2[i] = max(dp2[i], dp2[j] + 1);
            }
        }
        ans2 = max(ans2, dp2[i]);
    }

    cout << ans1 << '\n';
    cout << ans2 << '\n';
    return 0;
}
