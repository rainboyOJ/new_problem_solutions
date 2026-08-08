#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 对每个发射站直接向左右两边暴力寻找最近的更高站。
const int MAXN = 1000000 + 5;

int n;
long long h[MAXN], v[MAXN];
long long rec[MAXN]; // rec[i] 表示第 i 个发射站收到的总能量

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> v[i];
    }

    for (int i = 1; i <= n; i++) {
        // 向左暴力找最近的更高站。
        int j = i - 1;
        while (j >= 1 && h[j] < h[i]) {
            j--;
        }
        if (j >= 1) {
            rec[j] += v[i];
        }

        // 向右暴力找最近的更高站。
        j = i + 1;
        while (j <= n && h[j] < h[i]) {
            j++;
        }
        if (j <= n) {
            rec[j] += v[i];
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, rec[i]);
    }

    cout << ans << '\n';
    return 0;
}
