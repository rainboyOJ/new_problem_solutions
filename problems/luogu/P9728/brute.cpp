/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 13:15
 *
 * P9728 [EC Final 2022] Dining Professors
 * 暴力解：辣菜之间没有区别、不辣菜之间也没有区别，
 *         于是只需枚举「哪 n-a 个位置放不辣菜」这 C(n, n-a) 种情况，
 *         对每种情况老老实实按定义统计满意度，取最大值。
 *         只适合 n<=20 左右的小数据，用于对拍。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;

int n;   // 教授人数 = 位置数
int a;   // 辣菜数量
int b[maxn];  // b[i]=1:教授 i 能吃辣
int pos[maxn]; // pos[p]=1:位置 p 放的是不辣菜

ll best; // 当前找到的最大满意度

// dep:      正在决定第 dep 个位置
// spicyCnt: 已经放掉的辣菜数量
void dfs(int dep, int spicyCnt) {
    // 剩下的位置全放辣菜也不够 n-a 道不辣菜，剪枝
    if (spicyCnt > a) {
        return;
    }
    if (dep == n) {
        if (spicyCnt != a) {
            return;
        }
        ll tot = 0;
        for (int i = 0; i < n; ++i) {
            int l = (i - 1 + n) % n; // 左边位置
            int r = (i + 1) % n;     // 右边位置
            if (b[i] == 1) {
                tot += 3;            // 能吃辣：三盘菜都算满意
            } else {
                tot += pos[l] + pos[i] + pos[r]; // 不能吃辣：只数不辣菜
            }
        }
        if (tot > best) {
            best = tot;
        }
        return;
    }
    // 位置 dep 放辣菜
    pos[dep] = 0;
    dfs(dep + 1, spicyCnt + 1);
    // 位置 dep 放不辣菜
    pos[dep] = 1;
    dfs(dep + 1, spicyCnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    best = -1;
    dfs(0, 0);
    cout << best << "\n";
    return 0;
}
