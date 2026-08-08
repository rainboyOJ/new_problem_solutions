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
    int ans = 1; // 当前找到的最长连号长度
    int len = 1; // 以当前位置结尾的连号长度

    for (int i = 2; i <= n; i++) {
        if (a[i] == a[i - 1] + 1) {
            len++;
        }
        else {
            len = 1;
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
