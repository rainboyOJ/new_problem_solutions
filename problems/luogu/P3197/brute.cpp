#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int m, n;
int choose_color[20];
i64 ans = 0;

void dfs(int pos) {
    if (pos == n + 1) {
        for (int i = 1; i < n; i++) {
            if (choose_color[i] == choose_color[i + 1]) {
                ans++;
                return;
            }
        }
        return;
    }

    for (int c = 1; c <= m; c++) {
        choose_color[pos] = c;
        dfs(pos + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    dfs(1);
    cout << ans % 100003 << '\n';
    return 0;
}
