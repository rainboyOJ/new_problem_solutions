/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P2386 放苹果：递归给每个盘子分苹果，分法按“不下降序列”去重，回溯时恢复现场。 */

#include <iostream>

const int max_n = 15;  // 盘子数最大为 10

int m, n;          // m 个苹果，n 个盘子
int a[max_n];      // a[dep]：第 dep 个盘子分到的苹果数，a[0] = 0 作为前一个盘子的初值
int cnt = 0;       // 合法分法数

// 给第 dep 个盘子分苹果（盘子编号 1 起始）。
// 苹果数不下降可以避免重复：同一个分法只保留排序后那一种写法。
void dfs(int dep) {
    if (dep == n) {
        // 最后一个盘子拿走全部剩余苹果，只要它不少于前一个盘子就合法。
        if (m >= a[dep - 1]) {
            cnt += 1;
        }
        return;
    }
    // 当前盘子至少要放前一个盘子那么多，至多放完剩余苹果。
    for (int i = a[dep - 1]; i <= m; i += 1) {
        a[dep] = i;  // 前进阶段：记录本盘选择，剩余苹果减少
        m -= i;
        dfs(dep + 1);
        m += i;      // 回溯阶段：恢复剩余苹果数
        a[dep] = 0;  // 回溯阶段：恢复本盘选择
    }
}

int main() {
    int t;
    std::cin >> t;
    while (t > 0) {
        std::cin >> m >> n;
        cnt = 0;
        dfs(1);
        std::cout << cnt << '\n';
        t -= 1;
    }
    return 0;
}
