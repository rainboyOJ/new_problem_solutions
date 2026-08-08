#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

int n, m, b, g;
int diff_row[MAXN], diff_col[MAXN];

int count_covered(int limit, int diff[]) {
    int covered = 0;
    int sum = 0;

    for (int i = 1; i <= limit; i++) {
        sum += diff[i];
        if (sum > 0) {
            covered++;
        }
    }

    return covered;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> b >> g;

    for (int i = 1; i <= b; i++) {
        int l, r;
        cin >> l >> r;
        diff_row[l]++;
        diff_row[r + 1]--;
    }

    for (int i = 1; i <= g; i++) {
        int l, r;
        cin >> l >> r;
        diff_col[l]++;
        diff_col[r + 1]--;
    }

    long long covered_row = count_covered(n, diff_row);
    long long covered_col = count_covered(m, diff_col);

    // 容斥：被覆盖的行全部算一次，被覆盖的列全部算一次，
    // 同时属于覆盖行和覆盖列的格子被重复统计，需要减掉。
    long long ans = covered_row * m + covered_col * n - covered_row * covered_col;
    cout << ans << '\n';

    return 0;
}
