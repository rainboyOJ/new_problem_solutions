// brute.cpp：枚举所有连续子段求和，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long ans = -(1LL << 60);
    for (int l = 1; l <= n; l++) {
        long long sum = 0;
        for (int r = l; r <= n; r++) {
            sum += a[r];
            ans = max(ans, sum);
        }
    }

    cout << ans << '\n';
    return 0;
}
