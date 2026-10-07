/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:53
 * update_at: 2026-10-06 10:53
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int ALL = 0b11111; // 5 盏灯全亮的状态
const int INF = 100;     // 超过 6 步的哨兵

int rows[6]; // 5x5 盘面每行压缩为一个 5 位整数

// 给定第一行操作 op0，递推得到最少步数；不可行返回 INF
int simulate(int op0) {
    int cur = op0;
    int steps = 0;
    for (int r = 0; r < 5; ++r) {
        steps += __builtin_popcount(cur);
        if (steps > 6) return INF;
        // 当前行自身及左右邻居被翻转
        rows[r] ^= cur ^ ((cur << 1) & ALL) ^ (cur >> 1);
        if (r + 1 < 5) {
            rows[r + 1] ^= cur;          // 下一行受当前行操作影响
            cur = (~rows[r]) & ALL;      // 当前行灭灯位置决定下一行必须按的开关
        } else {
            if (rows[r] != ALL) return INF; // 最后一行仍有灭灯则方案失败
        }
    }
    return steps;
}

int solve_one() {
    int backup[6];
    int ans = INF;
    for (int op0 = 0; op0 < 32; ++op0) {
        memcpy(backup, rows, sizeof(rows));
        ans = min(ans, simulate(op0));
        memcpy(rows, backup, sizeof(rows));
    }
    return ans <= 6 ? ans : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        string s;
        for (int r = 0; r < 5; ++r) {
            cin >> s;
            int mask = 0;
            for (int c = 0; c < 5; ++c)
                if (s[c] == '1') mask |= (1 << c);
            rows[r] = mask;
        }
        cout << solve_one() << "\n";
    }
    return 0;
}
