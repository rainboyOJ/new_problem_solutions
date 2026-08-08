#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;
int diff[1002][1002];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        // 二维差分：对矩形区域 [x1,x2) × [y1,y2) 全部 +1
        diff[x1][y1]++;
        diff[x1][y2]--;
        diff[x2][y1]--;
        diff[x2][y2]++;
    }

    int ans = 0;
    for (int i = 0; i <= MAX; i++) {
        for (int j = 0; j <= MAX; j++) {
            // 二维前缀和，还原每个单位格子的油漆层数
            if (i > 0) diff[i][j] += diff[i - 1][j];
            if (j > 0) diff[i][j] += diff[i][j - 1];
            if (i > 0 && j > 0) diff[i][j] -= diff[i - 1][j - 1];
            // 格子 [i,i+1)×[j,j+1) 有面积，只统计 i,j < MAX
            if (diff[i][j] == K && i < MAX && j < MAX) ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
