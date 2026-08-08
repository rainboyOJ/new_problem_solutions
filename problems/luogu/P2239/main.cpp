#include <bits/stdc++.h>
using namespace std;

long long n, i_pos, j_pos;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> i_pos >> j_pos;

    long long layer = min(min(i_pos - 1, j_pos - 1), min(n - i_pos, n - j_pos));
    long long top = layer + 1;
    long long left = layer + 1;
    long long bottom = n - layer;
    long long right = n - layer;
    long long len = n - 2 * layer;

    // start 表示这一层左上角格子的编号。
    long long start = 1 + 4LL * layer * (n - layer);

    long long ans;
    if (i_pos == top) {
        ans = start + (j_pos - left);
    } else if (j_pos == right) {
        ans = start + (len - 1) + (i_pos - top);
    } else if (i_pos == bottom) {
        ans = start + 2 * (len - 1) + (right - j_pos);
    } else {
        ans = start + 3 * (len - 1) + (bottom - i_pos);
    }

    cout << ans << '\n';
    return 0;
}
