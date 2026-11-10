/**
 * Problem: luogu P1031 - [NOIP 2002 提高组] 均分纸牌
 * Author: rainboy
 * Date: 2026-11-10 23:35
 * Description: 差额单向推移贪心算法
 */
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MAXN = 105;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum += a[i];
    }

    int avg = sum / n;
    int ans = 0;

    // 从左到右依次将差额推向相邻右侧
    for (int i = 1; i < n; ++i) {
        if (a[i] != avg) {
            int diff = a[i] - avg;
            a[i + 1] += diff;
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}
