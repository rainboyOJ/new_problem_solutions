/**
 * Problem: luogu P1031 - [NOIP 2002 提高组] 均分纸牌 (Brute / 前缀割截线基准)
 * Author: rainboy
 * Date: 2026-11-10 23:35
 * Description: 基于前缀割净盈亏为 0 的通道统计
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }

    int avg = sum / n;
    int cur_prefix_sum = 0;
    int moves = 0;

    for (int i = 0; i < n - 1; ++i) {
        cur_prefix_sum += (a[i] - avg);
        if (cur_prefix_sum != 0) {
            moves++;
        }
    }

    cout << moves << "\n";

    return 0;
}
