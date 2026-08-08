#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n, m;
long long x[MAXN];
long long y[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        cin >> y[i];
    }
    for (int i = 1; i <= m - 1; i++) {
        cin >> x[i];
    }

    sort(y + 1, y + n, greater<long long>());
    sort(x + 1, x + m, greater<long long>());

    int i = 1;
    int j = 1;
    long long row_piece = 1;  // 当前被横切后有多少块横向条带
    long long col_piece = 1;  // 当前被竖切后有多少块纵向条带
    long long ans = 0;

    while (i <= n - 1 && j <= m - 1) {
        if (y[i] > x[j]) {
            ans += y[i] * col_piece;
            row_piece++;
            i++;
        } else {
            ans += x[j] * row_piece;
            col_piece++;
            j++;
        }
    }

    while (i <= n - 1) {
        ans += y[i] * col_piece;
        i++;
    }
    while (j <= m - 1) {
        ans += x[j] * row_piece;
        j++;
    }

    cout << ans << '\n';
    return 0;
}
