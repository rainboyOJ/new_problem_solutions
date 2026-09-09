/**
 * Author by Rainboy blog: https://rainboylv.com blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:52
 * update_at: 2026-08-28 21:52
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 完全不用任何贪心结论，直接枚举所有方案：
//   1) 01 序列 choose[] 枚举每个人分到 1 号窗口还是 2 号窗口；
//   2) 叶子节点里，对每个窗口内部的所有排队顺序（全排列）都试一遍。
// 取所有方案里"最后吃完时刻"的最小值，这就是最优答案。
// 复杂度约 O(2^N * (N+1)! * N)，只适合 N <= 8 的小数据。

const int MAXN = 10;
const int INF = 0x3f3f3f3f;

int n;
int a[MAXN], b[MAXN];   // 输入：打饭耗时、吃饭耗时
int choose[MAXN];       // choose[i] = 0/1 表示第 i 人分到 1 号 / 2 号窗口
int ans;

// 计算一个窗口内的人按 ids 给出的顺序排队时，最晚吃完的时刻。
int calc_one_window(int ids[], int cnt) {
    int cur = 0; // 窗口累计打饭时间
    int mx = 0;  // 该窗口最晚吃完时刻
    for (int k = 0; k < cnt; k++) {
        int id = ids[k];
        cur += a[id];          // 第 id 人打完饭的时刻
        mx = max(mx, cur + b[id]);
    }
    return mx;
}

// 叶子节点：当前 choose[] 已把所有人分好窗口，再枚举每个窗口内部的全排列。
void check() {
    int w1[MAXN], w2[MAXN];
    int c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 0) w1[c1++] = i;
        else w2[c2++] = i;
    }
    sort(w1, w1 + c1); // 从任意固定顺序开始做全排列
    sort(w2, w2 + c2);
    do {
        do {
            int cur = max(calc_one_window(w1, c1), calc_one_window(w2, c2));
            if (cur < ans) ans = cur;
        } while (next_permutation(w2, w2 + c2));
    } while (next_permutation(w1, w1 + c1));
}

// 每一层决定第 dep 个人分到哪个窗口，dep == n+1 时得到一条完整 01 序列。
void dfs(int dep) {
    if (dep == n + 1) {
        check();
        return;
    }
    for (int v = 0; v <= 1; v++) { // 这一层选择第 dep 人的窗口
        choose[dep] = v;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    ans = INF;
    dfs(1);

    cout << ans << '\n';
    return 0;
}
