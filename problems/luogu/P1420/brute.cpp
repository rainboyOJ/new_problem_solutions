// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n;
int a[MAXN]; // 输入序列

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    int ans = 1;

    // 枚举每个起点，向右检查这一段能连续增长多久。
    for (int i = 1; i <= n; i++) {
        int len = 1;
        for (int j = i + 1; j <= n; j++) {
            if (a[j] == a[j - 1] + 1) {
                len++;
            }
            else {
                break;
            }
        }
        ans = max(ans, len);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
