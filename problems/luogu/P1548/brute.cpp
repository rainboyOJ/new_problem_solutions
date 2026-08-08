#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 直接枚举子矩形的左上角和右下角，再判断它是正方形还是普通长方形。
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    long long square_cnt = 0;
    long long rect_cnt = 0;

    for (int x1 = 1; x1 <= n; x1++) {
        for (int y1 = 1; y1 <= m; y1++) {
            for (int x2 = x1; x2 <= n; x2++) {
                for (int y2 = y1; y2 <= m; y2++) {
                    int height = x2 - x1 + 1;
                    int width = y2 - y1 + 1;
                    if (height == width) {
                        square_cnt++;
                    } else {
                        rect_cnt++;
                    }
                }
            }
        }
    }

    cout << square_cnt << ' ' << rect_cnt << '\n';
    return 0;
}
