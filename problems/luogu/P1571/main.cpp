#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
int a[MAXN], b[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];

    sort(b + 1, b + m + 1);

    bool first = true;
    for (int i = 1; i <= n; i++) {
        // 在第二个获奖名单中查找 a[i]，输出顺序仍然按第一个名单来。
        int pos = lower_bound(b + 1, b + m + 1, a[i]) - b;
        if (pos <= m && b[pos] == a[i]) {
            if (!first) cout << ' ';
            cout << a[i];
            first = false;
        }
    }
    cout << '\n';

    return 0;
}
