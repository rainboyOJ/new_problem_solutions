// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int a[3];

bool check(int x) {
    int b[4];
    for (int i = 0; i < 3; i++) {
        b[i] = a[i];
    }
    b[3] = x;
    sort(b, b + 4);
    return b[1] - b[0] == b[2] - b[1] && b[2] - b[1] == b[3] - b[2];
}

void solve() {
    // 为了与正式解保持一致：
    // 如果有多个合法答案，优先输出数值更大的那个。
    int ans = -1000000000;
    for (int x = -1000; x <= 1000; x++) {
        if (check(x)) {
            ans = x;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a[0] >> a[1] >> a[2];
    solve();

    return 0;
}
