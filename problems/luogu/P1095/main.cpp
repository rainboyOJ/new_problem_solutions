/**
 * Problem: luogu P1095 - [NOIP 2007 普及组] 守望者的逃离
 * Author: rainboy
 * Date: 2026-11-10 23:00
 * Description: 动态规划：法术推进与跑步松弛
 */
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXT = 300005;
int f[MAXT];  // f[t] 表示第 t 秒能走的最远距离

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, s, t;
    if (!(cin >> m >> s >> t)) return 0;

    // 第一阶段：纯法术状态转移（优先闪烁，无法闪烁则原地休息回蓝）
    for (int i = 1; i <= t; ++i) {
        if (m >= 10) {
            f[i] = f[i - 1] + 60;
            m -= 10;
        } else {
            f[i] = f[i - 1];
            m += 4;
        }
    }

    // 第二阶段：跑步状态松弛与最早到达判定
    for (int i = 1; i <= t; ++i) {
        // 比较上一秒跑步过来的距离与当前法术距离
        f[i] = max(f[i], f[i - 1] + 17);
        if (f[i] >= s) {
            cout << "Yes\n" << i << "\n";
            return 0;
        }
    }

    // 若 t 秒内无法逃离，输出最大能到达的距离
    cout << "No\n" << f[t] << "\n";

    return 0;
}
