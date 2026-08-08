#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1000;
int cover[MAXC + 1][MAXC + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // 朴素做法：直接枚举这个矩形覆盖到的每一个单位小方格。
        for (int x = x1; x < x2; x++) {
            for (int y = y1; y < y2; y++) {
                cover[x][y]++;
            }
        }
    }

    int ans = 0;
    for (int x = 0; x < MAXC; x++) {
        for (int y = 0; y < MAXC; y++) {
            if (cover[x][y] == k) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
