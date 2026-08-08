#include <bits/stdc++.h>
using namespace std;

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    long long square_cnt = 0;
    long long rect_cnt = 0;

    // 枚举子矩形的高和宽，统计这种尺寸一共能出现多少次。
    for (int h = 1; h <= n; h++) {
        for (int w = 1; w <= m; w++) {
            long long ways = 1LL * (n - h + 1) * (m - w + 1);
            if (h == w) {
                square_cnt += ways;
            } else {
                rect_cnt += ways;
            }
        }
    }

    cout << square_cnt << ' ' << rect_cnt << '\n';
    return 0;
}
