/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:27
 * update_at: 2026-08-13 13:29
 */
/* P2404 自然数的拆分问题 */
/* DFS 枚举非递减加数序列：每一层选择下一个加数，要求不小于上一个。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15; // n <= 8，全 1 拆分时序列最长也只有 n 项

int n;
int path[MAXN]; // path[1..depth] 保存当前拆分序列
int depth;      // 当前序列长度

// 还需凑出 remaining，下一个加数至少为 min_val
void dfs(int remaining, int min_val) {
    if (remaining == 0) {
        if (depth > 1) { // 排除只有 n 本身的单项方案
            for (int i = 1; i <= depth; i++) {
                if (i > 1)
                    cout << "+";
                cout << path[i];
            }
            cout << "\n";
        }
        return;
    }

    for (int val = min_val; val <= remaining; val++) {
        path[++depth] = val;
        dfs(remaining - val, val); // 下一项不小于 val，保证序列非递减
        depth--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dfs(n, 1);
    return 0;
}
