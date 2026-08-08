// brute.cpp：用搜索枚举所有向右/向下走法，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

int n, m;
long long ans;

bool blocked(int x, int y) {
    return x % 2 == 0 && y % 2 == 0;
}

void dfs(int x, int y) {
    if (x > n || y > m) {
        return;
    }
    if (blocked(x, y)) {
        return;
    }
    if (x == n && y == m) {
        ans++;
        return;
    }

    dfs(x + 1, y);
    dfs(x, y + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    dfs(1, 1);
    cout << ans << '\n';
    return 0;
}
