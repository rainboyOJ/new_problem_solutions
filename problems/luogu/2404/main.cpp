/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P2404 自然数的拆分问题 */
/* DFS 枚举非递减加数序列，下一项从上一项开始选择，避免重复。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int path[MAXN]; // 保存当前拆分序列
int depth;      // 当前序列长度

// 剩余剩余，当前最小可选值
void dfs(int remaining, int min_val) {
    if (remaining == 0) {
        if (depth > 1) { // 排除只有一个数的情况
            for (int i = 1; i < depth; i++) {
                cout << path[i] << "+";
            }
            cout << path[depth] << "\n";
        }
        return;
    }

    for (int val = min_val; val <= remaining; val++) {
        path[++depth] = val;
        dfs(remaining - val, val); // 下一项至少为 val，保证非递减
        depth--;
    }
}

int main() {
    cin >> n;
    dfs(n, 1);
    return 0;
}
