/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 17:27
 * update_at: 2026-08-13 14:10
 */
// 1.cpp：自然数拆分的另一种 DFS 写法。
// 与 main.cpp 同一思路（加数非递减），区别在参数形式：dfs(pre, left, dep)
// 直接用 left 表示"还剩下多少要拆"，pre 是下一个加数的下界。
#include <bits/stdc++.h>
using namespace std;

int n;
int a[100005]; // a[dep]：当前方案第 dep 个加数

// 已确定前 dep-1 个加数，下一个加数至少为 pre，还剩下 left 没有拆。
void dfs(int pre, int left, int dep) {
    // 拆完：left == 0，输出方案。
    if (left == 0) {
        // 只有一项（dep == 2 表示只拆出 n 本身）不输出，题目要求至少两个加数。
        if (dep == 2)
            return;
        for (int i = 1; i <= dep - 2; i++)
            cout << a[i] << "+";
        cout << a[dep - 1] << "\n";
        return;
    }

    // 枚举下一个加数 i：不小于 pre（保证非递减去重），且不超过剩余的 left。
    for (int i = pre; i <= left; i++) {
        a[dep] = i;
        dfs(i, left - i, dep + 1);
    }
}

int main() {
    std::cin >> n;
    dfs(1, n, 1);

    return 0;
}
