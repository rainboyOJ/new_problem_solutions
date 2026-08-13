/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:20
 * update_at: 2026-08-13 13:20
 */
// brute.cpp：小数据暴力解，把“下一块吃哪块奶酪”看成选择序列来递归枚举所有吃奶酪顺序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;
const double INF = 1e100;

int n;
double x[MAXN], y[MAXN];      // 每块奶酪的坐标
int path[MAXN];               // path[dep]：第 dep 步吃的奶酪编号，组成完整吃奶酪顺序
bool used[MAXN];              // used[i]：第 i 块奶酪是否已经吃过
double ans;                   // 记录当前找到的最短总距离

// 两点之间的欧氏距离。
double dist(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

// 一条完整吃奶酪顺序已经生成，按顺序把距离累加起来。
double calc_answer() {
    double cur = dist(0, 0, x[path[1]], y[path[1]]);   // 从原点出发
    for (int i = 2; i <= n; i++) {
        cur += dist(x[path[i - 1]], y[path[i - 1]], x[path[i]], y[path[i]]);
    }
    return cur;
}

// 第 dep 层在做“选择”：从没吃过的奶酪里选一块作为第 dep 步的目标。
void dfs(int dep) {
    if (dep == n + 1) {
        // 一条完整顺序生成完毕，统一检查并统计答案
        ans = min(ans, calc_answer());
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (used[i]) {
            continue;
        }
        used[i] = true;
        path[dep] = i;
        dfs(dep + 1);
        used[i] = false;   // 回溯，恢复状态
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    ans = INF;
    dfs(1);

    cout.setf(ios::fixed);
    cout << setprecision(2) << ans << '\n';
    return 0;
}
